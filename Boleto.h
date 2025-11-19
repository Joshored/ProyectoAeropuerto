//
// Created by fer on 18/11/2025.
//

#ifndef C___CLION__VUELOS_H
#define C___CLION__VUELOS_H
#include <string>
#include <vector>
#include<mutex>
#include "Boletos.h"
using namespace std;
class VueloDatos {
private:
    string destino;
    Boletos boletos;
public:
    VueloDatos(string destino, string tipo,double precio, int asiento);

    //VueloDatos();

    string getDestino();
    void mostrarAsientos();
    void comprarAsientos();
};
class Vuelos {
private:
    vector <VueloDatos> lista;
public:
    Vuelos();

    void mostrarVuelos();
    VueloDatos * seleccionarVuelo(int id);
};



#endif //C___CLION__VUELOS_H