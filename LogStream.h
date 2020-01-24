/*************************************************************************
                           LogStream  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <LogStream> (fichier LogStream.h) ----------------
#if ! defined ( LOGSTREAM_H )
#define LOGSTREAM_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LogStream>
//
//
//------------------------------------------------------------------------

class LogStream
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    LogStream(string filename);
    vector<string> getLogLine();

//------------------------------------------------- Surcharge d'opérateurs
    LogStream & operator = ( const LogStream & unLogStream );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    LogStream ( const LogStream & unLogStream );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    LogStream ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~LogStream ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    bool endOfFile;
    ifstream stream;
};

//-------------------------------- Autres définitions dépendantes de <LogStream>

#endif // LOGSTREAM_H

