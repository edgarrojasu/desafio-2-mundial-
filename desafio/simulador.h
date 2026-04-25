#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "partido.h"
using namespace std;

class simulador {
private:
    float alpha;
    float beta;
    float mu;

public:
    simulador();
    simulador(const simulador& otro);

    float getAlpha() const;
    float getBeta() const;
    float getMu() const;

    void setAlpha(float valor);
    void setBeta(float valor);
    void setMu(float valor);

    float calcularLambda(equipo* equipoA, equipo* equipoB);
    int simularGoles(float lambda);
    int simularAmarillas(int amarillasActuales);
    int simularFaltas(int faltasActuales);
    float calcularPosesion(equipo* equipoA, equipo* equipoB, int golesA, int golesB);
    void seleccionarConvocados(equipo* e, int* indices);
    void simular(partido& p, bool permitirEmpate);
    int generarPoissonAleatorio(float lambda);

    friend ostream& operator<<(ostream& os, const simulador& s);
};

#endif // SIMULADOR_H
