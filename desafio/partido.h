#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include <cstring>
#include "equipo.h"
#include "estadisticaspartido.h"
using namespace std;

class partido {
private:
    char* fecha;
    char* hora;
    char* sede;
    char* arbitros[3];
    equipo* equipo1;
    equipo* equipo2;
    estadisticaspartido statsEquipo1;
    estadisticaspartido statsEquipo2;
    bool prorroga;
    bool jugado;

public:
    partido();
    partido(const partido& otro);
    ~partido();

    char* getFecha() const;
    char* getHora() const;
    char* getSede() const;
    char* getArbitro(int indice) const;
    equipo* getEquipo1() const;
    equipo* getEquipo2() const;
    estadisticaspartido& getStatsEquipo1();
    estadisticaspartido& getStatsEquipo2();
    bool isProrroga() const;
    bool isJugado() const;
    equipo* getGanador();

    void setFecha(const char* valor);
    void setHora(const char* valor);
    void setSede(const char* valor);
    void setArbitro(int indice, const char* valor);
    void setEquipo1(equipo* e);
    void setEquipo2(equipo* e);
    void setProrroga(bool valor);

    partido& operator=(const partido& otro);
    friend ostream& operator<<(ostream& os, const partido& p);
    void setJugado(bool valor);
};

#endif // PARTIDO_H
