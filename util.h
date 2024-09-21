#ifndef _util_h
#define _util_h


#include <Core/Core.h>


using namespace Upp;


class Util {
    public:

        static bool createOLDirectory(const String& path);
        static void print(const String& newText, bool debugOnly = false);
        static void processDebugQueue();

};


#endif