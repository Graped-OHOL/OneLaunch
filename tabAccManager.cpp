#include "util.h"
#include "tabAccManager.h"
#include "accCache.h"
#include "OneLaunch.h"


static bool inEditMode = false;
static String editingAccID;


void AccMngr::init() {

    tabA->EditBtn.WhenPush = [=] { onEditBtnPressed(); };
    tabA->DelBtn.WhenPush = [=] { onDelBtnPressed(); };
    tabA->SaveCreateBtn.WhenPush = [=] { onSaveCreateBtnPressed(); };

    tabA->AccountsList.AddColumn("ID", 5).Sorting();
    tabA->AccountsList.AddColumn("EMail", 15).Sorting();
    tabA->AccountsList.AddColumn("Key", 5).Sorting();
    tabA->AccountsList.AddColumn("Notes", 10).Sorting();

    if(config.yumhack) {

        tabA->AccountsList.AddColumn("CName", 5).Sorting();
        tabA->AccountsList.AddColumn("YHKey", 5).Sorting();
    }

    toggleYumhackFields(config.yumhack == 1);
}


void AccMngr::onEditBtnPressed() {

    if (inEditMode) {

        PromptOK("Please press save before trying to edit another account.");
        return;
    }

    inEditMode = true;

    int rowIndex = tabA->AccountsList.GetCursor();
    Value accIdVal = tabA->AccountsList.Get(rowIndex, 0);
    editingAccID = accIdVal.ToString();

    tabA->SaveCreateBtn.SetLabel("Save");
    tabA->AccountEditorLbl.SetLabel("Editing account : " + editingAccID);

    if(Account* acc = AccCache::getAccount(editingAccID)) {

        tabA->accountId.SetText(acc->id);
        tabA->email.SetText(acc->email);
        tabA->accountKey.SetText(acc->key);
        tabA->accountNotes.SetText(acc->notes);
        tabA->clientName.SetText(acc->clientName);
        tabA->yumhackKey.SetText(acc->yumhackKey);
    }
}


void AccMngr::onDelBtnPressed() {

    int rowIndex = tabA->AccountsList.GetCursor();
    Value accIdVal = tabA->AccountsList.Get(rowIndex, 0);
    String accID = accIdVal.ToString();

    if (PromptYesNo("Are you sure you want to delete this account?")) {

        if (AccCache::deleteAccount(accID)) {

            Util::print("[ACC] Deleted account : " + accID, true);
        } else {

            Util::print("[ACC] Failed to delete account : " + accID, true);
        }
    } else {

        Util::print("[ACC] Cancelled deletion for : " + accID, true);
    }
}


void AccMngr::clearEditorFields() {

    tabA->accountId.Clear();
    tabA->email.Clear();
    tabA->accountKey.Clear();
    tabA->accountNotes.Clear();
    tabA->clientName.Clear();
    tabA->yumhackKey.Clear();
}


void AccMngr::onSaveCreateBtnPressed() {

    Account acc;
    acc.id = tabA->accountId.GetText().ToString();
    acc.email = tabA->email.GetText().ToString();
    acc.key = tabA->accountKey.GetText().ToString();
    acc.notes = tabA->accountNotes.GetText().ToString();
    acc.clientName = tabA->clientName.GetText().ToString();
    acc.yumhackKey = tabA->yumhackKey.GetText().ToString();

    bool success;

    if(inEditMode) {

        success = AccCache::updateAccount(editingAccID, acc);
        inEditMode = false;
        tabA->SaveCreateBtn.SetLabel("Create");
        tabA->AccountEditorLbl.SetLabel("Create a new account");
        editingAccID.Clear();
    } else {

        success = AccCache::addAccount(acc);
    }

    if(success) {

        clearEditorFields();
        Util::print(Format("[ACC] Account %s: %s", inEditMode ? "updated" : "created", acc.id), true);
    } else {

        Util::print(Format("[ACC] Failed to %s account: %s", inEditMode ? "update" : "create", acc.id), true);
    }
}


void AccMngr::updateAccountsList() {

    tabA->AccountsList.Clear();

    for (const Account& acc : AccCache::getAccounts()) {

        Vector<Value> accountVector;
        accountVector << acc.id << acc.email << acc.key << acc.notes;

        if(config.yumhack) {

            accountVector << acc.clientName << acc.yumhackKey;
        }

        tabA->AccountsList.Add(accountVector);
    }
}


void AccMngr::toggleYumhackFields(bool yumhackEnabled) {

    tabA->ClientNameLbl.Show(yumhackEnabled);
    tabA->clientName.Show(yumhackEnabled);
    tabA->YumhackKeyLbl.Show(yumhackEnabled);
    tabA->yumhackKey.Show(yumhackEnabled);
}