#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>
#include <thread>
#include "Klausur.h"

using namespace std;

void foo(Klausur Klausur2, vector<Aufgabe> Klausur1aufgaben)
        {
            cout << "[10] Die Klausur exportieren." << endl << endl;

            string ausgabe1 = Klausur2.getDatum();
            string ausgabe2 = Klausur2.getTitel();
            int ausgabe3 = Klausur2.getDauer();
            cout << "Datum: " << ausgabe1 << endl;
            cout << "Titel: " << ausgabe2 << endl;
            cout << "Dauer: " << ausgabe3 << endl << endl; 
            ausgabe1.erase(0,2);

            string s = "Klausur_export/"+ausgabe1+".tex";
            cout << s << endl;
            fstream file;
            string h = "\\";
            h.erase(1,1);
            file.open(s,ios::out);
        
            file << "%Datum: " << ausgabe1 << endl;
            file << "%Titel: " << ausgabe2 << endl;
            file << "%Dauer: " << ausgabe3 << endl << endl;
            file << h+"documentclass[11pt,a4paper,oneside]{report}" << endl;
            file << h+"begin{document}" <<  endl;
            file << "Datum: " << ausgabe1 << endl;
            file << "Titel: " << ausgabe2 << endl;
            file << "Dauer: " << ausgabe3 << endl << endl;
        
            for (int i = 0; i < Klausur1aufgaben.size(); i++)
                {
                    int ausgabe10 = Klausur1aufgaben[i].getID();
                    string befehl = h+"input{./Aufgaben/" + std::to_string(ausgabe10) + ".tex}";
                    file << befehl << endl; 
                }
            file << h+"end{document}" <<  endl;
            string p = Klausur2.getDatum();
            p.erase(0,2);
            s = "pdflatex Klausur_export/"+p+".tex";
            const char * d = s.c_str();
            system(d);


        }


