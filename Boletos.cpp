// Implementación de la clase Boletos
#include "Boletos.h"
#include <iostream>
using namespace std;

// Constructor de la clase Boletos
Boletos::Boletos(string t, double p, int n)
    : tipo(t), precio(p), numAsientos(n), asientos(n, 0) {}

// Compra un asiento para el cliente con idCliente
bool Boletos::comprarAsiento(int idCliente) {
    lock_guard<mutex> lock(mtx);

    // Buscar un asiento libre
    for (int i = 0; i < numAsientos; i++) {
        if (asientos[i] == 0) {
            asientos[i] = idCliente;
            return true;
        }
    }
    return false;
}

// Muestra el mapa de asientos
void Boletos::mostrarMapa() {
    cout << "\n[" << tipo << "] 0 = libre, id = ocupado\n"; // Encabezado del mapa
    for (int i = 0; i < numAsientos; i++) { // Mostrar cada asiento
        cout << i+1 << ":" << asientos[i] << " "; // Mostrar número de asiento y estado
        if ((i+1) % 15 == 0) cout << endl; // Salto de línea cada 15 asientos
    }
    cout << endl; // Nueva línea al final
}
