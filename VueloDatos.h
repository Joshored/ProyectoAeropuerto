// Clase VueloDatos que contiene la información de un vuelo
#ifndef VUELODATOS_H
#define VUELODATOS_H

#include <string>
#include "Boletos.h"

// Clase VueloDatos que contiene la información de un vuelo
class VueloDatos {
private:
    std::string destino;
    std::string horario;
    Boletos boletosVIP;
    Boletos boletosNormal;

public:
    // Constructor modificado para usar move semantics
    VueloDatos(std::string destino_, std::string horario_,
               Boletos&& vip, Boletos&& normal);

    bool comprarVIP(int idCliente);
    bool comprarNormal(int idCliente);
    bool estaLleno() const; // verifica si el vuelo está completamente lleno

    std::string getDestino() const { return destino; }
    std::string getHorario() const { return horario; }
    double getPrecioVIP() const { return boletosVIP.getPrecio(); }
    double getPrecioNormal() const { return boletosNormal.getPrecio(); }

    void mostrarAsientos();
};

#endif