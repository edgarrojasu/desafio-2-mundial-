#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <cstring>
#include <string>
#include "jugador.h"
#include "estadisticasequipo.h"
using namespace std;

class equipo {
private:
    char* pais;
    char* confederacion;
    char* directorTecnico;
    int rankingFIFA;
    jugador* plantilla;
    int numJugadores;
    estadisticasequipo statsHistoricas;
    int puntos;
    int diferenciaGoles;

public:
    equipo();
    equipo(const equipo& otro);
    ~equipo();

    char* getPais() const;
    char* getConfederacion() const;
    char* getDirectorTecnico() const;
    int getRankingFIFA() const;
    jugador* getPlantilla() const;
    int getNumJugadores() const;
    estadisticasequipo& getStatsHistoricas();
    int getPuntos() const;
    int getDiferenciaGoles() const;

    void setPais(const char* valor);
    void setConfederacion(const char* valor);
    void setDirectorTecnico(const char* valor);
    void setRankingFIFA(int valor);
    void setPuntos(int valor);
    void setDiferenciaGoles(int valor);

    void generarPlantilla();

    equipo& operator=(const equipo& otro);
    bool operator<(const equipo& otro) const;
    friend ostream& operator<<(ostream& os, const equipo& e);
};

#endif // EQUIPO_H
