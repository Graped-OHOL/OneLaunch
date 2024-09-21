#ifndef _tabLauncher_h
#define _tabLauncher_h


#include <CtrlLib/CtrlLib.h>
#include "accCache.h"


using namespace Upp;


class Launcher {
    public:

        static void init();
        static void initConsole();
        static void debugPrint(const String& newText, bool debugOnly = false);
        static void updateSelectorColumn();

    private:

        static void onListBtnPressed();
        static void onLaunchBtnPressed();
        static void launchSingleGame(const Account& account);
        static void onLaunchAllBtnPressed();
        static Vector<int> getSelectedAccounts();
        static String getSelectorColumnName(int index);
        static void toggleSelectorColumn();

};


#endif