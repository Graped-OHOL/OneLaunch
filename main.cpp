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

    Color buttonBG = Color(51, 51, 51);
    Color buttonCLK = Color(0, 180, 225);
    Color highlight = Color(0, 160, 225);

    
    SColorHighlight_Write(highlight);

    Button::Style normBtn = Button::StyleNormal();
    normBtn.look[0] = buttonBG;
    normBtn.look[1] = highlight;
    normBtn.look[2] = buttonCLK;
    normBtn.textcolor[2] = Black();
    normBtn.focus_use_ok = false; 

    Button::Style tabBtns = Button::StyleNormal();
    tabBtns.look[0] = buttonBG;
    tabBtns.look[1] = buttonBG;
    tabBtns.look[2] = buttonCLK;
    tabBtns.textcolor[2] = Black();
    tabBtns.focus_use_ok = false;
    

    DropList::Style d = DropList::StyleDefault();
    d.paper = highlight;
    d.look[1] = highlight;

    Button::StyleNormal().Write() = normBtn;
    Button::StyleLeftEdge().Write() = tabBtns;
    DropList::StyleDefault().Write() = d;

    initGUI();
}