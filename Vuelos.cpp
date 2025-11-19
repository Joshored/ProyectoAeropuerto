//
// Created by fer on 18/11/2025.
//

#include "Vuelos.h"
#include <iostream>
#include <thread>
using namespace std;

VueloDatos::VueloDatos(string destino, string tipo, double precio, int asientos)
    : destino(destino), boletos(tipo, precio, asientos) {}

string VueloDatos::getDestino() {
    return destino;
}

void VueloDatos::mostrarAsientos() {
    boletos.mostrarMapa();
}

void VueloDatos::comprarAsientos() {
    int numClientes;
    cout << "¿Cuántos pasajeros comprarán? ";
    cin >> numClientes;

    vector<thread> hilos(numClientes);

    for (int i = 0; i < numClientes; i++) {
        hilos[i] = thread(&Boletos::comprarAsiento, &boletos, i+1);
    }

    for (auto& h : hilos) h.join();
}

//Vuelos::VueloDatos(){
//lista.push_back(VueloDatos("CANCUN","VIP",3500,50));
//}

Vuelos::Vuelos() {
    lista.push_back(VueloDatos("Cancún","VIP",3500,50));
    lista.push_back(VueloDatos("Tijuana", "Normal", 1200, 300));
    lista.push_back(VueloDatos("Guadalajara", "VIP", 3800, 50));
    lista.push_back(VueloDatos("Monterrey", "Normal", 1500, 300));
}

void Vuelos::mostrarVuelos() {
    cout << "\n--- Vuelos Disponibles ---\n";
    for (int i = 0; i < lista.size(); i++) {
        cout << i+1 << ". " << lista[i].getDestino() << endl;
    }
}

VueloDatos* Vuelos::seleccionarVuelo(int id) {
    if (id < 1 || id > lista.size()) return nullptr;
    return &lista[id - 1];
}
