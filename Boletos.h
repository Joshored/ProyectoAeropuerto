// Clase Boletos para manejar la compra de asientos
#ifndef BOLETOS_H
#define BOLETOS_H

#include <vector>
#include <string>
#include <mutex>

// Clase Boletos para manejar la compra de asientos
class Boletos {
private:
    std::string tipo; // tipo de boleto (VIP o Normal)
    double precio; // precio del boleto
    int numAsientos; // número total de asientos
    std::vector<int> asientos;   // 0 = libre, idCliente = ocupado
    std::mutex mtx; // mutex para sincronización

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

    void mostrarMapa(); // muestra el mapa de asientos

    int getNumAsientos() const { return numAsientos; }
    double getPrecio() const { return precio; } // devuelve el precio del boleto
    std::string getTipo() const { return tipo; } // devuelve el tipo de boleto
};

#endif