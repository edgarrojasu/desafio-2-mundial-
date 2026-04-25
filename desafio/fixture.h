#ifndef FIXTURE_H
#define FIXTURE_H

#include <iostream>
#include <cstring>
#include "grupo.h"
#include "simulador.h"
using namespace std;

class fixture {
private:
    char* nombreEtapa;
    partido** partidos;
    int numPartidos;
    int capacidad;
    equipo** clasificados;
    int numClasificados;

public:
    fixture();
    fixture(const char* etapa);
    fixture(const fixture& otro);
    ~fixture();

    char* getNombreEtapa() const;
    partido* getPartido(int indice) const;
    int getNumPartidos() const;
    equipo* getClasificado(int indice) const;
    int getNumClasificados() const;

    void agregarPartido(partido* p);
    void agregarClasificado(equipo* e);
    void setNombreEtapa(const char* nombre);

    void simularEtapa(simulador& sim, bool permitirEmpate);
    void imprimirResultados() const;
    void imprimirGoleadores() const;

    fixture& operator=(const fixture& otro);
    friend ostream& operator<<(ostream& os, const fixture& f);
};

#endif // FIXTURE_H
