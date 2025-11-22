// Clase Boletos para manejar la compra de asientos
#ifndef BOLETOS_H
#define BOLETOS_H

#include <vector>
#include <string>
#include <mutex>

// Clase Boletos para manejar la compra de asientos
class Boletos {
private:
    std::string tipo;
    double precio;
    int numAsientos;
    std::vector<int> asientos;   // 0 = libre, idCliente = ocupado
    int asientosOcupados;         // contador de asientos ocupados
    std::mutex mtx;

public:
    Boletos(std::string t, double p, int n);

    // Constructor de movimiento
    Boletos(Boletos&& other) noexcept
        : tipo(std::move(other.tipo)),
          precio(other.precio),
          numAsientos(other.numAsientos),
          asientos(std::move(other.asientos)),
          asientosOcupados(other.asientosOcupados),
          mtx() {}

    // Eliminar constructor de copia y operador de asignación
    Boletos(const Boletos&) = delete;
    Boletos& operator=(const Boletos&) = delete;

    bool comprarAsiento(int idCliente);
    bool estaLleno() const; // verifica si todos los asientos están ocupados
    void mostrarMapa();

    int getNumAsientos() const { return numAsientos; }
    double getPrecio() const { return precio; }
    std::string getTipo() const { return tipo; }
};

#endif