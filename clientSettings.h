#ifndef _clientSettings_h
#define _clientSettings_h


#include <Core/Core.h>


using namespace Upp;


struct OHOLSettings {

    String autoLogin, hardToQuitMode, skipFPSMeasure, fullscreen, borderless,
           countOnVsync, hideGameUI, showMouseOverHighlights, eKeyForRightClick,
           musicOff, soundEffectsOff, useCustomServer, pauseOnMinimize, vogModeOn,
           screenHeight, screenWidth, emulatedCursorScale, mouseSpeed,
           musicLoudness, soundEffectsLoudness, soundBufferSize, soundSampleRate,
           customServerAddress, customServerPort, serverPassword, emotDuration,
           tutorialDone, cursorMode, email, accountKey, clientName;

};


class ClientSettings {
    public:

        static void init();
        static bool updateSetting(const String& settingName, const String& newValue);
        static void setToDefault();

};


#endif