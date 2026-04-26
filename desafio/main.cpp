#include <iostream>
#include <cstdlib>
#include <ctime>
#include "torneo.h"
using namespace std;

void mostrarMenu()
{
    cout << "\n";
    cout << "========================================" << endl;
    cout << "         UdeAWorldCup FIFA 2026         " << endl;
    cout << "========================================" << endl;
    cout << "  1. Iniciar simulacion completa" << endl;
    cout << "  2. Ver estadisticas finales" << endl;
    cout << "  3. Guardar datos de jugadores" << endl;
    cout << "  0. Salir" << endl;
    cout << "========================================" << endl;
    cout << "Seleccione una opcion: ";
}

int main()
{
    srand(time(nullptr));

    torneo t;
    bool torneoSimulado = false;

    int opcion = -1;
    while (opcion != 0)
    {
        mostrarMenu();
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "\nCargando equipos..." << endl;
            t.cargarEquipos("selecciones_clasificadas_mundial.csv");

            cout << "\nConformando grupos..." << endl;
            t.conformarGrupos();

            cout << "\nSimulando fase de grupos..." << endl;
            t.simularFaseGrupos();

            cout << "\nConfigurando dieciseisavos..." << endl;
            t.configurarDieciseisavos();

            cout << "\nSimulando eliminacion directa..." << endl;
            t.simularTorneo();

            torneoSimulado = true;
            cout << "\nSimulacion completada." << endl;
            break;

        case 2:
            if (!torneoSimulado)
            {
                cout << "Primero debe iniciar la simulacion (opcion 1)." << endl;
                break;
            }
            t.generarEstadisticas();
            break;

        case 3:
            if (!torneoSimulado)
            {
                cout << "Primero debe iniciar la simulacion (opcion 1)." << endl;
                break;
            }
            {
                lectorcsv escritor("selecciones_clasificadas_mundial.csv");
                escritor.escribirJugadores(t.getEquipos(), t.getNumEquipos());
            }
            break;

        case 0:
            cout << "Saliendo..." << endl;
            break;

        default:
            cout << "Opcion invalida." << endl;
            break;
        }
    }

    return 0;
}
