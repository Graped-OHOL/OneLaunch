#include "util.h"
#include "clientSettings.h"
#include "OneLaunch.h"


struct SettingItem {

    String name;
    String* value;
};

static Array<SettingItem> settingsArray;


static void InitializeSettingsArray() {

    if (settingsArray.IsEmpty()) {

        settingsArray.Add({("autoLogin"), &oholSettings.autoLogin});
        settingsArray.Add({("hardToQuitMode"), &oholSettings.hardToQuitMode});
        settingsArray.Add({("skipFPSMeasure"), &oholSettings.skipFPSMeasure});
        settingsArray.Add({("fullscreen"), &oholSettings.fullscreen});
        settingsArray.Add({("borderless"), &oholSettings.borderless});
        settingsArray.Add({("countOnVsync"), &oholSettings.countOnVsync});
        settingsArray.Add({("hideGameUI"), &oholSettings.hideGameUI});
        settingsArray.Add({("showMouseOverHighlights"), &oholSettings.showMouseOverHighlights});
        settingsArray.Add({("eKeyForRightClick"), &oholSettings.eKeyForRightClick});
        settingsArray.Add({("musicOff"), &oholSettings.musicOff});
        settingsArray.Add({("soundEffectsOff"), &oholSettings.soundEffectsOff});
        settingsArray.Add({("useCustomServer"), &oholSettings.useCustomServer});
        settingsArray.Add({("pauseOnMinimize"), &oholSettings.pauseOnMinimize});
        settingsArray.Add({("vogModeOn"), &oholSettings.vogModeOn});

        settingsArray.Add({("screenHeight"), &oholSettings.screenHeight});
        settingsArray.Add({("screenWidth"), &oholSettings.screenWidth});
        settingsArray.Add({("emulatedCursorScale"), &oholSettings.emulatedCursorScale});
        settingsArray.Add({("mouseSpeed"), &oholSettings.mouseSpeed});
        settingsArray.Add({("musicLoudness"), &oholSettings.musicLoudness});
        settingsArray.Add({("soundEffectsLoudness"), &oholSettings.soundEffectsLoudness});
        settingsArray.Add({("soundBufferSize"), &oholSettings.soundBufferSize});
        settingsArray.Add({("soundSampleRate"), &oholSettings.soundSampleRate});
        settingsArray.Add({("customServerAddress"), &oholSettings.customServerAddress});
        settingsArray.Add({("customServerPort"), &oholSettings.customServerPort});
        settingsArray.Add({("serverPassword"), &oholSettings.serverPassword});
        settingsArray.Add({("emotDuration"), &oholSettings.emotDuration});
        settingsArray.Add({("tutorialDone"), &oholSettings.tutorialDone});

        settingsArray.Add({("cursorMode"), &oholSettings.cursorMode});

        settingsArray.Add({("email"), &oholSettings.email});
        settingsArray.Add({("accountKey"), &oholSettings.accountKey});
        settingsArray.Add({("clientName"), &oholSettings.clientName});
    }
}


static String* GetSettingValue(const String& fileName) {

    InitializeSettingsArray();

    for (int i = 0; i < settingsArray.GetCount(); ++i) {

        if (settingsArray[i].name == fileName) {

            return settingsArray[i].value;
        }
    }

    return NULL;
}


void ClientSettings::init() {

    const char* fileNames[] = {

        "autoLogin", "hardToQuitMode", "skipFPSMeasure", "fullscreen", "borderless",
        "countOnVsync", "hideGameUI", "showMouseOverHighlights", "eKeyForRightClick",
        "musicOff", "soundEffectsOff", "useCustomServer", "pauseOnMinimize", "vogModeOn",
        "screenHeight", "screenWidth", "emulatedCursorScale", "mouseSpeed",
        "musicLoudness", "soundEffectsLoudness", "soundBufferSize", "soundSampleRate",
        "customServerAddress", "customServerPort", "serverPassword", "emotDuration",
        "tutorialDone", "cursorMode", "email", "accountKey", "clientName"
    };

    debugQ.Add("[SET] Loaded OHOL Settings");

    for (int i = 0; i < __countof(fileNames); ++i) {

        String fileName = fileNames[i];

        if (fileName == "clientName" && !config.yumhack) continue;

        String filePath = "settings/" + fileName + ".ini";

        if (FileExists(filePath)) {

            String value = LoadFile(filePath);
            String* setting = GetSettingValue(fileName);

            if (setting) *setting = value;

            if (fileName != "email" && fileName != "accountKey" && fileName != "clientName")
                debugQ.Add("[SET]  -" + fileName + " = " + value);
        } else {

            String defaultValue = "0";

            SaveFile(filePath, defaultValue);

            String* setting = GetSettingValue(fileName);

            if (setting) *setting = defaultValue;

            if (fileName != "email" && fileName != "accountKey" && fileName != "clientName") {

                debugQ.Add("[INS] Created " + fileName);
                debugQ.Add("[SET]  -" + fileName + " = " + defaultValue);
            }
        }
    }
}


bool ClientSettings::updateSetting(const String& settingName, const String& newValue) {

    String filePath = "settings/" + settingName + ".ini";
    String* setting = GetSettingValue(settingName);

    if (!setting) return false;
    
    *setting = newValue;

    if (settingName != "email" && settingName != "accountKey" && settingName != "clientName")
        Util::print("[SET] Saving OHOL Setting : " + settingName, true);

    return SaveFile(filePath, newValue);
}


void ClientSettings::setToDefault() {

    static const struct {

        const char* setting;
        const char* value;

    } defaultSettings[] = {

        {"autoLogin", "0"}, {"hardToQuitMode", "0"}, {"skipFPSMeasure", "0"},
        {"fullscreen", "1"}, {"borderless", "0"}, {"countOnVsync", "1"},
        {"hideGameUI", "0"}, {"showMouseOverHighlights", "1"}, {"eKeyForRightClick", "0"},
        {"musicOff", "0"}, {"soundEffectsOff", "0"}, {"useCustomServer", "0"},
        {"pauseOnMinimize", "0"}, {"vogModeOn", "0"}, {"screenHeight", "720"},
        {"screenWidth", "1280"}, {"emulatedCursorScale", "1.0"}, {"mouseSpeed", "1.0"},
        {"musicLoudness", "1.0"}, {"soundEffectsLoudness", "1.0"}, {"soundBufferSize", "1024"},
        {"soundSampleRate", "44100"}, {"customServerAddress", "localhost"}, {"customServerPort", "8005"},
        {"serverPassword", "testPassword"}, {"emotDuration", "10"}, {"tutorialDone", "0"},
        {"cursorMode", "0"}, {"email", "NOEMAIL"}, {"key", "NOKEY"}
    };

    for (int i = 0; i < __countof(defaultSettings); ++i) {

        updateSetting(defaultSettings[i].setting, defaultSettings[i].value);
    }

    if (config.yumhack)
        updateSetting("clientName", "NONAME");

    Util::print("[SET] Game client settings reset to default");
}