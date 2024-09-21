#ifndef _tabCtrl_h
#define _tabCtrl_h


#include <CtrlLib/CtrlLib.h>


using namespace Upp;


class Tabs {
    public:

        static void init();

    private:

        static void switchTab(int tabIndex);
        static Button* getTabButton(int index);

};


#endif