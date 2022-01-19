#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include "Aufgabe.h"

using namespace std;

class Klausur
{
    private:
        string Datum;
        string Titel;
        int Dauer;
        vector<Aufgabe> Klausuraufgaben;

    public:
        Klausur() 
        {
            Datum = "tbd"; Titel = "tbd"; Dauer = 0;
        }
        Klausur(string eingabe1, string eingabe2, int eingabe3)
        {
            Datum = eingabe1;
            Titel = eingabe2;
            Dauer = eingabe3;
        }
        
        string getDatum()
        {
            return Datum;
        }
        void setDatum(string eingabe)
        {
            Datum = eingabe;
        }

        string getTitel()
        {
            return Titel;
        }
        void setTitel(string eingabe)
        {
            Titel = eingabe;
        }

        int getDauer()
        {
            return Dauer;
        }
        void setDauer(int eingabe)
        {
            if (eingabe >= 0)
            {
                Dauer = eingabe;
            }
            else
            {
                cout << "Die Dauer kann keine negative Zahl annehmen." << endl;
            }
        }

        vector<Aufgabe> Aufgabenzuweisung()
        {
            int dauer = getDauer();
            int laufzeit = 0;
            
            vector<Aufgabe> Klausur1;
            vector<Aufgabe> Aufgabenpool;
            Aufgabenpool.shrink_to_fit();
            bool Aufgabenvorhanden = true;
            int k = 1;
            while (Aufgabenvorhanden == true)
            {
                string zeile1;
                int IDload = 0;
                string Nameload = "tbd";
                int Skgload = 0;
                int Bbzload = 0;
                fstream loadfile;
                loadfile.open("Aufgaben/"+std::to_string(k)+".tex");
                if (loadfile.is_open()==false)
                {
                    Aufgabenvorhanden = false;
                }
   
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

                if(Aufgabenvorhanden == true)
                {    
                    Aufgabe Aufgabe1 (IDload, Nameload, Skgload, Bbzload);
                    Aufgabenpool.push_back(Aufgabe1);
                }

                loadfile.close(); 
                k = k + 1;
            }
            int zufallsauswahl;
            cout << "Falls Sie die Klausuraufgaben anhand des Zufallsprinzips auswaehlen moechten, geben Sie eine 1 ein und besteatigen Ihre Auswahl mit der <Enter>-Taste." << endl <<
                    "Falls Sie die Klausuraufgaben manuell einpflegen wollen, waehlen Sie eine beliebige andere Zahl aus und bestaetigen Ihre Auswahl mit der <Enter>-Taste." <<endl << endl;
            cin >> zufallsauswahl;
            if (zufallsauswahl == 1)
            {
                while (dauer >= laufzeit)
                {
                    int groessePool = 0;
                    int wahl;
                    Aufgabenpool.shrink_to_fit();
                    groessePool = Aufgabenpool.size();
                    int zufallszahl;
                    srand (time(NULL));
                    zufallszahl = rand() % groessePool + 0;
                    
                    cout << "Die zufaellig ausgewaehlte Klausuraufgabe ist folgende: " << endl << endl;
                    int ausgabe1 = Aufgabenpool[zufallszahl].getID();
                    string ausgabe2 = Aufgabenpool[zufallszahl].getName();
                    int ausgabe3 = Aufgabenpool[zufallszahl].getSchwierigkeitsgrad();
                    int ausgabe4 = Aufgabenpool[zufallszahl].getBearbeitungszeit();
                    cout << "ID: " << ausgabe1 << endl;
                    cout << "Name: " << ausgabe2 << endl;
                    cout << "Schwierigkeitsgrad: " << ausgabe3 << endl;
                    cout << "Bearbeitungszeit: " << ausgabe4 << endl << endl;

                    cout << "Falls Sie die Position der Klausuraufgabeauswaehlen moechten, geben Sie eine 1 ein und besteatigen Ihre Auswahl mit der <Enter>-Taste." << endl <<
                    "Falls Sie die Klausuraufgaben hinten anhaengen wollen, waehlen Sie eine beliebige andere Zahl aus und bestaetigen Ihre Auswahl mit der <Enter>-Taste." <<endl << endl;
                    cin >> wahl;
                    
                    if (wahl == 1)
                    {
                        int position;
                        cout << "An welcher Position soll die Klausuraufgabe angebracht werden? Bitte bestaetigen Sie ihre Auswahl mit der <Enter>-Taste." << endl << endl;
                        cin >> position;
                        if (position < Klausur1.size())
                        {
                            Klausur1[position] = Aufgabenpool[zufallszahl];
                        }
                        else
                        {
                            Klausur1.push_back(Aufgabenpool[zufallszahl]);
                        }
                    }
                    else
                    {
                        Klausur1.push_back(Aufgabenpool[zufallszahl]);
                    }
                    laufzeit = laufzeit + Aufgabenpool[zufallszahl].getBearbeitungszeit();
                    Aufgabenpool.erase(Aufgabenpool.begin()+zufallszahl);
                }
                Klausur1.shrink_to_fit();
            }
            else
            {
                while (dauer >= laufzeit)
                {
                    int ID;
                    cout << "Bitte geben Sie die ID der gewuenschten Aufgabe ein: " << endl;
                    cin >> ID;
                    Aufgabe Aufgabe1 = Aufgabenpool[ID-1];
                    cout << "Die von Ihnen ausgewaehlte Klausuraufgabe ist folgende: " << endl << endl;
                    int ausgabe1 = Aufgabe1.getID();
                    string ausgabe2 = Aufgabe1.getName();
                    int ausgabe3 = Aufgabe1.getSchwierigkeitsgrad();
                    int ausgabe4 = Aufgabe1.getBearbeitungszeit();
                    cout << "ID: " << ausgabe1 << endl;
                    cout << "Name: " << ausgabe2 << endl;
                    cout << "Schwierigkeitsgrad: " << ausgabe3 << endl;
                    cout << "Bearbeitungszeit: " << ausgabe4 << endl << endl;
                    
                    int wahl;
                    cout << "Falls Sie die Position der Klausuraufgabeauswaehlen moechten, geben Sie eine 1 ein und besteatigen Ihre Auswahl mit der <Enter>-Taste." << endl <<
                    "Falls Sie die Klausuraufgaben hinten anhaengen wollen, waehlen Sie eine beliebige andere Zahl aus und bestaetigen Ihre Auswahl mit der <Enter>-Taste." <<endl << endl;
                    cin >> wahl;
                    
                    if (wahl == 1)
                    {
                        int position;
                        cout << "An welcher Position soll die Klausuraufgabe angebracht werden? Bitte bestaetigen Sie ihre Auswahl mit der <Enter>-Taste." << endl << endl;
                        cin >> position;
                        if (position < Klausur1.size())
                        {
                            Klausur1[position] = Aufgabenpool[ID-1];
                        }
                        else
                        {
                            Klausur1.push_back(Aufgabenpool[ID-1]);
                        }
                    }
                    else
                    {
                        Klausur1.push_back(Aufgabenpool[ID-1]);
                    }
                    laufzeit = laufzeit + Aufgabe1.getBearbeitungszeit();
                }

            }

            cout << "Ihre ertellte Klausur stellt sich wie folgt zusammen: " << endl << endl;
            for (int i = 0; i < Klausur1.size(); i++)
            {
                int ausgabe1 = Klausur1[i].getID();
                string ausgabe2 = Klausur1[i].getName();
                int ausgabe3 = Klausur1[i].getSchwierigkeitsgrad();
                int ausgabe4 = Klausur1[i].getBearbeitungszeit();

                cout << "ID: " << ausgabe1 << endl;
                cout << "Name: " << ausgabe2 << endl;
                cout << "Schwierigkeitsgrad: " << ausgabe3 << endl;
                cout << "Bearbeitungszeit: " << ausgabe4 << endl << endl;
            }
        return Klausur1;          
        }
        

    protected:

};