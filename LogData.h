/*************************************************************************
                           LogData  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <LogData> (fichier LogData.h) ----------------
#if ! defined ( LOGDATA_H )
#define LOGDATA_H







//--------------------------------------------------- Interfaces utilisées

#include <unordered_map>
#include <iostream>
#include <map>
#include <vector>
#include "Flags.h"
#include "LogStream.h"


//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct visits {

    unordered_map<string,int>  visitors;
    int hits;

};


//------------------------------------------------------------------------
// Rôle de la classe <LogData>
//
//
//------------------------------------------------------------------------

class LogData
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    // Parses and returns the data from a log file in the logData data structure
    void parseFile(string filename, flagsData f);

    void makeGraph( string filename);

    // Statistics funciton
    void statistics();


//------------------------------------------------- Surcharge d'opérateurs
    LogData & operator = ( const LogData & unLogData );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    LogData ( const LogData & unLogData );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    LogData ( string fileName, flagsData f);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~LogData ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

// For a given line, checks whether or not this data should be added to logData, for a given set of flags
bool passFlagConditions(vector<string> parsedLine, flagsData f);

// Adds the data from a given parsed line (vector<string>) to a given logData
void addLineToLogData( vector<string> input);


//----------------------------------------------------- Attributs protégés
    unordered_map<string,visits> log;

};

//-------------------------------- Autres définitions dépendantes de <LogData>

#endif // LogData_H
