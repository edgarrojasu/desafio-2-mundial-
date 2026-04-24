#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include <cstring>
#include "equipo.h"
#include "partido.h"
using namespace std;

class grupo {
private:
    char letra;
    equipo* equipos[4];
    partido* partidos[6];
    int numEquipos;
    int numPartidos;

public:
    grupo();
    grupo(const grupo& otro);
    ~grupo();

    char getLetra() const;
    equipo* getEquipo(int indice) const;
    partido* getPartido(int indice) const;
    int getNumEquipos() const;
    int getNumPartidos() const;

    void setLetra(char valor);
    void agregarEquipo(equipo* e);
    void agregarPartido(partido* p);

    bool tieneConfederacion(const char* confederacion) const;
    int contarConfederacion(const char* confederacion) const;
    void tablaClasificacion() const;
    void ordenarEquipos();

    grupo& operator=(const grupo& otro);
    friend ostream& operator<<(ostream& os, const grupo& g);
};

#endif // GRUPO_H
