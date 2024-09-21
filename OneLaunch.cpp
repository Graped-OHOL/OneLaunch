#include "util.h"
#include "accCache.h"
#include "tabCtrl.h"
#include "OneLaunch.h"


void initGUI() {

    debugQ.Add(Format("[INI] Initializing OneLaunch v%s", olVersionStr));

    mainWindow = new UIDlg();
    tabL = new LauncherDlg();
    tabA = new AccountManagerDlg();
    tabS = new SettingsDlg();

    if (!Util::createOLDirectory("onelaunch") || !Util::createOLDirectory("settings")) {

        Util::print("[ERR] Failed to create necessary directories. Exiting.");
        return;
    }

    OLConfig::load();
    ClientSettings::init();

    mainWindow->Title("OneLaunch");
    mainWindow->version = olVersionStr;
    mainWindow->Icon(StreamRaster::LoadFileAny(GetExeDirFile("rocket.ico")));

    Util::processDebugQueue();

    AccCache::init();
    Tabs::init();
    AccCache::UpdateArrays();

    Util::print("[INF] Loading Complete!", true);
    Util::print(Format("[INF] Welcome to OneLaunch v%s!", olVersionStr));

    isLoading = false;
    
    mainWindow->Run();
}