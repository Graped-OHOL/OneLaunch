#ifndef _gameLauncher_h
#define _gameLauncher_h


#include <Core/Core.h>


using namespace Upp;


#include "accCache.h"


class GameLauncher {
    public:

        static bool launchGame(const Account& account);
        static void launchAllGames(const Vector<int>& selectedIndices);

    private:

        static bool updateAccountSettings(const Account& account);
        static bool updateYumhackKey(const String& yumhackKey);
        static bool launchGameProcess(const String& exeName);
        
};


#endif