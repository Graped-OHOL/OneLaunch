#ifndef _config_h
#define _config_h


#include <Core/Core.h>


using namespace Upp;


struct Config {

    int yumhack;
    int debug;
    String exe;
    int delay;
    String selectorData;

    void Jsonize(JsonIO& json) {

        json
            ("yumhack", yumhack)
            ("debug", debug)
            ("exe", exe)
            ("delay", delay)
            ("selectorData", selectorData);

    }

};


class OLConfig {

    public:
        static void load();
        static void save();
        static void setToDefault();

    private:
        static void createDefault();

};


#endif // _config_config_h