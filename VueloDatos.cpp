// Implementación de la clase VueloDatos
#include "VueloDatos.h"
#include <iostream>
using namespace std;

// Constructor modificado para usar move semantics
VueloDatos::VueloDatos(string destino_, string horario_,
                       Boletos&& vip, Boletos&& normal)
    : destino(destino_), horario(horario_),
      boletosVIP(std::move(vip)), boletosNormal(std::move(normal)) {}

// Compra un asiento VIP para el cliente con idCliente
bool VueloDatos::comprarVIP(int idCliente) {
    return boletosVIP.comprarAsiento(idCliente);
}

// Compra un asiento normal para el cliente con idCliente
bool VueloDatos::comprarNormal(int idCliente) {
    return boletosNormal.comprarAsiento(idCliente);
}

// Verifica si el vuelo está completamente lleno
bool VueloDatos::estaLleno() const {
    return boletosVIP.estaLleno() && boletosNormal.estaLleno();
}

// Muestra el mapa de asientos del vuelo
void VueloDatos::mostrarAsientos() {
    cout << "\n=== " << destino << " (" << horario << ") ===\n";
    boletosVIP.mostrarMapa();
    boletosNormal.mostrarMapa();
}