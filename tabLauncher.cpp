#include "util.h"
#include "tabLauncher.h"
#include "gameLauncher.h"
#include "OneLaunch.h"


static int selShowCol = 0;


void Launcher::init() {

    tabL->ListBtn.WhenPush = [=] { onListBtnPressed(); };
    tabL->LaunchBtn.WhenPush = [=] { onLaunchBtnPressed(); };
    tabL->LaunchAllBtn.WhenPush = [=] { onLaunchAllBtnPressed(); };
    
    tabL->AccountSelectorList.AddColumn("Accounts");
    tabL->AccountSelectorList.MultiSelect();
}


void Launcher::initConsole() {

    int linesNeeded = (tabL->debugConsole.GetSize().cy / tabL->debugConsole.GetFont().GetHeight()) + 1;
    String padding;

    padding.Cat('\n', linesNeeded);
    tabL->debugConsole.SetData(padding);
}


void Launcher::debugPrint(const String& newText, bool debugOnly) {

    if (debugOnly && !config.debug) {

        return;
    }

    String currentText = tabL->debugConsole.GetData();
    String textToAppend = currentText.IsEmpty() ? newText : currentText + "\n" + newText;

    tabL->debugConsole.SetData(textToAppend);

    int totalLines = tabL->debugConsole.GetLineCount()+3;
    int lineHeight = tabL->debugConsole.GetFont().GetHeight();
    int contentHeight = totalLines * lineHeight;

    Size sz = tabL->debugConsole.GetSize();

    int maxScrollY = contentHeight - sz.cy;

    if (maxScrollY < 0) {

        maxScrollY = 0;
    }

    Point scrollPos = tabL->debugConsole.GetScrollPos();
    scrollPos.y = maxScrollY+1;
    tabL->debugConsole.SetScrollPos(scrollPos);
}


void Launcher::onLaunchBtnPressed() {

    debugPrint("[LAU] Launch button pressed", true);
    Vector<int> selectedIndices = getSelectedAccounts();
    
    if (selectedIndices.IsEmpty()) {

        PromptOK("Please select at least one account.");
        debugPrint("[LAU] No account selected.");
        return;
    }
    
    const Array<Account>& accounts = AccCache::getAccounts();

    if (selectedIndices.GetCount() == 1) {

        launchSingleGame(accounts[selectedIndices[0]]);
    } else {

        debugPrint("[LAU] Launching all selected accounts");
        GameLauncher::launchAllGames(selectedIndices);
    }
}


void Launcher::launchSingleGame(const Account& account) {

    if (GameLauncher::launchGame(account)) {

        debugPrint("[LAU] Game launched successfully for account: " + account.id, true);
    } else {

        debugPrint("[LAU] Failed to launch game for account: " + account.id, true);
    }
}


void Launcher::onLaunchAllBtnPressed() {

    debugPrint("[LAU] Launch all button pressed", true);
    
    const Array<Account>& allAccounts = AccCache::getAccounts();
    Vector<int> allIndices;

    allIndices.Reserve(allAccounts.GetCount());
    
    for (int i = 0; i < allAccounts.GetCount(); ++i) {

        allIndices.Add(i);
    }
    
    debugPrint("[LAU] Launching all accounts");
    GameLauncher::launchAllGames(allIndices);
}


Vector<int> Launcher::getSelectedAccounts() {

    Vector<int> selectedIndices;

    for (int i = 0; i < tabL->AccountSelectorList.GetCount(); ++i) {

        if (tabL->AccountSelectorList.IsSelected(i)) {

            selectedIndices.Add(i);
        }
    }

    return selectedIndices;
}


String Launcher::getSelectorColumnName(int index) {

    static const char* columnNames[] = {"IDs", "Emails", "Names", "Unknown"};
    return columnNames[min(index, 3)];
}


void Launcher::onListBtnPressed() {

    toggleSelectorColumn();
}


void Launcher::toggleSelectorColumn() {

    selShowCol = (selShowCol + 1) % 3;
    int nextCol = (selShowCol + 1) % 3;

    String changeTo = getSelectorColumnName(selShowCol);
    String newListBtnLbl = getSelectorColumnName(nextCol);

    tabL->ListBtn.SetLabel("List : " + newListBtnLbl);

    debugPrint("[LAU] Selector showing : " + changeTo, true);

    updateSelectorColumn();
}


void Launcher::updateSelectorColumn() {

    if (isLoading || configChanged) {

        selShowCol = config.selectorData == "IDs" ? 0 :
                     config.selectorData == "Emails" ? 1 :
                     config.selectorData == "Names" ? 2 : 0;
    }

    tabL->AccountSelectorList.Clear();

    for (const Account& acc : AccCache::getAccounts()) {

        tabL->AccountSelectorList.Add(selShowCol == 0 ? acc.id :
                                      selShowCol == 1 ? acc.email :
                                      acc.clientName);
    }
}