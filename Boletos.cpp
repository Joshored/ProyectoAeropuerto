// Implementación de la clase Boletos
#include "Boletos.h"
#include <iostream>
using namespace std;

// Constructor de la clase Boletos
Boletos::Boletos(string t, double p, int n)
    : tipo(t), precio(p), numAsientos(n), asientos(n, 0), asientosOcupados(0) {}

// Compra un asiento para el cliente con idCliente
bool Boletos::comprarAsiento(int idCliente) {
    lock_guard<mutex> lock(mtx);

    // Buscar un asiento libre
    for (int i = 0; i < numAsientos; i++) {
        if (asientos[i] == 0) {
            asientos[i] = idCliente;
            asientosOcupados++;
            return true;
        }
    }
    return false;
}

// Verifica si todos los asientos están ocupados
bool Boletos::estaLleno() const {
    return asientosOcupados >= numAsientos;
}

// Muestra el mapa de asientos
void Boletos::mostrarMapa() {
    cout << "\n[" << tipo << "] 0 = libre, id = ocupado\n";
    for (int i = 0; i < numAsientos; i++) {
        cout << i+1 << ":" << asientos[i] << " ";
        if ((i+1) % 15 == 0) cout << endl;
    }
    cout << endl;
}