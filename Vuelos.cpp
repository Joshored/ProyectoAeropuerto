#include "Vuelos.h"
#include <iostream>
using namespace std;

Vuelos::Vuelos() {

    vector<string> destinos = { "Japon", "Brasil", "CU2" };
    vector<string> horarios = { "Mañana", "Tarde", "Noche" };

    for (const auto& d : destinos) {
        for (const auto& h : horarios) {

            lista.push_back(
                make_unique<VueloDatos>(
                    d,
                    h,
                    Boletos("VIP", 500, 50),
                    Boletos("Normal", 200, 300)
                )
            );
        }
    }
}

void Vuelos::mostrarVuelos() {
    cout << "\n--- Vuelos Disponibles (9) ---\n\n";
    for (int i = 0; i < lista.size(); i++) {
        cout << i+1 << ". " << lista[i]->getDestino()
             << " - " << lista[i]->getHorario() << endl;
    }
}

