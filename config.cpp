#include "util.h"
#include "config.h"
#include "OneLaunch.h"


void OLConfig::load() {

    String filePath = GetExeDirFile("onelaunch/config.json");

    if (FileExists(filePath)) {

        String jsonData = LoadFile(filePath);
        Value parsedJson = ParseJSON(jsonData);
        
        if (!IsNull(parsedJson)) {

            LoadFromJson(config, jsonData);

            debugQ.Add("[CFG] Loaded Config");
            debugQ.Add(Format("[CFG]  -yumhack      = %d", config.yumhack));
            debugQ.Add(Format("[CFG]  -debug        = %d", config.debug));
            debugQ.Add(Format("[CFG]  -exe          = %s", config.exe));
            debugQ.Add(Format("[CFG]  -delay        = %d seconds", config.delay));
            debugQ.Add(Format("[CFG]  -selectorData = %s", config.selectorData));
        } else {

            debugQ.Add("[CFG] Failed to parse JSON.");
        }
    } else {

        debugQ.Add("[INS] Creating config file.");
        createDefault();
    }
}


void OLConfig::save() {

    String filePath = GetExeDirFile("onelaunch/config.json");

    if (StoreAsJsonFile(config, filePath)) {

        if (isLoading) {

            debugQ.Add("[CFG] Saved to file.");

        } else {

            Util::print("[CFG] Saved to file.", true);
        }
    } else {

        Util::print("[CFG] Failed to save config file.", true);
    }
}


void OLConfig::setToDefault() {

    config.yumhack = 0;
    config.debug = 0;
    config.exe = "OneLife.exe";
    config.delay = 3;
    config.selectorData = "Emails";

    save();
}


void OLConfig::createDefault() {

    String folderPath = GetExeDirFile("onelaunch");
    
    if (!DirectoryExists(folderPath)) {
        
        RealizeDirectory(folderPath);
    }

    setToDefault();

    debugQ.Add("[INS] Default config created.");
}