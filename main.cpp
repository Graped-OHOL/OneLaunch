#include "OneLaunch.h"


bool isLoading = true;
bool configChanged = false;
int olVersion = 1;
int olSubversion = 0;
String olVersionStr = Format("%d.%d", olVersion, olSubversion);

Vector<String> debugQ;


UIDlg* mainWindow = nullptr;
LauncherDlg* tabL = nullptr;
AccountManagerDlg* tabA = nullptr;
SettingsDlg* tabS = nullptr;
Config config;
OHOLSettings oholSettings;


GUI_APP_MAIN
{

    initGUI();
}