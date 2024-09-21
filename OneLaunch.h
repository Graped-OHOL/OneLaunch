#ifndef _OneLaunch_OneLaunch_h
#define _OneLaunch_OneLaunch_h


#include <CtrlLib/CtrlLib.h>
#include <Core/Core.h>


using namespace Upp;


#define LAYOUTFILE <OneLaunch/OneLaunch.lay>
#include <CtrlCore/lay.h>


class AccCache;
class ClientSettings;
class Config;
class GameLauncher;
class AccMngr;
class Tabs;
class Launcher;
class Settings;
class Util;


#include "config.h"
#include "clientSettings.h"


class UIDlg : public WithUI<TopWindow> {
    public:

        UIDlg() { CtrlLayout(*this, ""); }
};


class AccountManagerDlg : public WithAccountManager<TopWindow> {
    public:

        AccountManagerDlg() { CtrlLayout(*this, ""); }
};


class SettingsDlg : public WithSettings<TopWindow> {
    public:

        SettingsDlg() { CtrlLayout(*this, ""); }
};


class LauncherDlg : public WithLauncher<TopWindow> {
    public:

        LauncherDlg() { CtrlLayout(*this, ""); }
};



void initGUI();


extern UIDlg* mainWindow;


extern LauncherDlg* tabL;
extern AccountManagerDlg* tabA;
extern SettingsDlg* tabS;


extern Vector<String> debugQ;


extern Config config;
extern OHOLSettings oholSettings;


extern int olVersion;
extern int olSubversion;
extern String olVersionStr;


extern bool isLoading;
extern bool configChanged;


#endif