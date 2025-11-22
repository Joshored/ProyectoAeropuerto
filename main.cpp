// Simulación de compra de boletos de vuelos con múltiples clientes (hilos)
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include "Vuelos.h"
using namespace std;

// Estructura para almacenar estadísticas de cada cliente
struct StatsCliente {
    int id;
    int vip = 0;
    int normal = 0;
    double gasto = 0;
};

// Función que simula la actividad de un cliente
void clienteFuncion(int id, Vuelos* vuelos, StatsCliente* stats) {
    stats->id = id;

    static thread_local mt19937 rng(
        (unsigned)chrono::steady_clock::now().time_since_epoch().count() + id
    );

    uniform_int_distribution<int> pickTipo(0, 1); // 0=VIP, 1=Normal

    // Intentar comprar 50 boletos
    for (int i = 0; i < 50; i++) {
        // Seleccionar vuelo aleatorio de los disponibles
        int numVuelos = vuelos->totalVuelos();
        uniform_int_distribution<int> pickVuelo(0, numVuelos - 1);
        int v = pickVuelo(rng);
        int tipo = pickTipo(rng);

        VueloDatos& vuelo = (*vuelos)[v];
        bool ok = false;

        // Intentar comprar según tipo
        if (tipo == 0) { // VIP
            ok = vuelo.comprarVIP(id);
            if (ok) {
                stats->vip++;
                stats->gasto += vuelo.getPrecioVIP();
            }
        } else { // Normal
            ok = vuelo.comprarNormal(id);
            if (ok) {
                stats->normal++;
                stats->gasto += vuelo.getPrecioNormal();
            }
        }

        // Si la compra fue exitosa, verificar si el vuelo se llenó
        if (ok && vuelo.estaLleno()) {
            vuelos->agregarNuevoVuelo();
        }

        // Simular tiempo entre compras
        this_thread::sleep_for(50ms);
    }
}

int main() {
    Vuelos vuelos;
    // Pedir número de clientes
    int numClientes;
    cout << "Ingrese número de clientes (10, 30 o 50): ";
    cin >> numClientes;
    // Vector para almacenar estadísticas de cada cliente
    vector<StatsCliente> stats(numClientes);
    vector<thread> hilos;
    hilos.reserve(numClientes);
    // Simular el paso del tiempo
    cout << "\nSimulando horarios...\n";
    this_thread::sleep_for(3s);
    cout << "Mañana...\n";
    this_thread::sleep_for(3s);
    cout << "Tarde...\n";
    this_thread::sleep_for(3s);
    cout << "Noche...\n\n";
    // Iniciar hilos para cada cliente
    for (int i = 0; i < numClientes; i++)
        hilos.emplace_back(clienteFuncion, i+1, &vuelos, &stats[i]);

    for (auto& h : hilos) h.join();
    // Mostrar estadísticas por cliente
    cout << "\n=== ESTADÍSTICAS POR CLIENTE ===\n";
    for (auto& s : stats) {
        cout << "Cliente " << s.id
             << " | VIP=" << s.vip
             << " | NORMAL=" << s.normal
             << " | Gasto=$" << s.gasto << "\n";
    }

    vuelos.mostrarVuelos();
    // Mostrar el estado final de los asientos en cada vuelo
    cout << "\n=== ESTADO FINAL DE ASIENTOS ===\n";
    for (int i = 0; i < vuelos.totalVuelos(); i++)
        vuelos[i].mostrarAsientos();

    return 0;
}