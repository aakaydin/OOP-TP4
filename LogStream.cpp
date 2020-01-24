/*************************************************************************
                           LogStream  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <LogStream> (fichier LogStream.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <vector>
using namespace std;

//------------------------------------------------------ Include personnel
#include "LogStream.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type LogStream::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
LogStream & LogStream::operator = ( const LogStream & unLogStream )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
LogStream::LogStream ( const LogStream & unLogStream )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <LogStream>" << endl;
#endif
} //----- Fin de LogStream (constructeur de copie)


LogStream::LogStream (string filename)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <LogStream>" << endl;
#endif

    endOfFile = false;
    stream.open(filename);

} //----- Fin de LogStream

vector<string> LogStream::getLogLine() {
    vector<string> input(9);

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

        string newLine;
        getline(stream,newLine,'\n');

        endOfFile = (stream.eof());

        return input;
}


LogStream::~LogStream ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <LogStream>" << endl;
#endif
} //----- Fin de ~LogStream


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

