#include "util.h"
#include "tabSettings.h"
#include "tabAccManager.h"
#include "tabLauncher.h"
#include "OneLaunch.h"


void Settings::setClientSettingsElements() {

    #define SET_OPTION(name) tabS->name.Set(atoi(oholSettings.name))
    #define SET_TEXT(name) tabS->name.SetText(oholSettings.name)

    SET_OPTION(autoLogin);
    SET_OPTION(hardToQuitMode);
    SET_OPTION(skipFPSMeasure);
    SET_OPTION(fullscreen);
    SET_OPTION(borderless);
    SET_OPTION(countOnVsync);
    SET_OPTION(hideGameUI);
    SET_OPTION(showMouseOverHighlights);
    SET_OPTION(eKeyForRightClick);
    SET_OPTION(musicOff);
    SET_OPTION(soundEffectsOff);
    SET_OPTION(useCustomServer);
    SET_OPTION(pauseOnMinimize);
    SET_OPTION(vogModeOn);

    SET_TEXT(screenHeight);
    SET_TEXT(screenWidth);
    SET_TEXT(emulatedCursorScale);
    SET_TEXT(mouseSpeed);
    SET_TEXT(musicLoudness);
    SET_TEXT(soundEffectsLoudness);
    SET_TEXT(soundBufferSize);
    SET_TEXT(soundSampleRate);
    SET_TEXT(customServerAddress);
    SET_TEXT(customServerPort);
    SET_TEXT(serverPassword);
    SET_TEXT(emotDuration);
    SET_TEXT(tutorialDone);

    tabS->cursorMode.SetIndex(atoi(oholSettings.cursorMode));

    #undef SET_OPTION
    #undef SET_TEXT
}


void Settings::setLauncherSettingsElements() {

    tabS->yumhack.Set(config.yumhack);
    tabS->debugMode.Set(config.debug);
    tabS->exeToRun.SetText(config.exe);
    tabS->launchDelay.SetText(AsString(config.delay));
    tabS->selectorColumn.SetIndex(config.selectorData == "IDs" ? 0 : 
                                  config.selectorData == "Emails" ? 1 : 2);
}


void Settings::init() {

    tabS->defaultSettingsBtn.WhenPush = [=] { onDefaultSettingsBtnPressed(); };

    tabS->cursorMode.Add("Native").Add("Drawn").Add("Both").SetDropLines(3);
    tabS->selectorColumn.Add("IDs").Add("Emails").Add("Names").SetDropLines(3);

    #define HOOK_OPTION(name) tabS->name << [=] { onOptionChanged(tabS->name, #name); }
    #define HOOK_EDITFIELD(name) \
        tabS->name.WhenLostFocus << [=] { onEditFieldChanged(tabS->name, #name); }; \
        tabS->name.WhenEnter = [=] { onEditFieldChanged(tabS->name, #name); }

    HOOK_OPTION(yumhack);
    HOOK_OPTION(debugMode);
    HOOK_EDITFIELD(exeToRun);
    HOOK_EDITFIELD(launchDelay);
    tabS->selectorColumn.WhenSelectionChanged << [=] { onDropListChanged(tabS->selectorColumn, "selectorColumn"); };

    HOOK_OPTION(autoLogin);
    HOOK_OPTION(hardToQuitMode);
    HOOK_OPTION(skipFPSMeasure);
    HOOK_OPTION(fullscreen);
    HOOK_OPTION(borderless);
    HOOK_OPTION(countOnVsync);
    HOOK_OPTION(hideGameUI);
    HOOK_OPTION(showMouseOverHighlights);
    HOOK_OPTION(eKeyForRightClick);
    HOOK_OPTION(musicOff);
    HOOK_OPTION(soundEffectsOff);
    HOOK_OPTION(useCustomServer);
    HOOK_OPTION(pauseOnMinimize);
    HOOK_OPTION(vogModeOn);

    HOOK_EDITFIELD(screenHeight);
    HOOK_EDITFIELD(screenWidth);
    HOOK_EDITFIELD(emulatedCursorScale);
    HOOK_EDITFIELD(mouseSpeed);
    HOOK_EDITFIELD(musicLoudness);
    HOOK_EDITFIELD(soundEffectsLoudness);
    HOOK_EDITFIELD(soundBufferSize);
    HOOK_EDITFIELD(soundSampleRate);
    HOOK_EDITFIELD(customServerAddress);
    HOOK_EDITFIELD(customServerPort);
    HOOK_EDITFIELD(serverPassword);
    HOOK_EDITFIELD(emotDuration);
    HOOK_EDITFIELD(tutorialDone);

    tabS->cursorMode.WhenSelectionChanged << [=] { onDropListChanged(tabS->cursorMode, "cursorMode"); };

    #undef HOOK_OPTION
    #undef HOOK_EDITFIELD

    setClientSettingsElements();
    setLauncherSettingsElements();
}


void Settings::onDefaultSettingsBtnPressed() {

    Util::print("[SET] Default Settings button pressed.", true);
    ClientSettings::setToDefault();
    setClientSettingsElements();
    OLConfig::setToDefault();
    setLauncherSettingsElements();
}


void Settings::onOptionChanged(Option& option, const String& optionName) {

    option.Set(option.Get() ? 1 : 0);

    Util::print("[SET] " + optionName + " set to : " + AsString(option.Get()), true);

    if(optionName == "yumhack") {

        config.yumhack = option.Get() ? 1 : 0;
        OLConfig::save();
        AccMngr::toggleYumhackFields(config.yumhack);

    } else if(optionName == "debugMode") {

        config.debug = option.Get() ? 1 : 0;
        OLConfig::save();

    } else {

        ClientSettings::updateSetting(optionName, option.Get() ? "1" : "0");
    }
}


void Settings::onEditFieldChanged(EditField& editField, const String& fieldName) {

    String fieldText = editField.GetText().ToString();

    Util::print("[SET] " + fieldName + " set to : " + fieldText, true);

    if(fieldName == "exeToRun") {

        config.exe = fieldText;
        OLConfig::save();

    } else if(fieldName == "launchDelay") {

        config.delay = atoi(fieldText);
        OLConfig::save();
    } else {

        ClientSettings::updateSetting(fieldName, fieldText);
    }
}


void Settings::onDropListChanged(DropList& dropList, const String& listName) {

    String newSelection = dropList.GetValue().ToString();

    Util::print("[SET] " + listName + " set to : " + newSelection, true);

    if(listName == "selectorColumn") {

        config.selectorData = newSelection;
        OLConfig::save();

        configChanged = true;
        Launcher::updateSelectorColumn();
    } else {

        ClientSettings::updateSetting(listName, newSelection == "Native" ? "0" : 
                                                newSelection == "Drawn" ? "1" : "2");
    }
}