#include "util.h"
#include "tabCtrl.h"
#include "tabLauncher.h"
#include "tabAccManager.h"
#include "tabSettings.h"
#include "OneLaunch.h"


void Tabs::init() {

    Launcher::init();
    AccMngr::init();
    Settings::init();

    mainWindow->tabs.Add(*tabL, "Launcher");
    mainWindow->tabs.Add(*tabA, "Account Manager");
    mainWindow->tabs.Add(*tabS, "Settings");
    mainWindow->tabs.Set(0);

    mainWindow->LauncherTabBtn.SetStyle(Button::StyleLeftEdge());
    mainWindow->LauncherTabBtnFrame.Background(Color(0, 160, 225));

    mainWindow->LauncherTabBtn.WhenPush = [=] { switchTab(0); };
    mainWindow->AccountManagerTabBtn.WhenPush = [=] { switchTab(1); };
    mainWindow->SettingsTabBtn.WhenPush = [=] { switchTab(2); };
}


void Tabs::switchTab(int tabIndex) {
    
    for (int i = 0; i < 3; ++i) {

        getTabButton(i)->SetStyle(Button::StyleNormal());
        getTabButtonFrame(i)->Background(Color(114, 114, 114));
    }

    if (tabIndex >= 0 && tabIndex < 3) {

        mainWindow->tabs.Set(tabIndex);
        getTabButton(tabIndex)->SetStyle(Button::StyleLeftEdge());
        getTabButtonFrame(tabIndex)->Background(Color(0, 160, 225));
    }
}


Button* Tabs::getTabButton(int index) {

    switch (index) {
        
        case 0: return &mainWindow->LauncherTabBtn;
        case 1: return &mainWindow->AccountManagerTabBtn;
        case 2: return &mainWindow->SettingsTabBtn;
        default: return nullptr;
    }
}
RichTextCtrl* Tabs::getTabButtonFrame(int index) {

    switch (index) {
        
        case 0: return &mainWindow->LauncherTabBtnFrame;
        case 1: return &mainWindow->AccountManagerTabBtnFrame;
        case 2: return &mainWindow->SettingsTabBtnFrame;
        default: return nullptr;
    }
}