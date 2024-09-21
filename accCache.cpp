#include "util.h"
#include "accCache.h"
#include "tabAccManager.h"
#include "tabLauncher.h"
#include "OneLaunch.h"


const String AccCache::accountsFile = "onelaunch/accounts.json";
Array<Account> AccCache::Accounts;


const Array<Account>& AccCache::getAccounts() { 

    return Accounts;
}


void AccCache::init() {

    if (FileExists(accountsFile)) {

        Util::print("[ACC] Accounts file found.", true);
    } else {

        Util::print("[INS] Creating accounts file.");
        createAccountsFile();
    }

    if (!loadAccounts()) {

        Util::print("[ACC] Error loading accounts.");
    }
}


bool AccCache::addAccount(const Account& account) {

    for (const Account& a : Accounts) {

        if (a.id == account.id) {

            PromptOK("Account with this ID already exists.");
            return false;
        }
    }

    Accounts.Add(account);
    return saveAccounts();
}


bool AccCache::updateAccount(const String& id, const Account& newAccount) {

    for (int i = 0; i < Accounts.GetCount(); i++) {

        if (Accounts[i].id == id) {

            Accounts[i] = newAccount;
            return saveAccounts();
        }
    }

    return false;
}


bool AccCache::deleteAccount(const String& id) {

    for (int i = 0; i < Accounts.GetCount(); ++i) {

        if (Accounts[i].id == id) {

            Accounts.Remove(i);
            return saveAccounts();
        }
    }

    return false;
}


bool AccCache::saveAccounts() {

    String json = StoreAsJson(Accounts);

    if (SaveFile(accountsFile, json)) {

        Util::print("[ACC] Saved successfully.", true);
        UpdateArrays();
        return true;
    } else {

        Util::print("[ACC] Failed to save.");
        return false;
    }
}


bool AccCache::loadAccounts() { 

    String json = LoadFile(accountsFile);

    if (json.IsEmpty()) {

        Util::print("[ACC] No file found.");
        return false;
    }

    Accounts.Clear();
    
    if (!LoadFromJson(Accounts, json)) {

        Util::print("[ACC] Failed to load from JSON.");
        return false;
    }

    Util::print(Format("[ACC] Loaded %d account(s).", Accounts.GetCount()));
    return true;
}


Account* AccCache::getAccount(const String& id) {

    for (Account& account : Accounts) {

        if (account.id == id) {

            return &account;
        }
    }

    return nullptr;
}


bool AccCache::createAccountsFile() {

    Account ex1 = {"someid", "someone@somewhere.com", "XXXXX-YYYYY-ZZZZZ-11111", "Some notes", "Somebody", "SOMEBODYKEYDPN8CV6M8K65JK456G3HDG6FKN8CNT7BCH685DG2VB61"};
    Account ex2 = {"jasonid", "jason@ohol.com", "WWWWWW-XXXXX-YYYYY-ZZZZZ", "Please don't share my secret account.", "Jason", "JASONKEYDFG4KMD56G3DUMHDFG6FKMGDG23G2RARTJCKHFG6FBKCVM86KGJKBRO"};

    Accounts.Add(ex1);
    Accounts.Add(ex2);

    return saveAccounts();
}


void AccCache::UpdateArrays() {

    Launcher::updateSelectorColumn();
    AccMngr::updateAccountsList();
}