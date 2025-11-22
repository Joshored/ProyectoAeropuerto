// Definición de la clase Vuelos que maneja una colección de vuelos
#ifndef VUELOS_H
#define VUELOS_H

#include <vector>
#include <memory>
#include "VueloDatos.h"

// Clase Vuelos que maneja una lista de vuelos
class Vuelos {
private:
    std::vector<std::unique_ptr<VueloDatos>> lista;

public:
    Vuelos(); // Constructor que inicializa la lista de vuelos

    int totalVuelos() const { return lista.size(); } // devuelve el total de vuelos

    VueloDatos& operator[](int i) { return *lista[i]; } // acceso a vuelo por índice

    void mostrarVuelos(); // muestra la lista de vuelos disponibles
};

#endif
