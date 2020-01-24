
#if ! defined ( FLAGS_H )
#define FLAGS_H

struct flagsData {

    bool e;
    bool g;
    bool t;

    int time;
    std::string graphFilename;

    flagsData() {
        e = 0;
        g = 0;
        t = 0;
        time = 0;
    }
};
#endif
