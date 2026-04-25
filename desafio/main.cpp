#include <iostream>
#include <cstdlib>
#include <ctime>
#include "torneo.h"
using namespace std;

int main() {
    srand(time(nullptr));

    torneo t;
    t.cargarEquipos("selecciones_clasificadas_mundial.csv");
    t.conformarGrupos();
    t.simularFaseGrupos();
    t.configurarDieciseisavos();
    t.simularTorneo();
    t.generarEstadisticas();

    return 0;
}
