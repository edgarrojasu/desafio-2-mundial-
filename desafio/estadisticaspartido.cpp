#include "estadisticaspartido.h"

estadisticaspartido::estadisticaspartido()
{
    golesFavor = 0;
    golesContra = 0;
    posesionBalon = 0.0f;
    for (int i = 0; i < 11; i++)
    {
        convocados[i] = 0;
        golesConvocados[i] = 0;
        tarjetasAmarillasConvocados[i] = 0;
        tarjetasRojasConvocados[i] = 0;
        faltasConvocados[i] = 0;
        minutosJugados[i] = 0;
    }
}

estadisticaspartido::estadisticaspartido(const estadisticaspartido& otra)
{
    golesFavor = otra.golesFavor;
    golesContra = otra.golesContra;
    posesionBalon = otra.posesionBalon;
    for (int i = 0; i < 11; i++)
    {
        convocados[i] = otra.convocados[i];
        golesConvocados[i] = otra.golesConvocados[i];
        tarjetasAmarillasConvocados[i] = otra.tarjetasAmarillasConvocados[i];
        tarjetasRojasConvocados[i] = otra.tarjetasRojasConvocados[i];
        faltasConvocados[i] = otra.faltasConvocados[i];
        minutosJugados[i] = otra.minutosJugados[i];
    }
}

int estadisticaspartido::getGolesFavor() const { return golesFavor; }
int estadisticaspartido::getGolesContra() const { return golesContra; }
float estadisticaspartido::getPosesionBalon() const { return posesionBalon; }
int estadisticaspartido::getConvocado(int indice) const { return convocados[indice]; }
int estadisticaspartido::getGolesConvocado(int indice) const { return golesConvocados[indice]; }
int estadisticaspartido::getTarjetasAmarillasConvocado(int indice) const { return tarjetasAmarillasConvocados[indice]; }
int estadisticaspartido::getTarjetasRojasConvocado(int indice) const { return tarjetasRojasConvocados[indice]; }
int estadisticaspartido::getFaltasConvocado(int indice) const { return faltasConvocados[indice]; }
int estadisticaspartido::getMinutosJugados(int indice) const { return minutosJugados[indice]; }

void estadisticaspartido::setGolesFavor(int valor) { golesFavor = valor; }
void estadisticaspartido::setGolesContra(int valor) { golesContra = valor; }
void estadisticaspartido::setPosesionBalon(float valor) { posesionBalon = valor; }
void estadisticaspartido::setConvocado(int indice, int camiseta) { convocados[indice] = camiseta; }
void estadisticaspartido::setGolesConvocado(int indice, int valor) { golesConvocados[indice] = valor; }
void estadisticaspartido::setTarjetasAmarillasConvocado(int indice, int valor) { tarjetasAmarillasConvocados[indice] = valor; }
void estadisticaspartido::setTarjetasRojasConvocado(int indice, int valor) { tarjetasRojasConvocados[indice] = valor; }
void estadisticaspartido::setFaltasConvocado(int indice, int valor) { faltasConvocados[indice] = valor; }
void estadisticaspartido::setMinutosJugados(int indice, int valor) { minutosJugados[indice] = valor; }

ostream& operator<<(ostream& os, const estadisticaspartido& stats)
{
    os << "GF: " << stats.golesFavor
       << " | GC: " << stats.golesContra
       << " | Posesion: " << stats.posesionBalon << "%";
    return os;
}

estadisticaspartido& estadisticaspartido::operator=(const estadisticaspartido& otra)
{
    if (this != &otra)
    {
        golesFavor = otra.golesFavor;
        golesContra = otra.golesContra;
        posesionBalon = otra.posesionBalon;
        for (int i = 0; i < 11; i++)
        {
            convocados[i] = otra.convocados[i];
            golesConvocados[i] = otra.golesConvocados[i];
            tarjetasAmarillasConvocados[i] = otra.tarjetasAmarillasConvocados[i];
            tarjetasRojasConvocados[i] = otra.tarjetasRojasConvocados[i];
            faltasConvocados[i] = otra.faltasConvocados[i];
            minutosJugados[i] = otra.minutosJugados[i];
        }
    }
    return *this;
}
