#ifndef _tabSettings_h
#define _tabSettings_h


#include <CtrlLib/CtrlLib.h>


using namespace Upp;


class Settings {
    public:

        static void init();

    private:

        static void setClientSettingsElements();
        static void setLauncherSettingsElements();
        static void onDefaultSettingsBtnPressed();
        static void onOptionChanged(Option& option, const String& optionName);
        static void onEditFieldChanged(EditField& editField, const String& fieldName);
        static void onDropListChanged(DropList& dropList, const String& listName);

};


#endif