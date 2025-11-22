// Implementación de la clase Vuelos
#include "Vuelos.h"
#include <iostream>
using namespace std;

Vuelos::Vuelos() {
    // Inicialmente solo 3 vuelos: Japon-Mañana, Brasil-Mañana, CU2-Mañana
    for (int i = 0; i < 3; i++) {
        lista.push_back(
            make_unique<VueloDatos>(
                destinos[i],
                "Mañana",
                Boletos("VIP", 500, 20),
                Boletos("Normal", 200, 100)
            )
        );
    }
    siguienteVuelo = 3; // el siguiente vuelo a crear será el índice 3
}

// Agrega un nuevo vuelo según la secuencia
bool Vuelos::agregarNuevoVuelo() {
    lock_guard<mutex> lock(mtxVuelos);

    if (siguienteVuelo >= 9) return false; // ya se crearon los 9 vuelos

    // Calcular destino y horario según el índice
    int destinoIdx = siguienteVuelo % 3;
    int horarioIdx = siguienteVuelo / 3;
    // Crear y agregar el nuevo vuelo
    lista.push_back(
        make_unique<VueloDatos>(
            destinos[destinoIdx],
            horarios[horarioIdx],
            Boletos("VIP", 500, 20),
            Boletos("Normal", 200, 100)
        )
    );
    // Notificar que se agregó un nuevo vuelo
    cout << "\n*** NUEVO VUELO AGREGADO: " << destinos[destinoIdx]
         << " - " << horarios[horarioIdx] << " ***\n";

    siguienteVuelo++;
    return true;
}

// Muestra la lista de vuelos disponibles
void Vuelos::mostrarVuelos() {
    lock_guard<mutex> lock(mtxVuelos);
    cout << "\n--- Vuelos Disponibles (" << lista.size() << ") ---\n\n";
    for (int i = 0; i < lista.size(); i++) {
        cout << i+1 << ". " << lista[i]->getDestino()
             << " - " << lista[i]->getHorario() << endl;
    }
}