#include <iostream>
#include "lectorcsv.h"
using namespace std;

int main() {
    equipo* equipos = new equipo[48];
    int numEquipos = 0;

    lectorcsv lector("selecciones_clasificadas_mundial.csv");

    if (lector.leerEquipos(equipos, numEquipos)) {
        cout << "Equipos cargados: " << numEquipos << endl;

        equipo copia = equipos[0];
        cout << "\nCopia de France:" << endl;
        cout << copia << endl;

        copia.setPais("CopiaTest");
        cout << "\nDespues de modificar la copia:" << endl;
        cout << "Original: " << equipos[0].getPais() << endl;
        cout << "Copia: " << copia.getPais() << endl;

        jugador j1 = equipos[0].getPlantilla()[0];
        j1.setNombre("nombreTest");
        cout << "\nJugador original: " << equipos[0].getPlantilla()[0] << endl;
        cout << "Jugador copia: " << j1 << endl;
    }

    delete[] equipos;
    return 0;
}
