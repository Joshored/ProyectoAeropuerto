// Implementación de la clase Vuelos
#include "Vuelos.h"
#include <iostream>
using namespace std;

Vuelos::Vuelos() { // Constructor que inicializa la lista de vuelos
    // Definir destinos y horarios
    vector<string> destinos = { "Japon", "Brasil", "CU2" };
    vector<string> horarios = { "Mañana", "Tarde", "Noche" };
    // Crear combinaciones de vuelos
    for (const auto& d : destinos) {
        for (const auto& h : horarios) {
            // Agregar un nuevo vuelo a la lista usando make_unique
            lista.push_back(
                make_unique<VueloDatos>(
                    d,
                    h,
                    Boletos("VIP", 500, 20),
                    Boletos("Normal", 200, 100)
                )
            );
        }
    }
}
// Muestra la lista de vuelos disponibles
void Vuelos::mostrarVuelos() {
    cout << "\n--- Vuelos Disponibles (9) ---\n\n";
    for (int i = 0; i < lista.size(); i++) {
        cout << i+1 << ". " << lista[i]->getDestino()
             << " - " << lista[i]->getHorario() << endl;
    }
}

