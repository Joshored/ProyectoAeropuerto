// Definición de la clase Vuelos que maneja una colección de vuelos
#ifndef VUELOS_H
#define VUELOS_H

#include <vector>
#include <memory>
#include <mutex>
#include "VueloDatos.h"

// Clase Vuelos que maneja una lista de vuelos
class Vuelos {
private:
    std::vector<std::unique_ptr<VueloDatos>> lista;
    std::vector<std::string> destinos = { "Japon", "Brasil", "CU2" };
    std::vector<std::string> horarios = { "Mañana", "Tarde", "Noche" };
    int siguienteVuelo = 0; // índice del siguiente vuelo a crear (0-8)
    std::mutex mtxVuelos;

public:
    Vuelos(); // Constructor que inicializa la lista de vuelos

    int totalVuelos() const { return lista.size(); } // devuelve el total de vuelos

    VueloDatos& operator[](int i) { return *lista[i]; } // acceso a vuelo por índice

    void mostrarVuelos(); // muestra la lista de vuelos disponibles

    bool agregarNuevoVuelo(); // agrega un nuevo vuelo, retorna false si ya no hay más
};

#endif