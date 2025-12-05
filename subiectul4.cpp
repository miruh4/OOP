#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Masina {
private:
    char* marca;
    int anFabricatie;
    double putereMotor;

    // Atribut 1: culoare - util pentru descrierea mașinii
    char* culoare;

    // Atribut 2: kilometraj - util pentru evaluarea uzurii
    double kilometraj;

public:
    // Constructor fără parametri
    Masina() : anFabricatie(0), putereMotor(0), kilometraj(0) {
        marca = new char[strlen("Necunoscut") + 1];
        strcpy(marca, "Necunoscut");

        culoare = new char[strlen("Necunoscut") + 1];
        strcpy(culoare, "Necunoscut");
    }

    // Constructor cu parametri + validări
    Masina(const char* m, int an, double putere, const char* c, double km) {
        if (an < 0) an = 0;
        if (putere < 0) putere = 0;
        if (km < 0) km = 0;

        marca = new char[strlen(m) + 1];
        strcpy(marca, m);

        anFabricatie = an;
        putereMotor = putere;

        culoare = new char[strlen(c) + 1];
        strcpy(culoare, c);

        kilometraj = km;
    }

    // Constructor de copiere
    Masina(const Masina& ms) {
        marca = new char[strlen(ms.marca) + 1];
        strcpy(marca, ms.marca);

        anFabricatie = ms.anFabricatie;
        putereMotor = ms.putereMotor;

        culoare = new char[strlen(ms.culoare) + 1];
        strcpy(culoare, ms.culoare);

        kilometraj = ms.kilometraj;
    }

    // Operator =
    Masina& operator=(const Masina& ms) {
        if (this == &ms) return *this; // auto-atribuire

        delete[] marca;
        delete[] culoare;

        marca = new char[strlen(ms.marca) + 1];
        strcpy(marca, ms.marca);

        anFabricatie = ms.anFabricatie;
        putereMotor = ms.putereMotor;

        culoare = new char[strlen(ms.culoare) + 1];
        strcpy(culoare, ms.culoare);

        kilometraj = ms.kilometraj;

        return *this;
    }

    // Destructor
    ~Masina() {
        delete[] marca;
        delete[] culoare;
    }

    // Getters & setters
    double getPutereMotor() const { return putereMotor; }
    void setPutereMotor(double p) { if (p >= 0) putereMotor = p; }

    const char* getCuloare() const { return culoare; }
    void setCuloare(const char* c) {
        delete[] culoare;
        culoare = new char[strlen(c) + 1];
        strcpy(culoare, c);
    }

    double getKilometraj() const { return kilometraj; }
    void setKilometraj(double km) { if (km >= 0) kilometraj = km; }

    void afisare() const {
        cout << "Marca: " << marca
             << "\nAn Fabricatie: " << anFabricatie
             << "\nPutere Motor: " << putereMotor << " CP"
             << "\nCuloare: " << culoare
             << "\nKilometraj: " << kilometraj << " km\n";
    }
};

int main() {
    Masina m1("BMW", 2018, 190.5, "Negru", 75000);

    cout << "Masina 1:\n";
    m1.afisare();

    Masina m2 = m1; // constructor copiere
    cout << "\nMasina 2 (copiata):\n";
    m2.afisare();

    Masina m3;
    m3 = m1; // operator =
    cout << "\nMasina 3 (atribuire):\n";
    m3.afisare();

    // modificări
    m3.setPutereMotor(210.7);
    m3.setCuloare("Albastru");
    m3.setKilometraj(82000);

    cout << "\nMasina 3 modificata:\n";
    m3.afisare();

    return 0;
}
