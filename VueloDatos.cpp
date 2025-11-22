// Implementación de la clase VueloDatos
#include "VueloDatos.h"
#include <iostream>
using namespace std;

// Constructor modificado para usar move semantics
VueloDatos::VueloDatos(string destino_, string horario_,
                       Boletos&& vip, Boletos&& normal)
    : destino(destino_), horario(horario_), // Inicializa los atributos de destino y horario
      boletosVIP(std::move(vip)), boletosNormal(std::move(normal)) {} // Mueve los objetos Boletos

// para evitar copias innecesarias
bool VueloDatos::comprarVIP(int idCliente) {
    return boletosVIP.comprarAsiento(idCliente);
}

// Compra un asiento normal para el cliente con idCliente
bool VueloDatos::comprarNormal(int idCliente) {
    return boletosNormal.comprarAsiento(idCliente);
}

// Muestra el mapa de asientos del vuelo
void VueloDatos::mostrarAsientos() {
    cout << "\n=== " << destino << " (" << horario << ") ===\n"; // Muestra el encabezado con destino y horario
    boletosVIP.mostrarMapa(); // Muestra el mapa de asientos VIP
    boletosNormal.mostrarMapa(); // Muestra el mapa de asientos normales
}