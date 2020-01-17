#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;

struct visits{

    unordered_map<string,int>  visitors;
    int hits;

};






int main( int argc, char* argv[] )
{

    string filename = argv[argc-1];

    bool e = false;
    bool t = false;
    bool g = false;

    int time = 0;
    string graphName = "";

    for( int i=0; i<argc;i++) cout << argv[i] << endl;

    for( int i=1; i<argc-1;i++ )
    {
        string s = argv[i];

        if( s == "-e" ) e = true;

        if( s == "-t" )
        {
            t = true;
            time = stoi(argv[++i]);
        }
        if( s == "-g" )
        {
            g = true;
            graphName = argv[++i];
        }
    }



    unordered_map<string,visits> logData;

    vector<string> input(9);

    ifstream stream;
    stream.open(filename);


    while( !stream.eof() )
    {


        // IP
        getline(stream,input[0],' ');
        // User Logname
        getline(stream,input[1],' ');
        // Authenticated User
        getline(stream,input[2],' ');
        // Date
        getline(stream,input[3],'[');
        getline(stream,input[3],']');
        // Request
        getline(stream,input[4],'"');
        getline(stream,input[4],'"');
        // Status code
        getline(stream,input[5],' ');
        getline(stream,input[5],' ');
        // Data transfered
        getline(stream,input[6],' ');
        // Referer
        getline(stream,input[7],'"');
        getline(stream,input[7],'"');
        // Client Identification
        getline(stream,input[8],'"');
        getline(stream,input[8],'"');

        string lol;
        getline(stream,lol,'\n');

        if( stream.eof() ) break;
        for( string s : input ) cout << s << " ";

        cout << endl;

        // Filling logData

        // Date Flag
        if(t)
        {
            int hour;
            for( int i=0;i<input[3].length; i++)
            {
                if( input[3][i] == ':' )
                {
                    string h = input[3][i+1] +input[3][i+2];
                    hour = stoi(h);
                    break;
                }
            }
            if( hour != time ) continue;
        }

        // Log

        // string http = "http://intranet-if.insa-lyon.fr";
        //
        // for( int i=0;i<input[4].length; i++)
        // {
        //     if( input[4][i] == ' ')
        //     {
        //         i++;
        //         while( input[4][i] != ' '  )
        //         {
        //             http += input[4][i];
        //             i++;
        //         }
        //     }
        // }
        //
        // string http2 = input[7];
        //
        // // not found
        // if( logData.find(http) == logData.end() )
        // {
        //     visits v;
        //     v.hits = 1;
        //     v.visitors.insert("----",1);
        //     logData.insert(make_pair())
        // }
        // else // found
        // {
        //
        // }

    }


}
