#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <cstring>
#include "estadisticasjugador.h"
using namespace std;

class jugador {
private:
    char* nombre;
    char* apellido;
    int numeroCamiseta;
    estadisticasjugador stats;

public:
    jugador();
    jugador(const jugador& otro);
    ~jugador();

    char* getNombre() const;
    char* getApellido() const;
    int getNumeroCamiseta() const;
    estadisticasjugador& getStats();

    void setNombre(const char* valor);
    void setApellido(const char* valor);
    void setNumeroCamiseta(int valor);

    jugador& operator=(const jugador& otro);
    bool operator==(const jugador& otro) const;
    friend ostream& operator<<(ostream& os, const jugador& j);
};

#endif // JUGADOR_H
