#include "util.h"
#include "tabLauncher.h"
#include "OneLaunch.h"


bool Util::createOLDirectory(const String& path) {

    if (DirectoryExists(path)) {

        return true;
    }

    if (RealizeDirectory(path)) {

        if (path == "settings") {

            PromptOK("Couldn't find settings folder, OneLaunch may not be installed properly.");
        }

        debugQ.Add(Format("[INS] Created Directory : %s", path));
        return true;
    } else {

        debugQ.Add(Format("[INS] Failed to create directory : %s", path));
        return false;
    }
}


void Util::print(const String& newText, bool debugOnly) {

    Launcher::debugPrint(newText, debugOnly);
}


void Util::processDebugQueue() {

    for (const String& entry : debugQ) {

        Launcher::debugPrint(entry, true);
    }
    
    debugQ.Clear();
}