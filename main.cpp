#include <iostream>
#include <thread>
#include <vector>
#include "Boletos.h" //para llamar a la clase boletos
#include "Vuelos.h"
using namespace std;

int main () {
    int opc;
    Boletos BoletosVIP("VIP", 3500, 50);
    Boletos BoletosNormal("Normal", 1200, 300);
    do {
        cout<<"----------AEROLINEA (NOMBRE)----------"<<endl;
        cout<<"---Bienvenido que desea realizar---"<<endl;
        cout<<"1.Boletos"<<endl;
        cout<<"2.Vuelos disponibles"<<endl;
        cout<<"3.Salir"<<endl;
        cout<<"Ingrese la opcion: ";
        cin>>opc;
        switch(opc){
            case 1:
            int opc_Boleto;
            do {
                cout << "\n---- AEROLÍNEA ----\n";
                cout<<"Seleccionar boleto: "<<endl;
                cout<<"1.VIP(50 asientos)"<<endl;
                cout<<"2.NORMAL(300 asientos)"<<endl;
                cout<<"3.Regresar"<<endl;
                cout<<"Ingrese el tipo de boleto a seleccionar o regrese: ";
                cin>>opc_Boleto;

                if (opc_Boleto == 3) {
                    cout << "Saliendo del apartado de Boletos...\n";
                    break;
                }
                if (opc_Boleto != 1 && opc_Boleto != 2) {
                    cout << "Opcion invalida\n";
                    continue;
                }

                Boletos* vueloSeleccionado = (opc_Boleto == 1) ? &BoletosVIP : &BoletosNormal;
                vueloSeleccionado->mostrarMapa();
                //pasa saber cuantos pasejeros para subir a un avión
                int numClientes;
                cout << "Ingrese el numero de pasajeros: "<<endl;
                cin >> numClientes;

                vector<thread> clientes;
                clientes.reserve(numClientes);

                for (int i = 1; i <= numClientes; i++) {
                    clientes.emplace_back(&Boletos::comprarAsiento,vueloSeleccionado, i);
                }

                for (auto& c : clientes) {
                    c.join();
                }

                // Mostrar el mapa final
                vueloSeleccionado->mostrarMapa();
            }while (opc_Boleto !=3);
            break;
                //este caso es para ver los vuelos que estan
            case 2:
                int opc_vuelo;
                do {
                    cout << "\n---- AEROLÍNEA ----\n";
                    cout << "1. Ver vuelos disponibles\n";
                    cout << "2. Salir\n";
                    cout << "Ingrese opción: ";
                    cin >> opc_vuelo;

                    if (opc == 1) {
                        Vuelos vuelos;
                        vuelos.mostrarVuelos();

                        int idVuelo;
                        cout << "Seleccione un vuelo: ";
                        cin >> idVuelo;

                        auto* vuelo = vuelos.seleccionarVuelo(idVuelo);

                        if (!vuelo) {
                            cout << "Vuelo inválido\n";
                            continue;
                        }

                        vuelo->mostrarAsientos();
                        vuelo->comprarAsientos();
                        vuelo->mostrarAsientos();
                    }


                }while (opc_vuelo != 2);

        }
    }while (opc != 3);
    if (opc==3) {
        cout<<"Gracias por ocupar nuestra aerolinea"<<endl;
    }
return 0;
}