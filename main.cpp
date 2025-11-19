#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include "Vuelos.h"
using namespace std;

struct StatsCliente {
    int id;
    int vip = 0;
    int normal = 0;
    double gasto = 0;
};

void clienteFuncion(int id, Vuelos* vuelos, StatsCliente* stats) {

    stats->id = id;

    static thread_local mt19937 rng(
        (unsigned)chrono::steady_clock::now().time_since_epoch().count() + id
    );

    uniform_int_distribution<int> pickVuelo(0, vuelos->totalVuelos() - 1);
    uniform_int_distribution<int> pickTipo(0, 1); // 0=VIP, 1=Normal

    for (int i = 0; i < 6; i++) {

        int v = pickVuelo(rng);
        int tipo = pickTipo(rng);

        VueloDatos& vuelo = (*vuelos)[v];

        bool ok;

        if (tipo == 0) {
            ok = vuelo.comprarVIP(id);
            if (ok) {
                stats->vip++;
                stats->gasto += vuelo.getPrecioVIP();
            }
        }
        else {
            ok = vuelo.comprarNormal(id);
            if (ok) {
                stats->normal++;
                stats->gasto += vuelo.getPrecioNormal();
            }
        }

        this_thread::sleep_for(50ms);
    }
}

int main() {

    Vuelos vuelos;

    int numClientes;
    cout << "Ingrese número de clientes (10, 30 o 50): ";
    cin >> numClientes;

    vector<StatsCliente> stats(numClientes);
    vector<thread> hilos;
    hilos.reserve(numClientes);

    cout << "\nSimulando horarios...\n";
    this_thread::sleep_for(3s);
    cout << "Mañana...\n";
    this_thread::sleep_for(3s);
    cout << "Tarde...\n";
    this_thread::sleep_for(3s);
    cout << "Noche...\n\n";

    for (int i = 0; i < numClientes; i++)
        hilos.emplace_back(clienteFuncion, i+1, &vuelos, &stats[i]);

    for (auto& h : hilos) h.join();

    cout << "\n=== ESTADÍSTICAS POR CLIENTE ===\n";
    for (auto& s : stats) {
        cout << "Cliente " << s.id
             << " | VIP=" << s.vip
             << " | NORMAL=" << s.normal
             << " | Gasto=$" << s.gasto << "\n";
    }

    vuelos.mostrarVuelos();

    cout << "\n=== ESTADO FINAL DE ASIENTOS ===\n";
    for (int i = 0; i < vuelos.totalVuelos(); i++)
        vuelos[i].mostrarAsientos();

    return 0;
}
