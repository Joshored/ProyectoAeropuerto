// Clase VueloDatos que contiene la información de un vuelo
#ifndef VUELODATOS_H
#define VUELODATOS_H

#include <string>
#include "Boletos.h"

// Clase VueloDatos que contiene la información de un vuelo
class VueloDatos {
private:
    std::string destino; // destino del vuelo
    std::string horario;// horario del vuelo

    Boletos boletosVIP;
    Boletos boletosNormal;

public:
    // Constructor modificado para usar move semantics
    VueloDatos(std::string destino_, std::string horario_,
               Boletos&& vip, Boletos&& normal);

    bool comprarVIP(int idCliente); // devuelve true si se pudo comprar
    bool comprarNormal(int idCliente); // devuelve true si se pudo comprar


    std::string getDestino() const { return destino; }  // devuelve el destino
    std::string getHorario() const { return horario; }  // devuelve el horario

    double getPrecioVIP() const { return boletosVIP.getPrecio(); } // devuelve el precio VIP
    double getPrecioNormal() const { return boletosNormal.getPrecio(); } // devuelve el precio Normal

    void mostrarAsientos(); // muestra el mapa de asientos
};

#endif