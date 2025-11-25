#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Student {
private:
    const int idStudent;       // id unic pentru fiecare student
    static int nrStudenti;     // numar total de studenti
    char* nume;                // nume alocat dinamic
    int nota;                  // nota studentului
    int anStudiu;              // anul de studiu
    float mediaGenerala;       // media generala
    int nrMaterii;             // numarul de materii
    char** materii;            // vector de materii alocat dinamic

public:
    // Getteri
    int getIdStudent() { return this->idStudent; }
    static int getNrStudenti() { return nrStudenti; }
    char* getNume() { return this->nume; }
    int getNota() { return this->nota; }
    int getAnStudiu() { return this->anStudiu; }
    float getMediaGenerala() { return this->mediaGenerala; }
    int getNrMaterii() { return this->nrMaterii; }
    char** getMaterii() { return this->materii; }

    // Setteri
    void setNume(const char* n) {
        if (strlen(n) > 0) {
            if (this->nume) delete[] this->nume;
            this->nume = new char[strlen(n) + 1];
            strcpy(this->nume, n);
        }
    }

    void setNota(int n) { if (n >= 1 && n <= 10) this->nota = n; }
    void setAnStudiu(int a) { if (a >= 1 && a <= 6) this->anStudiu = a; }
    void setMediaGenerala(float m) { if (m >= 0) this->mediaGenerala = m; }

    void setMaterii(int nr, char** mat) {
        if (this->materii) {
            for (int i = 0; i < this->nrMaterii; i++) delete[] this->materii[i];
            delete[] this->materii;
        }
        this->nrMaterii = nr;
        if (this->nrMaterii > 0) {
            this->materii = new char*[this->nrMaterii];
            for (int i = 0; i < this->nrMaterii; i++) {
                this->materii[i] = new char[strlen(mat[i]) + 1];
                strcpy(this->materii[i], mat[i]);
            }
        } else this->materii = nullptr;
    }

    // Constructor fara parametri
    Student() : idStudent(++nrStudenti), nota(0), anStudiu(1), mediaGenerala(0.0f), nrMaterii(0), materii(nullptr) {
        this->nume = new char[strlen("Necunoscut") + 1];
        strcpy(this->nume, "Necunoscut");
    }

    // Constructor cu parametri
    Student(const char* n, int nota, char** mat, int nr, int an, float media)
        : idStudent(++nrStudenti) {
        this->nota = (nota >= 1 && nota <= 10) ? nota : 1;
        this->anStudiu = (an >= 1 && an <= 6) ? an : 1;
        this->mediaGenerala = (media >= 0) ? media : 0;
        if (n) {
            this->nume = new char[strlen(n) + 1];
            strcpy(this->nume, n);
        } else this->nume = nullptr;

        this->nrMaterii = nr;
        if (this->nrMaterii > 0) {
            this->materii = new char*[this->nrMaterii];
            for (int i = 0; i < this->nrMaterii; i++) {
                this->materii[i] = new char[strlen(mat[i]) + 1];
                strcpy(this->materii[i], mat[i]);
            }
        } else this->materii = nullptr;
    }

    // Constructor de copiere
    Student(const Student& copie) : idStudent(++nrStudenti) {
        this->nota = copie.nota;
        this->anStudiu = copie.anStudiu;
        this->mediaGenerala = copie.mediaGenerala;
        this->nrMaterii = copie.nrMaterii;

        if (copie.nume) {
            this->nume = new char[strlen(copie.nume) + 1];
            strcpy(this->nume, copie.nume);
        } else this->nume = nullptr;

        if (copie.materii) {
            this->materii = new char*[this->nrMaterii];
            for (int i = 0; i < this->nrMaterii; i++) {
                this->materii[i] = new char[strlen(copie.materii[i]) + 1];
                strcpy(this->materii[i], copie.materii[i]);
            }
        } else this->materii = nullptr;
    }

    // Operator =
    void operator=(const Student& copie) {
        if (this == &copie) return;

        this->nota = copie.nota;
        this->anStudiu = copie.anStudiu;
        this->mediaGenerala = copie.mediaGenerala;

        // dezalocare materii vechi
        if (this->materii) {
            for (int i = 0; i < this->nrMaterii; i++) delete[] this->materii[i];
            delete[] this->materii;
        }

        // copiere materii
        this->nrMaterii = copie.nrMaterii;
        if (copie.materii) {
            this->materii = new char*[this->nrMaterii];
            for (int i = 0; i < this->nrMaterii; i++) {
                this->materii[i] = new char[strlen(copie.materii[i]) + 1];
                strcpy(this->materii[i], copie.materii[i]);
            }
        } else this->materii = nullptr;

        // copiere nume
        if (this->nume) delete[] this->nume;
        if (copie.nume) {
            this->nume = new char[strlen(copie.nume) + 1];
            strcpy(this->nume, copie.nume);
        } else this->nume = nullptr;
    }

    // Destructor
    ~Student() {
        if (this->nume) delete[] this->nume;
        if (this->materii) {
            for (int i = 0; i < this->nrMaterii; i++) delete[] this->materii[i];
            delete[] this->materii;
        }
    }

    // Afisare
    void afisare() {
        cout << "ID: " << this->idStudent
             << ", Nume: " << (this->nume ? this->nume : "N/A")
             << ", Nota: " << this->nota
             << ", An studiu: " << this->anStudiu
             << ", Media: " << this->mediaGenerala
             << "\nMaterii: ";
        for (int i = 0; i < this->nrMaterii; i++) cout << this->materii[i] << " ";
        cout << endl;
    }
};

int Student::nrStudenti = 0;

int main() {
    char* materii1[] = { (char*)"POO", (char*)"Algoritmi" };
    Student s1("Ion Popescu", 9, materii1, 2, 2, 8.5f);
    s1.afisare();

    Student s2 = s1; // constructor de copiere
    s2.afisare();

    Student s3;
    s3 = s1; // operator =
    s3.afisare();

    s3.setNota(10);
    s3.setAnStudiu(3);
    s3.setMediaGenerala(9.1f);
    s3.afisare();

    cout << "Numar studenti creati: " << Student::getNrStudenti() << endl;

    return 0;
}
