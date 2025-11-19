#include "Boletos.h"
#include <iostream>
using namespace std;

Boletos::Boletos(string t, double p, int n)
    : tipo(t), precio(p), numAsientos(n), asientos(n, 0) {}

bool Boletos::comprarAsiento(int idCliente) {
    lock_guard<mutex> lock(mtx);

    for (int i = 0; i < numAsientos; i++) {
        if (asientos[i] == 0) {
            asientos[i] = idCliente;
            return true;
        }
    }
    return false;
}

void Boletos::mostrarMapa() {
    cout << "\n[" << tipo << "] 0 = libre, id = ocupado\n";
    for (int i = 0; i < numAsientos; i++) {
        cout << i+1 << ":" << asientos[i] << " ";
        if ((i+1) % 15 == 0) cout << endl;
    }
    cout << endl;
}
