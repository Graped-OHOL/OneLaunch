#ifndef _tabAccManager_h
#define _tabAccManager_h


#include <CtrlLib/CtrlLib.h>


using namespace Upp;


class AccMngr {
    public:

        static void init();
        static void updateAccountsList();
        static void toggleYumhackFields(bool yumhackEnabled);

    private:

        static void onEditBtnPressed();
        static void onDelBtnPressed();
        static void clearEditorFields();
        static void onSaveCreateBtnPressed();
        
};


#endif