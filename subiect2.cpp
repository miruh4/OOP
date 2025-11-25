#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Carte {
private:
    char* titlu;
    char* autor;
    int anPublicatie;
    char* isbn;

    // Atribut 1: număr pagini - util pentru descrierea detaliată a cărții
    int numarPagini;

    // Atribut 2: gen literar - util pentru clasificare
    char* gen;

public:
    // Constructor fără parametri
    Carte() : anPublicatie(0), numarPagini(0) {
        titlu = new char[strlen("Necunoscut") + 1];
        strcpy(titlu, "Necunoscut");

        autor = new char[strlen("Necunoscut") + 1];
        strcpy(autor, "Necunoscut");

        isbn = new char[strlen("N/A") + 1];
        strcpy(isbn, "N/A");

        gen = new char[strlen("Necunoscut") + 1];
        strcpy(gen, "Necunoscut");
    }

    // Constructor cu parametri + validări
    Carte(const char* t, const char* a, int an, const char* i, int pag, const char* g) {
        if (an < 0) an = 0;
        if (pag < 1) pag = 1;

        titlu = new char[strlen(t) + 1];
        strcpy(titlu, t);

        autor = new char[strlen(a) + 1];
        strcpy(autor, a);

        anPublicatie = an;

        isbn = new char[strlen(i) + 1];
        strcpy(isbn, i);

        numarPagini = pag;

        gen = new char[strlen(g) + 1];
        strcpy(gen, g);
    }

    // Constructor de copiere
    Carte(const Carte& c) {
        titlu = new char[strlen(c.titlu) + 1];
        strcpy(titlu, c.titlu);

        autor = new char[strlen(c.autor) + 1];
        strcpy(autor, c.autor);

        anPublicatie = c.anPublicatie;

        isbn = new char[strlen(c.isbn) + 1];
        strcpy(isbn, c.isbn);

        numarPagini = c.numarPagini;

        gen = new char[strlen(c.gen) + 1];
        strcpy(gen, c.gen);
    }

    // Operator =
    Carte& operator=(const Carte& c) {
        if (this == &c) return *this; // evităm auto-atribuirea

        delete[] titlu;
        delete[] autor;
        delete[] isbn;
        delete[] gen;

        titlu = new char[strlen(c.titlu) + 1];
        strcpy(titlu, c.titlu);

        autor = new char[strlen(c.autor) + 1];
        strcpy(autor, c.autor);

        anPublicatie = c.anPublicatie;

        isbn = new char[strlen(c.isbn) + 1];
        strcpy(isbn, c.isbn);

        numarPagini = c.numarPagini;

        gen = new char[strlen(c.gen) + 1];
        strcpy(gen, c.gen);

        return *this;
    }

    // Destructor
    ~Carte() {
        delete[] titlu;
        delete[] autor;
        delete[] isbn;
        delete[] gen;
    }

    // Getters & setters
    int getAnPublicatie() const { return anPublicatie; }
    void setAnPublicatie(int an) { if (an >= 0) anPublicatie = an; }

    int getNumarPagini() const { return numarPagini; }
    void setNumarPagini(int pag) { if (pag >= 1) numarPagini = pag; }

    const char* getGen() const { return gen; }
    void setGen(const char* g) {
        delete[] gen;
        gen = new char[strlen(g) + 1];
        strcpy(gen, g);
    }

    void afisare() const {
        cout << "Titlu: " << titlu
             << "\nAutor: " << autor
             << "\nAn publicatie: " << anPublicatie
             << "\nISBN: " << isbn
             << "\nNumar pagini: " << numarPagini
             << "\nGen: " << gen << "\n";
    }
};

int main() {
    Carte c1("Ion", "Liviu Rebreanu", 1920, "123-456", 300, "Roman");

    cout << "Carte 1:\n";
    c1.afisare();

    Carte c2 = c1; // test constructor copiere
    cout << "\nCarte 2 (copie):\n";
    c2.afisare();

    Carte c3;
    c3 = c1; // test operator=
    cout << "\nCarte 3 (atribuire):\n";
    c3.afisare();

    c3.setNumarPagini(350);
    c3.setGen("Drama");
    c3.setAnPublicatie(1930);

    cout << "\nCarte 3 modificata:\n";
    c3.afisare();

    return 0;
}
