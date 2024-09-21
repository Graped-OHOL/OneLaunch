#ifndef _AccCache_h_
#define _AccCache_h_


#include <Core/Core.h>


using namespace Upp;


struct Account {

    String id;
    String email;
    String key;
    String notes;
    String clientName;
    String yumhackKey;

    void Jsonize(JsonIO& json) {

        json
            ("id", id)
            ("email", email)
            ("key", key)
            ("notes", notes)
            ("clientName", clientName)
            ("yumhackKey", yumhackKey);

    }

};


class AccCache {
    public:

        static void init();
        static bool addAccount(const Account& account);
        static bool updateAccount(const String& id, const Account& newAccount);
        static bool deleteAccount(const String& id);
        static bool loadAccounts();
        static bool saveAccounts();
        static const Array<Account>& getAccounts();
        static Account* getAccount(const String& id);
        static void UpdateArrays();

    private:

        static Array<Account> Accounts;
        static const String accountsFile;
        static bool createAccountsFile();

};


#endif