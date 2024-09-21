#include "util.h"
#include "gameLauncher.h"
#include "OneLaunch.h"


bool GameLauncher::launchGame(const Account& account) {

    if (!updateAccountSettings(account)) {

        Util::print(Format("[LAU] Failed setting swap for : %s", account.id));
        return false;
    }

    if (config.yumhack) {

        if (!updateYumhackKey(account.yumhackKey)) {

            Util::print(Format("[LAU] Failed yhkey swap for : %s", account.id));
            return false;
        }
    }

    if (!launchGameProcess(config.exe)) {

        Util::print(Format("[LAU] Failed launching game for: %s", account.id));
        return false;
    }

    Util::print(Format("[LAU] Game launched for : %s", account.id));
    return true;
}


void GameLauncher::launchAllGames(const Vector<int>& selectedIndices) {

    const Array<Account>& accounts = AccCache::getAccounts();

    for (int index : selectedIndices) {

        if (index >= 0 && index < accounts.GetCount()) {

            const Account& account = accounts[index];

            if (launchGame(account)) {

                Sleep(config.delay * 1000);
            }
        }
    }
}


bool GameLauncher::updateAccountSettings(const Account& account) {

    return ClientSettings::updateSetting("email", account.email) &&
           ClientSettings::updateSetting("accountKey", account.key) &&
           (!config.yumhack || ClientSettings::updateSetting("clientName", account.clientName));

}


bool GameLauncher::updateYumhackKey(const String& yumhackKey) {

    String configPath = GetExeDirFile("yumlife.cfg");
    String configContent = LoadFile(configPath);
    
    int pos = configContent.Find("yumhack_key = ");

    if (pos >= 0) {

        int endPos = configContent.Find("\n", pos);

        if (endPos < 0) endPos = configContent.GetLength();

        String newLine = Format("yumhack_key = %s\n", yumhackKey);
        configContent.Remove(pos, endPos - pos);
        configContent.Insert(pos, newLine);

        return SaveFile(configPath, configContent);
    }

    Util::print("[LAU] Yumhack key not found in config file");
    return false;
}


bool GameLauncher::launchGameProcess(const String& exeName) {

    String exePath = GetExeDirFile(exeName);

    if (!FileExists(exePath)) {

        Util::print(Format("[LAU] Game executable not found: %s", exeName));
        return false;
    }

    HINSTANCE result = ShellExecute(NULL, "open", exePath.ToStd().c_str(), NULL, NULL, SW_SHOWNORMAL);
    
    if ((intptr_t)result <= 32) {

        Util::print(Format("[LAU] Failed to execute %s. Error code: %d", exeName, (int)(intptr_t)result), true);
        return false;
    }
    
    Util::print(Format("[LAU] Game launched successfully: %s", exeName), true);
    return true;
}