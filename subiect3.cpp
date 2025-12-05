#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Angajat {
private:
    char* nume;
    double salariu;
    char* departament;

    // Atribut 1: vechime în companie (în ani) - util pentru bonusuri și evaluări
    int vechime;

    // Atribut 2: funcție - util pentru ierarhizare și descrierea postului
    char* functie;

public:
    // Constructor fără parametri
    Angajat() : salariu(0), vechime(0) {
        nume = new char[strlen("Necunoscut") + 1];
        strcpy(nume, "Necunoscut");

        departament = new char[strlen("Necunoscut") + 1];
        strcpy(departament, "Necunoscut");

        functie = new char[strlen("Necunoscut") + 1];
        strcpy(functie, "Necunoscut");
    }

    // Constructor cu parametri + validări
    Angajat(const char* n, double s, const char* d, int v, const char* f) {
        if (s < 0) s = 0;
        if (v < 0) v = 0;

        nume = new char[strlen(n) + 1];
        strcpy(nume, n);

        salariu = s;

        departament = new char[strlen(d) + 1];
        strcpy(departament, d);

        vechime = v;

        functie = new char[strlen(f) + 1];
        strcpy(functie, f);
    }

    // Constructor de copiere
    Angajat(const Angajat& a) {
        nume = new char[strlen(a.nume) + 1];
        strcpy(nume, a.nume);

        salariu = a.salariu;

        departament = new char[strlen(a.departament) + 1];
        strcpy(departament, a.departament);

        vechime = a.vechime;

        functie = new char[strlen(a.functie) + 1];
        strcpy(functie, a.functie);
    }

    // Operator =
    Angajat& operator=(const Angajat& a) {
        if (this == &a) return *this; // evităm auto-atribuirea

        delete[] nume;
        delete[] departament;
        delete[] functie;

        nume = new char[strlen(a.nume) + 1];
        strcpy(nume, a.nume);

        salariu = a.salariu;

        departament = new char[strlen(a.departament) + 1];
        strcpy(departament, a.departament);

        vechime = a.vechime;

        functie = new char[strlen(a.functie) + 1];
        strcpy(functie, a.functie);

        return *this;
    }

    // Destructor
    ~Angajat() {
        delete[] nume;
        delete[] departament;
        delete[] functie;
    }

    // Getters & setters
    double getSalariu() const { return salariu; }
    void setSalariu(double s) { if (s >= 0) salariu = s; }

    int getVechime() const { return vechime; }
    void setVechime(int v) { if (v >= 0) vechime = v; }

    const char* getFunctie() const { return functie; }
    void setFunctie(const char* f) {
        delete[] functie;
        functie = new char[strlen(f) + 1];
        strcpy(functie, f);
    }

    void afisare() const {
        cout << "Nume: " << nume
             << "\nSalariu: " << salariu
             << "\nDepartament: " << departament
             << "\nVechime: " << vechime
             << " ani"
             << "\nFunctie: " << functie << "\n";
    }
};

int main() {
    Angajat a1("Maria Ionescu", 4500.5, "IT", 5, "Programator");

    cout << "Angajat 1:\n";
    a1.afisare();

    Angajat a2 = a1; // test constructor copiere
    cout << "\nAngajat 2 (copie):\n";
    a2.afisare();

    Angajat a3;
    a3 = a1; // test operator=
    cout << "\nAngajat 3 (atribuire):\n";
    a3.afisare();

    a3.setSalariu(5200);
    a3.setVechime(6);
    a3.setFunctie("Senior Developer");

    cout << "\nAngajat 3 modificat:\n";
    a3.afisare();

    return 0;
}
