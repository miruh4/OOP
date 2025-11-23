#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

class Produs {
private:
    char* nume; // alocat dinamic
    string tipProdus; // carne proaspata, congelata etc.
    string tipCarne;  // vita, porc, peste etc.
    string dataExp;   // format simplu: "2025-01-01"
    double pret;
    int stoc;

public:
    static const double TVA; // exemplu membru static/const

    Produs() : nume(nullptr), tipProdus("N/A"), tipCarne("N/A"), dataExp("N/A"), pret(0), stoc(0) {}

    Produs(const char* n, string tp, string tc, string de, double p, int s) :
        tipProdus(tp), tipCarne(tc), dataExp(de), pret(p), stoc(s) {
        if (n != nullptr) {
            nume = new char[strlen(n) + 1];
            strcpy(nume, n);
        } else {
            nume = nullptr;
        }
    }

    Produs(const Produs& other) : tipProdus(other.tipProdus), tipCarne(other.tipCarne),
        dataExp(other.dataExp), pret(other.pret), stoc(other.stoc) {
        if (other.nume) {
            nume = new char[strlen(other.nume) + 1];
            strcpy(nume, other.nume);
        } else nume = nullptr;
    }

    Produs& operator=(const Produs& other) {
        if (this == &other) return *this;
        delete[] nume;
        if (other.nume) {
            nume = new char[strlen(other.nume) + 1];
            strcpy(nume, other.nume);
        } else nume = nullptr;
        tipProdus = other.tipProdus;
        tipCarne = other.tipCarne;
        dataExp = other.dataExp;
        pret = other.pret;
        stoc = other.stoc;
        return *this;
    }

    ~Produs() { delete[] nume; }

    // operator *= reducere dacă expiră mâine
    Produs& operator*=(double reducere) {
        pret *= (1 - reducere);
        return *this;
    }

    // operator == compară toate câmpurile
    bool operator==(const Produs& p) const {
        return strcmp(nume, p.nume) == 0 && tipProdus == p.tipProdus && tipCarne == p.tipCarne &&
               dataExp == p.dataExp && pret == p.pret && stoc == p.stoc;
    }

    const string& getTipCarne() const { return tipCarne; }
    const string& getDataExp() const { return dataExp; }
    int getStoc() const { return stoc; }

    void actualizeazaStoc(int cant) { stoc += cant; }

    friend ostream& operator<<(ostream& out, const Produs& p) {
        out << "Produs: " << (p.nume ? p.nume : "N/A")
            << " | Tip:" << p.tipProdus
            << " | Carne:" << p.tipCarne
            << " | Exp:" << p.dataExp
            << " | Pret:" << p.pret
            << " | Stoc:" << p.stoc;
        return out;
    }
};

const double Produs::TVA = 0.09;

// Clasa pentru gestiunea stocurilor
class StocMagazin {
private:
    vector<Produs> produse;

public:
    // operator += adaugă un produs sau actualizează dacă există
    void operator+=(const Produs& p) {
        for (auto& prod : produse) {
            if (prod == p) {
                prod.actualizeazaStoc(p.getStoc());
                return;
            }
        }
        produse.push_back(p);
    }

    // operator() elimină produsele fără stoc
    void operator()() {
        vector<Produs> filtrat;
        for (auto& p : produse)
            if (p.getStoc() > 0)
                filtrat.push_back(p);
        produse = filtrat;
    }

    void afiseaza() {
        for (auto& p : produse) cout << p << "\n";
    }
};

// container STL pentru căutarea după SPECIE DE PEȘTE
// -> folosim multimap<string, Produs>
// cheia = tipCarne (ex: "somon", "pastrav")
// valoarea = produsul
using MapPeste = multimap<string, Produs>;

int main() {
    Produs p1("Pulpa Porc", "Carne proaspata", "porc", "2025-01-20", 25.5, 10);
    Produs p2("Somon", "Carne proaspata", "somon", "2025-01-19", 50.0, 5);

    // Reducere pentru produsele ce expira maine -> *= 0.20
    p2 *= 0.20;

    // Test operator ==
    cout << "Sunt egale? " << (p1 == p2) << "\n";

    // Gestiune stoc
    StocMagazin stoc;
    stoc += p1;
    stoc += p2;

    cout << "--- Inainte de stergere ---\n";
    stoc.afiseaza();

    stoc(); // elimina produsele cu stoc 0

    cout << "--- Dupa stergere ---\n";
    stoc.afiseaza();

    // container pentru produse de pește
    MapPeste hartaPeste;
    hartaPeste.insert({"somon", p2});

    return 0;
}
