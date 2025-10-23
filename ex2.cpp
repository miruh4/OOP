#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

class Serviciu3D {
private:
    char* model;       // alocat dinamic
    string material;
    int nrExemplare;
    double dimensiuni; // volum sau dimensiune generica
    double cost;
    string categorie;  // ex: "Decoratiune", "Prototip"
    string dataLivrare; // data estimata de livrare

public:
    static const double TVA;

    // Constructor default
    Serviciu3D() : model(nullptr), material("N/A"), nrExemplare(0), dimensiuni(0), cost(0), categorie("N/A"), dataLivrare("N/A") {}

    // Constructor cu parametri
    Serviciu3D(const char* m, string mat, int nr, double dim, double c, string cat, string data)
        : material(mat), nrExemplare(nr), dimensiuni(dim), cost(c), categorie(cat), dataLivrare(data) {
        if (m) {
            model = new char[strlen(m) + 1];
            strcpy(model, m);
        } else model = nullptr;
    }

    // Constructor copiere
    Serviciu3D(const Serviciu3D& s)
        : material(s.material), nrExemplare(s.nrExemplare), dimensiuni(s.dimensiuni), cost(s.cost), categorie(s.categorie), dataLivrare(s.dataLivrare) {
        if (s.model) {
            model = new char[strlen(s.model) + 1];
            strcpy(model, s.model);
        } else model = nullptr;
    }

    // Operator =
    Serviciu3D& operator=(const Serviciu3D& s) {
        if (this == &s) return *this;
        delete[] model;
        if (s.model) {
            model = new char[strlen(s.model) + 1];
            strcpy(model, s.model);
        } else model = nullptr;
        material = s.material;
        nrExemplare = s.nrExemplare;
        dimensiuni = s.dimensiuni;
        cost = s.cost;
        categorie = s.categorie;
        dataLivrare = s.dataLivrare;
        return *this;
    }

    ~Serviciu3D() { delete[] model; }

    // Operator < pentru sortare dupa cost
    bool operator<(const Serviciu3D& s) const {
        return cost < s.cost;
    }

    // Operator += combina doar daca modelul si materialul coincid
    Serviciu3D& operator+=(const Serviciu3D& s) {
        if (model && s.model && strcmp(model, s.model) == 0 && material == s.material) {
            nrExemplare += s.nrExemplare;
            cost += s.cost;
        }
        return *this;
    }

    void afisare() const {
        cout << "Model: " << (model ? model : "N/A")
             << " | Material: " << material
             << " | Nr exemplare: " << nrExemplare
             << " | Dimensiuni: " << dimensiuni
             << " | Cost: " << cost
             << " | Categorie: " << categorie
             << " | Data livrare: " << dataLivrare << "\n";
    }

    // Scriere binara
    void scrieBin(ofstream& fout) const {
        int len = model ? strlen(model) : 0;
        fout.write((char*)&len, sizeof(len));
        if (len) fout.write(model, len);
        int matLen = material.size();
        fout.write((char*)&matLen, sizeof(matLen));
        fout.write(material.c_str(), matLen);
        fout.write((char*)&nrExemplare, sizeof(nrExemplare));
        fout.write((char*)&dimensiuni, sizeof(dimensiuni));
        fout.write((char*)&cost, sizeof(cost));

        int catLen = categorie.size();
        fout.write((char*)&catLen, sizeof(catLen));
        fout.write(categorie.c_str(), catLen);

        int dataLen = dataLivrare.size();
        fout.write((char*)&dataLen, sizeof(dataLen));
        fout.write(dataLivrare.c_str(), dataLen);
    }

    // Citire binara
    void citesteBin(ifstream& fin) {
        int len;
        fin.read((char*)&len, sizeof(len));
        delete[] model;
        if (len) {
            model = new char[len + 1];
            fin.read(model, len);
            model[len] = '\0';
        } else model = nullptr;

        int matLen;
        fin.read((char*)&matLen, sizeof(matLen));
        char* buffer = new char[matLen + 1];
        fin.read(buffer, matLen);
        buffer[matLen] = '\0';
        material = buffer;
        delete[] buffer;

        fin.read((char*)&nrExemplare, sizeof(nrExemplare));
        fin.read((char*)&dimensiuni, sizeof(dimensiuni));
        fin.read((char*)&cost, sizeof(cost));

        int catLen;
        fin.read((char*)&catLen, sizeof(catLen));
        buffer = new char[catLen + 1];
        fin.read(buffer, catLen);
        buffer[catLen] = '\0';
        categorie = buffer;
        delete[] buffer;

        int dataLen;
        fin.read((char*)&dataLen, sizeof(dataLen));
        buffer = new char[dataLen + 1];
        fin.read(buffer, dataLen);
        buffer[dataLen] = '\0';
        dataLivrare = buffer;
        delete[] buffer;
    }

    string getMaterial() const { return material; }
};

const double Serviciu3D::TVA = 0.19;

// Manager mai complex cu STL map pentru cautare dupa material
class ManagerServicii {
private:
    vector<Serviciu3D> servicii;
public:
    void adaugaServiciu(const Serviciu3D& s) { servicii.push_back(s); }
    
    void afisare() {
        for (auto& s : servicii) s.afisare();
    }

    // Cautare dupa material
    vector<Serviciu3D> cautaDupaMaterial(const string& mat) {
        vector<Serviciu3D> rez;
        for (auto& s : servicii)
            if (s.getMaterial() == mat)
                rez.push_back(s);
        return rez;
    }
};

int main() {
    Serviciu3D s1("Model1", "Plastic", 10, 12.5, 100.0, "Decoratiune", "2025-01-30");
    Serviciu3D s2("Model2", "Lemn", 5, 20.0, 150.0, "Prototip", "2025-02-05");
    Serviciu3D s3("Model1", "Plastic", 5, 12.5, 50.0, "Decoratiune", "2025-01-30");

    s1 += s3; // combina exemplare si cost pentru acelasi model si material

    vector<Serviciu3D> lista = {s1, s2};
    sort(lista.begin(), lista.end()); // foloseste operator< pentru sortare dupa cost

    cout << "--- Lista sortata ---\n";
    for (auto& s : lista) s.afisare();

    ManagerServicii mgr;
    mgr.adaugaServiciu(s1);
    mgr.adaugaServiciu(s2);

    cout << "--- Manager Servicii ---\n";
    mgr.afisare();

    // cautare dupa material
    vector<Serviciu3D> plastice = mgr.cautaDupaMaterial("Plastic");
    cout << "--- Servicii din Plastic ---\n";
    for (auto& s : plastice) s.afisare();

    return 0;
}
