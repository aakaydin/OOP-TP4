/*************************************************************************
                           LogData  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <LogData> (fichier LogData.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "LogData.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type LogData::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void LogData::parseFile(string fileName, flagsData f) {

    LogStream stream(fileName);

    while( !stream.eof() )
    {
        vector<string> input = stream.getLogLine();

        // Date Flag
        if(!passFlagConditions(input, f)) {
            continue;
        }

        // Populate logData with parsed line data
        addLineToLogData( input);
    }

}

void LogData::makeGraph( string filename) {

    string nodes;
    string edges;

    // nodeNames stores a mapping between generated nodeX variable names
    // and their identifying URLs, with n being the total number of distinct nodes.
    unordered_map<string, string> nodeNames;
    int n = 0;

    for(auto& data: log) {

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

void LogData::statistics()
{
    multimap<int,string> topTen;

    for(auto& p: log)
    {
        topTen.insert(make_pair(p.second.hits,p.first));

        // cout << "lol" << endl;
    }

    multimap<int,string> :: reverse_iterator i;


    int j = 0;
    for( i=topTen.rbegin(); i != topTen.rend(); ++i )
    {
        cout << "/" <<  i->second;
        cout<< " (" << i->first << " hits)" << endl;
        j++;
        if( j > 9 ) break;
    }
}


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

LogData::LogData ( string fileName , flagsData f)
// Algorithme :
//
{
    //cout << "log data const" << endl;
    parseFile(fileName,f);

#ifdef MAP
    cout << "Appel au constructeur de <LogData>" << endl;
#endif
} //----- Fin de LogData


LogData::~LogData ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <LogData>" << endl;
#endif
} //----- Fin de ~LogData


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

bool LogData::passFlagConditions(vector<string> parsedLine, flagsData f) {
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
            if( parsedLine[4].find(".jpg") != std::string::npos
            || parsedLine[4].find(".png") != std::string::npos
            || parsedLine[4].find(".gif") != std::string::npos
            || parsedLine[4].find(".ico") != std::string::npos
            || parsedLine[4].find(".css") != std::string::npos
            || parsedLine[4].find(".js") != std::string::npos  )
            {
                return false;
            }
        }

    return true;
}


void LogData::addLineToLogData( vector<string> input) {
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
    if( log.find(http) == log.end() )
    {
        visits newVisits;
        newVisits.hits = 1;
        newVisits.visitors.insert(make_pair(http2, 1));
        log.insert(make_pair(http, newVisits));
    }
    else // found
    {

        visits keyData = log.at(http);
        keyData.hits++;
        if(keyData.visitors.find(http2) == keyData.visitors.end()) {
            keyData.visitors.insert(make_pair(http2, 1));
        } else {
            keyData.visitors.at(http2)++;
        }
        log[http] = keyData;
    }
}
