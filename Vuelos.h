#ifndef VUELOS_H
#define VUELOS_H

#include <vector>
#include <memory>
#include "VueloDatos.h"

class Vuelos {
private:
    std::vector<std::unique_ptr<VueloDatos>> lista;

public:
    Vuelos();

    int totalVuelos() const { return lista.size(); }

    VueloDatos& operator[](int i) { return *lista[i]; }

    void mostrarVuelos();
};

#endif
