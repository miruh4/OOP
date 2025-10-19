#include <iostream>
#include <cstring>
using namespace std;

struct Student {
    char* nume;
    float nota;
};

void filtrareStudentiPrag(Student** studenti, int* dim, float prag) {
    Student* aux = new Student[*dim];
    int j = 0;
    for(int i = 0; i < *dim; i++) {
        if((*studenti)[i].nota >= prag) aux[j++] = (*studenti)[i];
        else delete[] (*studenti)[i].nume;
    }
    delete[] (*studenti);
    *dim = j;
    *studenti = aux;
}

void inverseazaStudenti(Student** studenti, int dim) {
    for(int i = 0; i < dim/2; i++) {
        Student temp = (*studenti)[i];
        (*studenti)[i] = (*studenti)[dim - 1 - i];
        (*studenti)[dim - 1 - i] = temp;
    }
}

float mediaNote(Student* studenti, int dim) {
    if(dim == 0) return 0;
    float suma = 0;
    for(int i = 0; i < dim; i++) suma += studenti[i].nota;
    return suma / dim;
}

void afisareStudenti(Student* studenti, int dim) {
    for(int i = 0; i < dim; i++)
        cout << studenti[i].nume << " - nota: " << studenti[i].nota << endl;
}

int main() {
    int dim;
    cout << "Cate note? ";
    cin >> dim;
    cin.ignore();

    Student* studenti = new Student[dim];
    for(int i = 0; i < dim; i++) {
        char buffer[50];
        cout << "Nume student " << i << ": ";
        cin.getline(buffer, 50);
        studenti[i].nume = new char[strlen(buffer)+1];
        strcpy(studenti[i].nume, buffer);

        cout << "Nota: ";
        cin >> studenti[i].nota;
        cin.ignore();
    }

    filtrareStudentiPrag(&studenti, &dim, 5.0);
    inverseazaStudenti(&studenti, dim);

    cout << "\nStudenti promovati (inversati):\n";
    afisareStudenti(studenti, dim);

    cout << "Media notelor: " << mediaNote(studenti, dim) << endl;

    for(int i = 0; i < dim; i++) delete[] studenti[i].nume;
    delete[] studenti;
}

