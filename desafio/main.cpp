#include <iostream>
#include <cstdlib>
#include <ctime>
#include "lectorcsv.h"
#include "sorteo.h"
using namespace std;

int main()
{
    srand(time(nullptr));

    equipo* equipos = new equipo[48];
    int numEquipos = 0;

    lectorcsv lector("selecciones_clasificadas_mundial.csv");
    lector.leerEquipos(equipos, numEquipos);

    sorteo s;
    s.armarBombos(equipos, numEquipos);
    s.formarGrupos();
    s.imprimirGrupos();

    delete[] equipos;
    return 0;
}
