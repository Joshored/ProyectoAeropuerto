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

    bool comprarAsiento(int idCliente);   // devuelve true si se pudo comprar

    void mostrarMapa();

    int getNumAsientos() const { return numAsientos; }
    double getPrecio() const { return precio; }
    std::string getTipo() const { return tipo; }
};

#endif
