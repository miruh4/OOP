#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
using namespace std;

class Serviciu3D {
private:
    char* model;
    string material;
    int nrExemplare;
    double dimensiuni;
    double cost;

public:
    static const double TVA;

    Serviciu3D() : model(nullptr), material("N/A"), nrExemplare(0), dimensiuni(0), cost(0) {}

    Serviciu3D(const char* m, string mat, int nr, double dim, double c) : material(mat), nrExemplare(nr), dimensiuni(dim), cost(c) {
        if (m != nullptr) {
            model = new char[strlen(m) + 1];
            strcpy(model, m);
        } else model = nullptr;
    }

    Serviciu3D(const Serviciu3D& s) : material(s.material), nrExemplare(s.nrExemplare), dimensiuni(s.dimensiuni), cost(s.cost) {
        if (s.model) {
            model = new char[strlen(s.model) + 1];
            strcpy(model, s.model);
        } else model = nullptr;
    }

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
        return *this;
    }

    ~Serviciu3D() { delete[] model; }

    // operator += combina doua obiecte cu acelasi model
    Serviciu3D& operator+=(const Serviciu3D& s) {
        if (model && s.model && strcmp(model, s.model) == 0) {
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
             << " | Cost: " << cost << "\n";
    }

    void scrieBin(ofstream& fout) {
        int len = model ? strlen(model) : 0;
        fout.write((char*)&len, sizeof(len));
        if (len > 0) fout.write(model, len);
        int matLen = material.size();
        fout.write((char*)&matLen, sizeof(matLen));
        fout.write(material.c_str(), matLen);
        fout.write((char*)&nrExemplare, sizeof(nrExemplare));
        fout.write((char*)&dimensiuni, sizeof(dimensiuni));
        fout.write((char*)&cost, sizeof(cost));
    }

    void citesteBin(ifstream& fin) {
        int len;
        fin.read((char*)&len, sizeof(len));
        delete[] model;
        if (len > 0) {
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
    }
};

const double Serviciu3D::TVA = 0.19;

// Manager simplu "has-a"
class ManagerServicii {
private:
    vector<Serviciu3D> servicii;
public:
    void adaugaServiciu(const Serviciu3D& s) { servicii.push_back(s); }
    void afisare() {
        for (auto& s : servicii) s.afisare();
    }
};

int main() {
    Serviciu3D s1("Model1", "Plastic", 10, 12.5, 100.0);
    Serviciu3D s2("Model2", "Lemn", 5, 20.0, 150.0);
    Serviciu3D s3("Model1", "Plastic", 5, 12.5, 50.0);

    s1 += s3; // combina exemplare si cost pentru acelasi model

    ManagerServicii mgr;
    mgr.adaugaServiciu(s1);
    mgr.adaugaServiciu(s2);

    cout << "--- Manager Servicii ---\n";
    mgr.afisare();

    // scriere/citire fisier binar
    ofstream fout("servicii.bin", ios::binary);
    s1.scrieBin(fout);
    fout.close();

    Serviciu3D s4;
    ifstream fin("servicii.bin", ios::binary);
    s4.citesteBin(fin);
    fin.close();

    cout << "--- Citire din fisier binar ---\n";
    s4.afisare();

    return 0;
}
