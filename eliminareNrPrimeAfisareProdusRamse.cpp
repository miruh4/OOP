#include <iostream>
using namespace std;

bool estePrim(int x) {
    if(x < 2) return false;
    for(int i = 2; i*i <= x; i++)
        if(x % i == 0) return false;
    return true;
}

void eliminaPrime(int** vector, int* dim) {
    int* aux = new int[*dim];
    int j = 0;
    for(int i = 0; i < *dim; i++) {
        if(!estePrim((*vector)[i])) aux[j++] = (*vector)[i];
    }
    delete[] (*vector);
    *dim = j;
    *vector = aux;
}

long long produsVector(int* vector, int dim) {
    if(dim == 0) return 0;
    long long produs = 1;
    for(int i = 0; i < dim; i++) produs *= vector[i];
    return produs;
}

void afisareVector(int* vector, int dim) {
    for(int i = 0; i < dim; i++) cout << vector[i] << " ";
    cout << endl;
}

int main() {
    int dim;
    cout << "Cate numere? ";
    cin >> dim;

    int* vector = new int[dim];
    for(int i = 0; i < dim; i++) cin >> vector[i];

    eliminaPrime(&vector, &dim);

    cout << "\nVectorul dupa eliminarea numerelor prime: ";
    afisareVector(vector, dim);

    cout << "Produsul numerelor ramase: " << produsVector(vector, dim) << endl;

    delete[] vector;
}