int main()
{
Aufgabe Aufgabenverwaltung[9999];
vector<Klausur> Klausurenverwaltung;
Klausurenverwaltung.shrink_to_fit(); 
vector<Aufgabe> Klausur1aufgaben;
Klausur Klausur2; 

cout << "Bestehende Aufgaben werden geladen..." << endl;
for (int i = 0; i <= 9999; i++)
{
    string zeile1;
    int IDload = 0;
    string Nameload = "tbd";
    int Skgload = 0;
    int Bbzload = 0;
    fstream loadfile;
    loadfile.open("Aufgaben/"+std::to_string(i)+".tex");
   
    getline(loadfile, zeile1);
    zeile1.erase(0,5);
    istringstream(zeile1) >> IDload;

    getline(loadfile, zeile1);
    zeile1.erase(0,7);
    Nameload = zeile1;

    getline(loadfile, zeile1);
    zeile1.erase(0,20);
    istringstream(zeile1) >> Skgload;

    getline(loadfile, zeile1);
    zeile1.erase(0,19);
    istringstream(zeile1) >> Bbzload;

    Aufgabe Aufgabe1 (IDload, Nameload, Skgload,Bbzload);
    Aufgabenverwaltung[IDload] = Aufgabe1;

    loadfile.close(); 
}
cout << "Aufgaben wurden erfolgreich geladen!" << endl << endl;

cout << "Bestehende Klausuren werden geladen..." << endl;
bool Klausurvorhanden = true;
int k = 1;
while (Klausurvorhanden == true)
{
    string zeile1;
    string Datumload = "tbd";
    string Titelload = "tbd";
    int Dauerload = 0;

    fstream loadfile;
    loadfile.open("Klausuren/"+std::to_string(k)+".tex");
    if (loadfile.is_open()==false)
    {
        Klausurvorhanden = false;
    }
   
    getline(loadfile, zeile1);
    zeile1.erase(0,7);
    Datumload = zeile1;

    getline(loadfile, zeile1);
    zeile1.erase(0,7);
    Titelload = zeile1;

    getline(loadfile, zeile1);
    zeile1.erase(0,8);
    istringstream(zeile1) >> Dauerload;

    if(Klausurvorhanden == true)
    {    
        Klausur Klausur1 (Datumload, Titelload, Dauerload);
        Klausurenverwaltung.push_back(Klausur1);
    }

    loadfile.close(); 
    k = k + 1;
}
cout << "Klausuren wurden erfolgreich geladen!" << endl << endl;

while (true == true)
{
    int auswahl;
    string opener;
    cout << "Sehr geehrte Prueferinnen und Pruefer," << endl << 
    "ich wuensche Sie herzlichst zur digitalen Klausurerstellung willkommen." << endl << 
    "Bitte waehlen Sie zu Beginn die gewuenschte Funktion durch Eingabe der voranstehenden Nummer aus" << endl << 
    "und bestaetigen Sie ihre Eingabe mit <Enter>." << endl << endl <<
    
    "[1]  Eine Aufgabe anlegen." << endl <<  
    "[2]  Eine Aufgabe bearbeiten." << endl << 
    "[3]  Eine Aufgabe loeschen." << endl << 
    "[4]  Eine Uebersicht aller Aufgagen ausgeben." << endl << 
    "[5]  Eine neue Klausur erstellen." << endl << 
    "[6]  Einer Klausur Aufgaben zuweisen." << endl << 
    "[7]  Eine Aufgabe aus einer Klausur entfernen." << endl << 
    "[8]  Die Klausurkonfiguration ausgeben." << endl <<
    "[9]  Eine Klausurkonfiguration importieren" << endl << 
    "[10] Eine Klausur exportieren." << endl; 
    cin >> auswahl;
    cout << endl << endl;

    if (auswahl == 1)
    {
        int eingabe1;
        string eingabe2;
        int eingabe3;
        int eingabe4;

        cout << "[1]  Eine Aufgabe anlegen." << endl << endl;
        cout << "Bitte geben Sie die ID(1 bis 9999) der anzulegenden Aufgabe ein: ";
        cin >> eingabe1;
        cout << "Bitte geben Sie den Namen(- statt Leerzeichen) der anzulegenden Aufgabe ein: ";
        cin >> eingabe2;
        cout << "Bitte geben Sie den Schwierigkeitsgrad(1=Leicht, 2=Mittel, 3=Schwer) der anzulegenden Aufgabe ein: ";
        cin >> eingabe3;
        cout << "Bitte geben Sie die Bearbeitungszeit in Minuten der anzulegenden Aufgabe ein: ";
        cin >> eingabe4;
        cout << endl;

        int Zaehler = eingabe1;

        Aufgabe Aufgabe1 (eingabe1, eingabe2, eingabe3, eingabe4);
        Aufgabenverwaltung[Zaehler] = Aufgabe1;

        cout << "Ihre Aufgabe wurde mit folgenden Parametern erstellt:" << endl << endl;
        int ausgabe1 = Aufgabe1.getID();
        string ausgabe2 = Aufgabe1.getName();
        int ausgabe3 = Aufgabe1.getSchwierigkeitsgrad();
        int ausgabe4 = Aufgabe1.getBearbeitungszeit();

        std::string s = "Aufgaben/"+std::to_string(ausgabe1)+".tex";
        string h = "\\";
        h.erase(1,1);
        fstream file;
        file.open(s,ios::out);
        file << "%ID: " << ausgabe1 << endl;
        file << "%Name: " << ausgabe2 << endl;
        file << "%Schwierigkeitsgrad: " << ausgabe3 << endl;
        file << "%Bearbeitungszeit: " << ausgabe4 << endl << endl;
        file << h+"begin{abstract}"<< endl;
        file << "Name: " << ausgabe2 << endl;
        file << "Schwierigkeitsgrad: " << ausgabe3 << endl;
        file << "Bearbeitungszeit: " << ausgabe4 << endl << endl;
        file << h+"end{abstract}" << endl;
        file.close();


        cout << "ID: " << ausgabe1 << endl;
        cout << "Name: " << ausgabe2 << endl;
        cout << "Schwierigkeitsgrad: " << ausgabe3 << endl;
        cout << "Bearbeitungszeit: " << ausgabe4 << endl << endl;

        cout << "Ihre Aufgabe wurde erfolgreich angelegt. Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
        "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;
    }
    else if (auswahl == 2)
    {
        cout << "[2]  Eine Aufgabe bearbeiten." << endl << endl;
        int eingabe1;
        string eingabe2;
        int eingabe3;
        int eingabe4;
        cout << "Bitte geben Sie die ID der zu bearbeitenden Aufgabe ein: ";
        cin >> eingabe1;

        cout << "Die zu bearbeitende Aufgabe ist die folgende:" << endl << endl;
        int ausgabe1 = Aufgabenverwaltung[eingabe1].getID();
        string ausgabe2 = Aufgabenverwaltung[eingabe1].getName();
        int ausgabe3 = Aufgabenverwaltung[eingabe1].getSchwierigkeitsgrad();
        int ausgabe4 = Aufgabenverwaltung[eingabe1].getBearbeitungszeit();

        cout << "ID: " << ausgabe1 << endl;
        cout << "Name: " << ausgabe2 << endl;
        cout << "Schwierigkeitsgrad: " << ausgabe3 << endl;
        cout << "Bearbeitungszeit: " << ausgabe4 << endl << endl;

        cout << "Bitte geben Sie den neuen Namen(- statt Leerzeichen) der zu bearbeitenden Aufgabe ein: ";
        cin >> eingabe2;
        cout << "Bitte geben Sie den neuen Schwierigkeitsgrad(1=Leicht, 2=Mittel, 3=Schwer) der zu bearbeitenden Aufgabe ein: ";
        cin >> eingabe3;
        cout << "Bitte geben Sie die neue Bearbeitungszeit in Minuten der zu bearbeitenden Aufgabe ein: ";
        cin >> eingabe4;
        cout << endl;

        int Zaehler = eingabe1;

        Aufgabe Aufgabe1 (eingabe1, eingabe2, eingabe3, eingabe4);
        Aufgabenverwaltung[Zaehler] = Aufgabe1;

        cout << "Die zu bearbeitende Aufgabe wurde mit folgenden Parametern überschrieben:" << endl << endl;
        ausgabe1 = Aufgabe1.getID();
        ausgabe2 = Aufgabe1.getName();
        ausgabe3 = Aufgabe1.getSchwierigkeitsgrad();
        ausgabe4 = Aufgabe1.getBearbeitungszeit();

        std::string s = "Aufgaben/"+std::to_string(ausgabe1)+".tex";
        fstream file;
        string h = "\\";
        h.erase(1,1);
        file.open(s,ios::out);
        file << "%ID: " << ausgabe1 << endl;
        file << "%Name: " << ausgabe2 << endl;
        file << "%Schwierigkeitsgrad: " << ausgabe3 << endl;
        file << "%Bearbeitungszeit: " << ausgabe4 << endl << endl;
        file << h+"begin{abstract}"<< endl;
        file << "Name: " << ausgabe2 << endl;
        file << "Schwierigkeitsgrad: " << ausgabe3 << endl;
        file << "Bearbeitungszeit: " << ausgabe4 << endl << endl;
        file << h+"end{abstract}" << endl;
        file.close();


        cout << "ID: " << ausgabe1 << endl;
        cout << "Name: " << ausgabe2 << endl;
        cout << "Schwierigkeitsgrad: " << ausgabe3 << endl;
        cout << "Bearbeitungszeit: " << ausgabe4 << endl << endl;

        cout << "Ihre Aufgabe wurde erfolgreich bearbeitet. Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
        "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;

    }
    else if (auswahl == 3)
    {
        cout << "[3]  Eine Aufgabe loeschen." << endl << endl;

        int eingabe1;
        int eingabe2;
        cout << "Bitte geben Sie die ID der zu loeschenden Aufgabe ein: ";
        cin >> eingabe1;

        cout << "Die zu loeschende Aufgabe ist die folgende:" << endl << endl;
        int ausgabe1 = Aufgabenverwaltung[eingabe1].getID();
        string ausgabe2 = Aufgabenverwaltung[eingabe1].getName();
        int ausgabe3 = Aufgabenverwaltung[eingabe1].getSchwierigkeitsgrad();
        int ausgabe4 = Aufgabenverwaltung[eingabe1].getBearbeitungszeit();

        cout << "ID: " << ausgabe1 << endl;
        cout << "Name: " << ausgabe2 << endl;
        cout << "Schwierigkeitsgrad: " << ausgabe3 << endl;
        cout << "Bearbeitungszeit: " << ausgabe4 << endl << endl;

        cout << "Wollen Sie die Aufgabe wirklich unwiederruflich loeschen? Falls ja, waehlen Sie 1 und bestaetigen Sie mit der <Enter> Taste." << endl <<
                "Falls Sie die Aktion abbrechen wollen, waehlen Sie eine beliebige andere Zahl und bestaetigen mit der <Enter>-Taste: " << endl;
        cin >> eingabe2;
        if (eingabe2 == 1)
        {
            string s = "Aufgaben/" + std::to_string(ausgabe1) + ".tex";
            const char * c = s.c_str();
            std::remove(c);
            Aufgabenverwaltung[eingabe1] = Aufgabe();
            cout << "Die Aufgabe wurde unwiederruflich geloescht. Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
            "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;
        }
        else
        {
            cout << "Das Loeschen der Aufgabe wurde abgebrochen. Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
            "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;
        }
    }
    else if (auswahl == 4)
    {
        cout << "[4]  Eine Uebersicht aller Aufgaben ausgeben." << endl << endl;

        for (int i = 1; i <= 9999; i++)
        {
            std::string s = "Aufgaben/"+std::to_string(i)+".tex";
            fstream file;
            file.open(s);
            
            if (file.fail()==false)
            {
                int ausgabe1 = Aufgabenverwaltung[i].getID();
                string ausgabe2 = Aufgabenverwaltung[i].getName();
                int ausgabe3 = Aufgabenverwaltung[i].getSchwierigkeitsgrad();
                int ausgabe4 = Aufgabenverwaltung[i].getBearbeitungszeit();

                cout << "ID: " << ausgabe1 << endl;
                cout << "Name: " << ausgabe2 << endl;
                cout << "Schwierigkeitsgrad: " << ausgabe3 << endl;
                cout << "Bearbeitungszeit: " << ausgabe4 << endl << endl;
            }
        }
        cout << "Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
            "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;
    }
    else if (auswahl == 5)
    {
        cout << "[5]  Eine neue Klausur erstellen." << endl << endl; 

        string eingabe1;
        string eingabe2;
        int eingabe3;

        cout << "Bitte geben Sie das Datum(TT.MM.JJJ) der Klausur ein: ";
        cin >> eingabe1;
        cout << "Bitte geben Sie den Titel(_ statt Leerzeichen) der Klausur ein: ";
        cin >> eingabe2;
        cout << "Bitte geben Sie die Dauer(in Minuten) der Klausur ein: ";
        cin >> eingabe3;
        cout << endl;

        Klausur Klausur1 (eingabe1, eingabe2, eingabe3);
        Klausurenverwaltung.push_back(Klausur1);
        int stelle = Klausurenverwaltung.size();

        cout << "Ihre Klausur wurde mit folgenden Parametern erstellt:" << endl << endl;
        string ausgabe1 = Klausur1.getDatum();
        string ausgabe2 = Klausur1.getTitel();
        int ausgabe3 = Klausur1.getDauer();


        std::string s = "Klausuren/"+std::to_string(stelle)+".tex";
        fstream file;
        file.open(s,ios::out);
        file << "%Datum: " << ausgabe1 << endl;
        file << "%Titel: " << ausgabe2 << endl;
        file << "%Dauer: " << ausgabe3 << endl << endl;
        file.close();


        cout << "Datum: " << ausgabe1 << endl;
        cout << "Titel: " << ausgabe2 << endl;
        cout << "Dauer: " << ausgabe3 << endl << endl;

        cout << "Ihre Klausur wurde erfolgreich angelegt. Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
        "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;

    }
    else if (auswahl == 6)
    {
        int eingabe1;
        cout << "[6]  Einer Klausur Aufgaben zuweisen." << endl << endl;
        cout << "Welcher Klausur moechten Sie Aufgaben zuweisen? Bitte wahlen Sie die Nummer der Klausur und bestaetigen Sie ihre Auswahl mit der <Enter>-Taste." << endl << endl;

        for (int i = 0; i < Klausurenverwaltung.size(); i++)
        {
            Klausur Klausur1 = Klausurenverwaltung[i];
            string ausgabe1 = Klausur1.getDatum();
            string ausgabe2 = Klausur1.getTitel();
            int ausgabe3 = Klausur1.getDauer();

            cout << "Nummer: " << i << endl;
            cout << "Datum: " << ausgabe1 << endl;
            cout << "Titel: " << ausgabe2 << endl;
            cout << "Dauer: " << ausgabe3 << endl << endl;
        }
        cin >> eingabe1;

        Klausur Klausur1 = Klausurenverwaltung[eingabe1];
        string ausgabe1 = Klausur1.getDatum();
        string ausgabe2 = Klausur1.getTitel();
        int ausgabe3 = Klausur1.getDauer();
        Klausur2 = Klausur1;
        
        cout << "Die von Ihnen ausgewaehlte Klausur ist die folgende: " << endl;

        cout << "Nummer: " << eingabe1 << endl;
        cout << "Datum: " << ausgabe1 << endl;
        cout << "Titel: " << ausgabe2 << endl;
        cout << "Dauer: " << ausgabe3 << endl << endl; 
        
        Klausur1aufgaben = Klausur1.Aufgabenzuweisung();
        Klausur1aufgaben.shrink_to_fit();

        cout << "Die Aufgaben wurden Ihrer ausgewaehlten Klausur erfolgreich hinzugefuegt. Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
        "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;

    }
    else if (auswahl == 7)
    {
        cout << "[7]  Eine Aufgabe aus der erstellten Klausur entfernen." << endl << endl;

        string ausgabe1 = Klausur2.getDatum();
        string ausgabe2 = Klausur2.getTitel();
        int ausgabe3 = Klausur2.getDauer();
        
        cout << "Die erstellte Klausur ist die folgende: " << endl << endl;

        cout << "Datum: " << ausgabe1 << endl;
        cout << "Titel: " << ausgabe2 << endl;
        cout << "Dauer: " << ausgabe3 << endl << endl; 

        cout << "Die zu der Klausur gehoerenden Aufgaben sind folgende: " << endl << endl;

        for (int i = 0; i < Klausur1aufgaben.size(); i++)
        {
                int ausgabe1 = Klausur1aufgaben[i].getID();
                string ausgabe2 = Klausur1aufgaben[i].getName();
                int ausgabe3 = Klausur1aufgaben[i].getSchwierigkeitsgrad();
                int ausgabe4 = Klausur1aufgaben[i].getBearbeitungszeit();

                cout << "Nummer: " << i << endl;
                cout << "ID: " << ausgabe1 << endl;
                cout << "Name: " << ausgabe2 << endl;
                cout << "Schwierigkeitsgrad: " << ausgabe3 << endl;
                cout << "Bearbeitungszeit: " << ausgabe4 << endl << endl;
        }

        cout << "Geben Sie die Nummer der Aufgabe ein, welche Sie loeschen moechten: " << endl;
        int nummer;
        cin >> nummer;
        Klausur1aufgaben.erase(Klausur1aufgaben.begin()+nummer);
        Klausur1aufgaben.shrink_to_fit();
        
        cout << "Die uebrigen zu der Klausur gehoerenden Aufgaben sind folgende: " << endl << endl;

        for (int i = 0; i < Klausur1aufgaben.size(); i++)
        {
                int ausgabe1 = Klausur1aufgaben[i].getID();
                string ausgabe2 = Klausur1aufgaben[i].getName();
                int ausgabe3 = Klausur1aufgaben[i].getSchwierigkeitsgrad();
                int ausgabe4 = Klausur1aufgaben[i].getBearbeitungszeit();

                cout << "ID: " << ausgabe1 << endl;
                cout << "Name: " << ausgabe2 << endl;
                cout << "Schwierigkeitsgrad: " << ausgabe3 << endl;
                cout << "Bearbeitungszeit: " << ausgabe4 << endl << endl;
        }

        cout << "Die Aufgabe wurde erfolgreich aus der Klausur geloescht. Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
        "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;

    }
    else if (auswahl == 8)
    {
        cout << "[8]  Die Klausurkonfiguration ausgeben." << endl << endl;

        string ausgabe1 = Klausur2.getDatum();
        string ausgabe2 = Klausur2.getTitel();
        int ausgabe3 = Klausur2.getDauer();


        std::string s = "Klausurkonfigurationen/"+ausgabe1+".txt";
        fstream file;
        file.open(s,ios::out);
        file << "%Datum: " << ausgabe1 << endl;
        file << "%Titel: " << ausgabe2 << endl;
        file << "%Dauer: " << ausgabe3 << endl << endl;
        
        for (int i = 0; i < Klausur1aufgaben.size(); i++)
        {
            int ausgabe4 = Klausur1aufgaben[i].getID();
            string ausgabe5 = Klausur1aufgaben[i].getName();
            int ausgabe6 = Klausur1aufgaben[i].getSchwierigkeitsgrad();
            int ausgabe7 = Klausur1aufgaben[i].getBearbeitungszeit();
            file << "%Nummer: " << i << endl;
            file << "%ID: " << ausgabe4 << endl;
            file << "%Name: " << ausgabe5 << endl;
            file << "%Schwierigkeitsgrad: " << ausgabe6 << endl;
            file << "%Bearbeitungszeit: " << ausgabe7 << endl << endl;    
        }
        
        file.close();


        cout << "Die Klausurkonfiguration wurde erfolgreich exportiert. Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
        "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;

    }
    else if (auswahl == 9)
    {
        cout << "[9] Eine Klausurkonfiguration importieren" << endl << endl;

        string schluessel;
        cout << "Bitte geben Sie das Datum(TT.MM.JJJJ) der zu importierenden Klausur an: " << endl;
        cin >> schluessel;
        schluessel = "Klausurkonfigurationen/"+schluessel+".txt";
        cout << schluessel;
        
        fstream loadfile;
        string zeile1;
        string Datumload;
        string Titelload;
        int Dauerload;

        loadfile.open(schluessel);
        if (loadfile.is_open()==true)
        {
            getline(loadfile, zeile1);
            zeile1.erase(0,6);
            Datumload = zeile1;

            getline(loadfile, zeile1);
            zeile1.erase(0,7);
            Titelload = zeile1;

            getline(loadfile, zeile1);
            zeile1.erase(0,8);
            istringstream(zeile1) >> Dauerload;

            Klausur2.setDatum(Datumload);
            Klausur2.setTitel(Titelload);
            Klausur2.setDauer(Dauerload);

            Klausur1aufgaben.clear();
            Klausur1aufgaben.shrink_to_fit();

            for (int i = 1; i > 0 ;i+0)
            {
                string zeile2;
                int IDload;
                string Nameload;
                int Skgload;
                int Bbzload;
            
                getline(loadfile, zeile2);

                getline(loadfile, zeile2);
                zeile2.erase(0,9);
                istringstream(zeile2) >> i;

                getline(loadfile, zeile2);
                zeile2.erase(0,5);
                istringstream(zeile2) >> IDload;

                getline(loadfile, zeile2);
                zeile2.erase(0,7);
                Nameload = zeile2;

                getline(loadfile, zeile2);
                zeile2.erase(0,20);
                istringstream(zeile2) >> Skgload;

                getline(loadfile, zeile2);
                zeile2.erase(0,19);
                istringstream(zeile2) >> Bbzload;

                if (Nameload == "")
                {
                    i = 0;
                }
                else
                {
                    Aufgabe Aufgabe1(IDload, Nameload, Skgload, Bbzload);
                    Klausur1aufgaben.push_back(Aufgabe1);
                    i = 1;
                }
            }

            loadfile.close();

            cout << "Die importierte Klausur ist die folgende: " << endl << endl;
            string ausgabe1 = Klausur2.getDatum();
            string ausgabe2 = Klausur2.getTitel();
            int ausgabe3 = Klausur2.getDauer();
            cout << "Datum: " << ausgabe1 << endl;
            cout << "Titel: " << ausgabe2 << endl;
            cout << "Dauer: " << ausgabe3 << endl << endl; 

            cout << "Die zu der Klausur gehoerenden Aufgaben sind folgende: " << endl << endl;

            for (int i = 0; i < Klausur1aufgaben.size(); i++)
            {
                int ausgabe1 = Klausur1aufgaben[i].getID();
                string ausgabe2 = Klausur1aufgaben[i].getName();
                int ausgabe3 = Klausur1aufgaben[i].getSchwierigkeitsgrad();
                int ausgabe4 = Klausur1aufgaben[i].getBearbeitungszeit();

                cout << "Nummer: " << i << endl;
                cout << "ID: " << ausgabe1 << endl;
                cout << "Name: " << ausgabe2 << endl;
                cout << "Schwierigkeitsgrad: " << ausgabe3 << endl;
                cout << "Bearbeitungszeit: " << ausgabe4 << endl << endl;
            }


            cout << "Die Klausurkonfiguration wurde erfolgreich importiert. Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
            "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;
        }
        else
        {
            cout << "Klausurkonfiguration wurde nicht gefunden. Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
            "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;
        }

    }
    else if (auswahl == 10)
    {
        
        std::thread thread_object(foo, Klausur2, Klausur1aufgaben);
        cout << "Die Klausur wurde erfolgreich als PDF exportiert. Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
            "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;

    }   
    else
    {
        cout << "Ihre Eingabe entsprach keiner Zahl zwischen 1 und 10. Bitte druecken Sie einen beliebigen Buchstaben und" << endl << 
        "bestaetigen Sie mit der <Enter> Taste um zum Hauptmenue zurueckzugelangen." << endl;
    }


    cin >> opener;
    cout << endl << endl;

};
}
