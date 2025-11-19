//
// Created by fer on 16/11/2025.
//
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
#include "Boletos.h"

Boletos::Boletos(string t, double p, int n)
    : tipo(t), precio(p), numAsientos(n), asientos(n, false) {}

void Boletos::comprarAsiento(int idCliente){
    int asiento;

    cout << "\nCliente " << idCliente << ", ingresa el número de asiento que quieres comprar: ";
    cin >> asiento;

    if (asiento < 1 || asiento > numAsientos) {
        cout << "Ese asiento no existe \n";
        return;
    }
    int index=asiento-1;//-1
    lock_guard<mutex> lock(mtx); // proteger acceso a los asientos
    //int index=asiento-1;
    if (!asientos[index]) {
        asientos[index] = true;
        cout << "Cliente " << idCliente << " compro el asiento " << asiento <<"  costo de boleto:$"<<precio<< "\n";
    } else {
        cout << "Cliente " << idCliente << " intentó comprar el asiento "
             << asiento << " pero ya estaba ocupado \n";
    }
}

//Muestra los asientos (en forma de mapa)
void Boletos::mostrarMapa() {
    cout << "\nMapa de asientos (" << tipo << ")  [O=Ocupado, _=Libre]\n";
    for (int i = 1; i <= numAsientos; i++) {
        cout << i<<" " ; //esto es para saber el numero del lugar que desea el cliente
        cout << (asientos[i-1] ? "O " : "_ ");
        if (i  % 15 == 0) cout << endl;
    }
    cout << endl;
}
int Boletos::getNumAsientos() const {
    return numAsientos;
}
