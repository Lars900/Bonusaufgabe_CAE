#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

class Aufgabe
{
    private:
        int ID;
        string Name;
        int Schwierigkeitsgrad;
        int Bearbeitungszeit;

    public:
        Aufgabe() 
        {
            ID = 0; Name = "tbd"; Schwierigkeitsgrad = 0; Bearbeitungszeit = 0;
        }
        Aufgabe(int eingabe1, string eingabe2, int eingabe3, int eingabe4)
        {
            ID = eingabe1;
            Name = eingabe2;
            Schwierigkeitsgrad = eingabe3;
            Bearbeitungszeit = eingabe4;
        }

        int getID()
        {
            return ID;
        }
        void setID(int eingabe)
        {
            if (eingabe > 0)
            {
                ID = eingabe;
            }
            else
            {
                cout << "Die ID kann keine negative Zahl annehmen." << endl;
            }
        }

        string getName()
        {
            return Name;
        }
        void setName(string eingabe)
        {
            Name = eingabe;
        }
        
        int getSchwierigkeitsgrad()
        {
            return Schwierigkeitsgrad;
        }
        void setSchwierigkeitsgrad(int eingabe)
        {
            if (Schwierigkeitsgrad == (1 || 2 || 3))
            {
                Schwierigkeitsgrad = eingabe;
            }
            else
            {
                cout << "Der Schwierigkeitsgrad muss in einer Zahl zwischen 1 und 3 angegeben werden" << endl;
            }
        }

        int getBearbeitungszeit()
        {
            return Bearbeitungszeit;
        }
        void setBearbeitungszeit(int eingabe)
        {
            if (eingabe >= 0)
            {
                Bearbeitungszeit = eingabe;
            }
            else
            {
                cout << "Die Bearbeitungszeit kann keine negative Zahl annehmen." << endl;
            }
        }

    protected:

};