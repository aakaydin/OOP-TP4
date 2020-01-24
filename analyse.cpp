
#include <iostream>
#include "Flags.h"
#include "LogData.h"

using namespace std;

flagsData parseArgs(int argc, char* argv[]);

int main( int argc, char* argv[] )
{


    if(argc > 1) {

        string filename = argv[argc-1];
        flagsData f = parseArgs(argc, argv);

        LogData log( filename,f );

        log.statistics();

    } else {
        // printMessage("You must provide a log file name as an argument!");
    }

    return 0;
}

flagsData parseArgs(int argc, char* argv[]) {
    flagsData f;

    for( int i=1; i<argc-1;i++ )
    {
        string s = argv[i];

        if( s == "-e" ) f.e = 1;

        if( s == "-t" )
        {
            f.t = 1;
            f.time = stoi(argv[++i]);
        }
        if( s == "-g" )
        {
            f.g = 1;
            f.graphFilename = argv[++i];
        }
    }
    return f;
}
