#ifndef BOLETOS_H
#define BOLETOS_H

#include <vector>
#include <string>
#include <mutex>

class Boletos {
private:
    std::string tipo;
    double precio;
    int numAsientos;
    std::vector<int> asientos;   // 0 = libre, idCliente = ocupado
    std::mutex mtx;

public:
    Boletos(std::string t, double p, int n);

    // Constructor de movimiento
    Boletos(Boletos&& other) noexcept
        : tipo(std::move(other.tipo)),
          precio(other.precio),
          numAsientos(other.numAsientos),
          asientos(std::move(other.asientos)),
          mtx() {}  // mutex se inicializa vacío

    // Eliminar constructor de copia y operador de asignación
    Boletos(const Boletos&) = delete;
    Boletos& operator=(const Boletos&) = delete;

    bool comprarAsiento(int idCliente);   // devuelve true si se pudo comprar

    void mostrarMapa();

    int getNumAsientos() const { return numAsientos; }
    double getPrecio() const { return precio; }
    std::string getTipo() const { return tipo; }
};

#endif