#ifndef SORTEO_H
#define SORTEO_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "equipo.h"
#include "grupo.h"
using namespace std;

class sorteo {
private:
    equipo* bombos[4][12];
    int tamBombos[4];
    grupo* grupos;
    int numGrupos;

public:
    sorteo();
    sorteo(const sorteo& otro);
    ~sorteo();

    grupo* getGrupos() const;
    grupo& getGrupo(int indice) const;
    int getNumGrupos() const;

    void armarBombos(equipo* equipos, int numEquipos);
    void formarGrupos();
    void imprimirGrupos() const;

    sorteo& operator=(const sorteo& otro);
    friend ostream& operator<<(ostream& os, const sorteo& s);

private:
    void ordenarPorRanking(equipo** lista, int tam);
    bool puedeAgregarseAlGrupo(grupo& g, equipo* e) const;
};

#endif // SORTEO_H
