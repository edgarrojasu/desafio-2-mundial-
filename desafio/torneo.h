#ifndef TORNEO_H
#define TORNEO_H

#include <iostream>
#include <cstring>
#include "lectorcsv.h"
#include "sorteo.h"
#include "fixture.h"
#include "simulador.h"
using namespace std;

class torneo {
private:
    equipo* equipos;
    int numEquipos;
    sorteo* sorteoGrupos;
    fixture* etapas[7];
    simulador sim;
    int numEtapas;

public:
    torneo();
    torneo(const torneo& otro);
    ~torneo();

    void cargarEquipos(const char* archivo);
    void conformarGrupos();
    void simularFaseGrupos();
    void configurarDieciseisavos();
    void simularEtapa(int indice);
    void simularTorneo();
    void generarEstadisticas();
    void imprimirTablas() const;

    torneo& operator=(const torneo& otro);
    friend ostream& operator<<(ostream& os, const torneo& t);
};

#endif // TORNEO_H
