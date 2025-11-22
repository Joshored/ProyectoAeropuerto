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
    // Inicializar estadísticas del cliente
    stats->id = id;

    static thread_local mt19937 rng( // seed único por hilo
        (unsigned)chrono::steady_clock::now().time_since_epoch().count() + id
    );
    // Distribuciones para seleccionar vuelo y tipo de boleto
    uniform_int_distribution<int> pickVuelo(0, vuelos->totalVuelos() - 1); // Índices de vuelos
    uniform_int_distribution<int> pickTipo(0, 1); // 0=VIP, 1=Normal

    // Intentar comprar 6 boletos
    for (int i = 0; i < 6; i++) {
        // Seleccionar vuelo y tipo de boleto aleatoriamente
        int v = pickVuelo(rng);
        int tipo = pickTipo(rng);
        // Obtener referencia al vuelo seleccionado
        VueloDatos& vuelo = (*vuelos)[v];
        // Intentar comprar el boleto
        bool ok;
        // Comprar boleto según el tipo seleccionado
        if (tipo == 0) { // VIP
            ok = vuelo.comprarVIP(id);
            if (ok) {
                stats->vip++;
                stats->gasto += vuelo.getPrecioVIP();
            }
        }

        else { // Normal
            ok = vuelo.comprarNormal(id);
            if (ok) {
                stats->normal++;
                stats->gasto += vuelo.getPrecioNormal();
            }
        }
        // Simular tiempo de espera entre compras
        this_thread::sleep_for(50ms);
    }
}

int main() {

    Vuelos vuelos; //

    int numClientes;
    cout << "Ingrese número de clientes (10, 30 o 50): ";
    cin >> numClientes;

    vector<StatsCliente> stats(numClientes); // Estadísticas por cliente
    vector<thread> hilos; // Hilos para cada cliente
    hilos.reserve(numClientes); // Reservar espacio para los hilos

    cout << "\nSimulando horarios...\n";
    this_thread::sleep_for(3s);
    cout << "Mañana...\n";
    this_thread::sleep_for(3s);
    cout << "Tarde...\n";
    this_thread::sleep_for(3s);
    cout << "Noche...\n\n";

    for (int i = 0; i < numClientes; i++) // Crear hilos para cada cliente
        hilos.emplace_back(clienteFuncion, i+1, &vuelos, &stats[i]);

    for (auto& h : hilos) h.join();// Esperar a que todos los hilos terminen

    cout << "\n=== ESTADÍSTICAS POR CLIENTE ===\n";
    for (auto& s : stats) {// Mostrar estadísticas de cada cliente
        cout << "Cliente " << s.id
             << " | VIP=" << s.vip
             << " | NORMAL=" << s.normal
             << " | Gasto=$" << s.gasto << "\n";
    }

    vuelos.mostrarVuelos();// Mostrar lista de vuelos

    cout << "\n=== ESTADO FINAL DE ASIENTOS ===\n";
    for (int i = 0; i < vuelos.totalVuelos(); i++)// Mostrar mapa de asientos de cada vuelo
        vuelos[i].mostrarAsientos(); // Mostrar mapa de asientos

    return 0;
}
