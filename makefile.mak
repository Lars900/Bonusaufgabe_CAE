Aufgabenverwaltung: Aufgabenverwaltung.o
	g++ Aufgabenverwaltung.o -o Aufgabenverwaltung

Aufgabenverwaltung.o: Aufgabenverwaltung.cpp
	g++ -c Aufgabenverwaltung.cpp

clean:
	rm *.o 