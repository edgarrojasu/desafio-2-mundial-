#ifndef ESTADISTICASEQUIPO_H
#define ESTADISTICASEQUIPO_H

#include <iostream>
using namespace std;

class estadisticasequipo
{
    private:
    int golesFavor;
    int golesContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

public:
    estadisticasequipo();
    estadisticasequipo(const estadisticasequipo& otra);

    int getGolesFavor() const;
    int getGolesContra() const;
    int getPartidosGanados() const;
    int getPartidosEmpatados() const;
    int getPartidosPerdidos() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;
    int getFaltas() const;

    void setGolesFavor(int valor);
    void setGolesContra(int valor);
    void setPartidosGanados(int valor);
    void setPartidosEmpatados(int valor);
    void setPartidosPerdidos(int valor);
    void setTarjetasAmarillas(int valor);
    void setTarjetasRojas(int valor);
    void setFaltas(int valor);

    estadisticasequipo& operator+=(const estadisticasequipo& otra);
    friend ostream& operator<<(ostream& os, const estadisticasequipo& stats);
};

#endif // ESTADISTICASEQUIPO_H
