#ifndef ESTADISTICASPARTIDO_H
#define ESTADISTICASPARTIDO_H

#include <iostream>
using namespace std;

class estadisticaspartido {
private:
    int golesFavor;
    int golesContra;
    float posesionBalon;
    int convocados[11];
    int golesConvocados[11];
    int tarjetasAmarillasConvocados[11];
    int tarjetasRojasConvocados[11];
    int faltasConvocados[11];
    int minutosJugados[11];

public:
    estadisticaspartido();
    estadisticaspartido(const estadisticaspartido& otra);

    int getGolesFavor() const;
    int getGolesContra() const;
    float getPosesionBalon() const;
    int getConvocado(int indice) const;
    int getGolesConvocado(int indice) const;
    int getTarjetasAmarillasConvocado(int indice) const;
    int getTarjetasRojasConvocado(int indice) const;
    int getFaltasConvocado(int indice) const;
    int getMinutosJugados(int indice) const;

    void setGolesFavor(int valor);
    void setGolesContra(int valor);
    void setPosesionBalon(float valor);
    void setConvocado(int indice, int camiseta);
    void setGolesConvocado(int indice, int valor);
    void setTarjetasAmarillasConvocado(int indice, int valor);
    void setTarjetasRojasConvocado(int indice, int valor);
    void setFaltasConvocado(int indice, int valor);
    void setMinutosJugados(int indice, int valor);

    friend ostream& operator<<(ostream& os, const estadisticaspartido& stats);
};

#endif // ESTADISTICASPARTIDO_H
