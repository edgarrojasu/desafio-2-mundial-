#ifndef ESTADISTICASJUGADOR_H
#define ESTADISTICASJUGADOR_H

#include <iostream>
using namespace std;

class estadisticasjugador
{
    private:
    int goles;
    int asistencias;
    int minutosJugados;
    int partidosJugados;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

public:
    estadisticasjugador();
    estadisticasjugador(const estadisticasjugador& otra);

    int getGoles() const;
    int getAsistencias() const;
    int getMinutosJugados() const;
    int getPartidosJugados() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;
    int getFaltas() const;

    void setGoles(int valor);
    void setAsistencias(int valor);
    void setMinutosJugados(int valor);
    void setPartidosJugados(int valor);
    void setTarjetasAmarillas(int valor);
    void setTarjetasRojas(int valor);
    void setFaltas(int valor);

    estadisticasjugador& operator+=(const estadisticasjugador& otra);
    estadisticasjugador& operator=(const estadisticasjugador& otra);
    friend ostream& operator<<(ostream& os, const estadisticasjugador& stats);
};

#endif // ESTADISTICASJUGADOR_H
