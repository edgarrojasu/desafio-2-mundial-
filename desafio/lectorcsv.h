#ifndef LECTORCSV_H
#define LECTORCSV_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "equipo.h"
using namespace std;

class lectorcsv {
private:
    char* nombreArchivo;

public:
    lectorcsv(const char* archivo);
    lectorcsv(const lectorcsv& otro);
    ~lectorcsv();

    bool leerEquipos(equipo* equipos, int& numEquipos);
    void escribirJugadores(equipo* equipos, int numEquipos);
    void leerJugadores(equipo* equipos, int numEquipos);
};

#endif // LECTORCSV_H
