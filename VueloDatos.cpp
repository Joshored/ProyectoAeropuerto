#include "VueloDatos.h"
#include <iostream>
using namespace std;

VueloDatos::VueloDatos(string destino_, string horario_,
                       Boletos vip, Boletos normal)
    : destino(destino_), horario(horario_),
      boletosVIP(vip), boletosNormal(normal) {}

bool VueloDatos::comprarVIP(int idCliente) {
    return boletosVIP.comprarAsiento(idCliente);
}

bool VueloDatos::comprarNormal(int idCliente) {
    return boletosNormal.comprarAsiento(idCliente);
}

void VueloDatos::mostrarAsientos() {
    cout << "\n=== " << destino << " (" << horario << ") ===\n";
    boletosVIP.mostrarMapa();
    boletosNormal.mostrarMapa();
}
