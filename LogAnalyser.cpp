#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;

struct visits {

    unordered_map<string,int>  visitors;
    int hits;

};

struct flagsData {

    bool e;
    bool g;
    bool t;

    int time;
    string graphFilename;

    flagsData() {
        e = 0;
        g = 0;
        t = 0;
        time = 0;
    }
};

// Parses the arguments specified by the user at runtime
flagsData parseArgs(int argc, char* argv[]);

// Parses and returns the data from a log file in the logData data structure
unordered_map<string,visits> parseFile(string filename, flagsData f);

// For a given line, checks whether or not this data should be added to logData, for a given set of flags
bool passFlagConditions(vector<string> parsedLine, flagsData f);

// Adds the data from a given parsed line (vector<string>) to a given logData
unordered_map<string,visits> addLineToLogData(unordered_map<string,visits>& logData, vector<string> input);

// Prints the contents of 'logData'
void printMapContents(unordered_map<string,visits> logData);

void makeGraph(unordered_map<string,visits> logData, string filename);

int main( int argc, char* argv[] )
{

    string filename = argv[argc-1];

    flagsData f = parseArgs(argc, argv);

    unordered_map<string,visits> logData = parseFile(filename, f);

    if(f.g) {
        makeGraph(logData, f.graphFilename);
    }


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

unordered_map<string,visits> parseFile(string filename, flagsData f) {
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

        // Filling logData

        // Date Flag
        if(!passFlagConditions(input, f)) {
            continue;
        }

        // Populate logData with parsed line data
        logData = addLineToLogData(logData, input);
    }

    return logData;
}

bool passFlagConditions(vector<string> parsedLine, flagsData f) {
    if(f.t)
        {
            int hour;
            for( int i=0;i<parsedLine[3].length(); i++)
            {
                if( parsedLine[3][i] == ':' )
                {
                    string h;
                    h += parsedLine[3][i+1];
                    h +=  + parsedLine[3][i+2];
                    hour = stoi(h);
                    break;
                }
            }
            return hour == f.time;
        }

    // Handle remaining flags here

    if(f.e)
        {
            if( parsedLine[4].find(".jpg") != std::string::npos || parsedLine[4].find(".png") != std::string::npos || parsedLine[4].find(".gif") != std::string::npos ||
            parsedLine[4].find(".ico") != std::string::npos || parsedLine[4].find(".css") != std::string::npos || parsedLine[4].find(".js") != std::string::npos  )
            {
                return false;
            }
        }

    return true;
}

unordered_map<string,visits> addLineToLogData(unordered_map<string,visits>& logData, vector<string> input) {
    string http = "http://intranet-if.insa-lyon.fr";

    for( int i=0;i<input[4].length(); i++)
    {
        if( input[4][i] == ' ')
        {
            i++;
            while( input[4][i] != ' '  )
            {
                http += input[4][i];
                i++;
            }
        }
    }

    string http2 = input[7];

    // not found
    if( logData.find(http) == logData.end() )
    {
        visits newVisits;
        newVisits.hits = 1;
        newVisits.visitors.insert(make_pair(http2, 1));
        logData.insert(make_pair(http, newVisits));
    }
    else // found
    {

        visits keyData = logData.at(http);
        keyData.hits++;
        if(keyData.visitors.find(http2) == keyData.visitors.end()) {
            keyData.visitors.insert(make_pair(http2, 1));
        } else {
            keyData.visitors.at(http2)++;
        }
        logData[http] = keyData;
    }

    return logData;
}

void printMapContents(unordered_map<string,visits> logData) {
    for(auto& p: logData) {
        std::cout << " " << p.first << " -- hits: " << p.second.hits << "\n" ;
        for(auto& q: p.second.visitors) {
            cout << "   " << q.first << " - " << q.second << endl;
        }
    }
}

void makeGraph(unordered_map<string,visits> logData, string filename) {

    string nodes;
    string edges;

    // nodeNames stores a mapping between generated nodeX variable names
    // and their identifying URLs, with n being the total number of distinct nodes.
    unordered_map<string, string> nodeNames;
    int n = 0;

    for(auto& data: logData) {

        string nodeName = "node" + to_string(n++);
        nodes += nodeName + " [label=\"" + data.first + "\"];\n";
        nodeNames.insert(make_pair(data.first, nodeName));

        for(auto& visitor : data.second.visitors) {

            string visitorNodeName;
            if(nodeNames.find(visitor.first) == nodeNames.end()) {
                visitorNodeName = "node" + to_string(n++);
                nodes += visitorNodeName + " [label=\"" + visitor.first + "\"];\n";
                nodeNames.insert(make_pair(visitor.first, visitorNodeName));
            } else {
                visitorNodeName = nodeNames.at(visitor.first);
            }

            edges += visitorNodeName + " -> " + nodeName + "[label=\"" + to_string(visitor.second) + "\"];\n";
        }
    }

    string fileText = "digraph {\n" + nodes + edges + "}";

    ofstream out(filename);
    out << fileText;
    out.close();

}
