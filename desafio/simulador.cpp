#include "simulador.h"

simulador::simulador()
{
    alpha = 0.6f;
    beta  = 0.4f;
    mu    = 1.35f;
}

simulador::simulador(const simulador& otro)
{
    alpha = otro.alpha;
    beta  = otro.beta;
    mu    = otro.mu;
}

float simulador::getAlpha() const { return alpha; }
float simulador::getBeta() const  { return beta; }
float simulador::getMu() const    { return mu; }

void simulador::setAlpha(float valor) { alpha = valor; }
void simulador::setBeta(float valor)  { beta  = valor; }
void simulador::setMu(float valor)    { mu    = valor; }

float simulador::calcularLambda(equipo* equipoA, equipo* equipoB)
{
    int ptA = equipoA->getStatsHistoricas().getPartidosGanados()
              + equipoA->getStatsHistoricas().getPartidosEmpatados()
              + equipoA->getStatsHistoricas().getPartidosPerdidos();

    int ptB = equipoB->getStatsHistoricas().getPartidosGanados()
              + equipoB->getStatsHistoricas().getPartidosEmpatados()
              + equipoB->getStatsHistoricas().getPartidosPerdidos();

    float gfa = (ptA > 0)
                    ? (float)equipoA->getStatsHistoricas().getGolesFavor() / ptA
                    : mu;
    float gcb = (ptB > 0)
                    ? (float)equipoB->getStatsHistoricas().getGolesContra() / ptB
                    : mu;

    if (gfa <= 0) gfa = 0.1f;
    if (gcb <= 0) gcb = 0.1f;

    float lambda = mu * pow(gfa / mu, alpha) * pow(gcb / mu, beta);
    return lambda;
}

int simulador::simularGoles(float lambda)
{
    int golesTotal = (int)round(lambda);
    return golesTotal;
}

int simulador::simularAmarillas(int amarillasActuales)
{
    float prob = (rand() % 10000) / 100.0f;
    if (amarillasActuales == 0 && prob < 6.0f)   return 1;
    if (amarillasActuales == 1 && prob < 1.15f)  return 1;
    return 0;
}

int simulador::simularFaltas(int faltasActuales)
{
    float prob = (rand() % 10000) / 100.0f;
    if (faltasActuales == 0 && prob < 13.0f)   return 1;
    if (faltasActuales == 1 && prob < 2.75f)   return 1;
    if (faltasActuales == 2 && prob < 0.7f)    return 1;
    return 0;
}

float simulador::calcularPosesion(equipo* equipoA, equipo* equipoB)
{

    int rankA = equipoA->getRankingFIFA();
    int rankB = equipoB->getRankingFIFA();
    float total = (float)(rankA + rankB);
    float posesionA = (rankB / total) * 100.0f;
    return posesionA;
}

void simulador::seleccionarConvocados(equipo* e, int* indices)
{
    int disponibles[26];
    for (int i = 0; i < 26; i++) disponibles[i] = i;

    for (int i = 0; i < 11; i++)
    {
        int j = i + rand() % (26 - i);
        int temp = disponibles[i];
        disponibles[i] = disponibles[j];
        disponibles[j] = temp;
        indices[i] = disponibles[i];
    }
}

void simulador::simular(partido& p, bool permitirEmpate)
{
    equipo* e1 = p.getEquipo1();
    equipo* e2 = p.getEquipo2();

    float lambda1 = calcularLambda(e1, e2);
    float lambda2 = calcularLambda(e2, e1);

    int convocados1[11], convocados2[11];
    seleccionarConvocados(e1, convocados1);
    seleccionarConvocados(e2, convocados2);

    for (int i = 0; i < 11; i++)
    {
        p.getStatsEquipo1().setConvocado(i, e1->getPlantilla()[convocados1[i]].getNumeroCamiseta());
        p.getStatsEquipo2().setConvocado(i, e2->getPlantilla()[convocados2[i]].getNumeroCamiseta());
    }

    int golesEq1 = 0, golesEq2 = 0;
    int golesEsperados1 = generarPoissonAleatorio(lambda1);
    int golesEsperados2 = generarPoissonAleatorio(lambda2);

    for (int i = 0; i < 11; i++)
    {
        int golesJug = 0;
        float prob = (rand() % 10000) / 100.0f;
        if (prob < 4.0f && golesEq1 < golesEsperados1)
        {
            golesJug = 1;
            golesEq1++;
        }
        p.getStatsEquipo1().setGolesConvocado(i, golesJug);
    }

    for (int i = 0; i < 11; i++)
    {
        int golesJug = 0;
        float prob = (rand() % 10000) / 100.0f;
        if (prob < 4.0f && golesEq2 < golesEsperados2)
        {
            golesJug = 1;
            golesEq2++;
        }
        p.getStatsEquipo2().setGolesConvocado(i, golesJug);
    }

    p.getStatsEquipo1().setGolesFavor(golesEq1);
    p.getStatsEquipo1().setGolesContra(golesEq2);
    p.getStatsEquipo2().setGolesFavor(golesEq2);
    p.getStatsEquipo2().setGolesContra(golesEq1);

    if (!permitirEmpate && golesEq1 == golesEq2)
    {
        int rankA = e1->getRankingFIFA();
        int rankB = e2->getRankingFIFA();
        int total = rankA + rankB;
        int prob = rand() % total;
        if (prob < rankB)
        {
            p.getStatsEquipo1().setGolesFavor(golesEq1 + 1);
            p.getStatsEquipo1().setGolesContra(golesEq2);
            p.getStatsEquipo2().setGolesContra(golesEq1 + 1);
        }
        else
        {
            p.getStatsEquipo2().setGolesFavor(golesEq2 + 1);
            p.getStatsEquipo2().setGolesContra(golesEq1);
            p.getStatsEquipo1().setGolesContra(golesEq2 + 1);
        }
        p.setProrroga(true);

        for (int i = 0; i < 11; i++)
        {
            p.getStatsEquipo1().setMinutosJugados(i, 120);
            p.getStatsEquipo2().setMinutosJugados(i, 120);
        }
    }
    else
    {
        for (int i = 0; i < 11; i++)
        {
            p.getStatsEquipo1().setMinutosJugados(i, 90);
            p.getStatsEquipo2().setMinutosJugados(i, 90);
        }
    }

    for (int i = 0; i < 11; i++)
    {
        int amarillas1 = 0, faltas1 = 0;
        amarillas1 += simularAmarillas(amarillas1);
        amarillas1 += simularAmarillas(amarillas1);
        faltas1 += simularFaltas(faltas1);
        faltas1 += simularFaltas(faltas1);
        faltas1 += simularFaltas(faltas1);
        p.getStatsEquipo1().setTarjetasAmarillasConvocado(i, amarillas1);
        p.getStatsEquipo1().setTarjetasRojasConvocado(i, amarillas1 >= 2 ? 1 : 0);
        p.getStatsEquipo1().setFaltasConvocado(i, faltas1);

        int amarillas2 = 0, faltas2 = 0;
        amarillas2 += simularAmarillas(amarillas2);
        amarillas2 += simularAmarillas(amarillas2);
        faltas2 += simularFaltas(faltas2);
        faltas2 += simularFaltas(faltas2);
        faltas2 += simularFaltas(faltas2);
        p.getStatsEquipo2().setTarjetasAmarillasConvocado(i, amarillas2);
        p.getStatsEquipo2().setTarjetasRojasConvocado(i, amarillas2 >= 2 ? 1 : 0);
        p.getStatsEquipo2().setFaltasConvocado(i, faltas2);
    }

    float posesion1 = calcularPosesion(e1, e2);
    p.getStatsEquipo1().setPosesionBalon(posesion1);
    p.getStatsEquipo2().setPosesionBalon(100.0f - posesion1);

    estadisticasequipo deltaE1, deltaE2;
    int gf1 = p.getStatsEquipo1().getGolesFavor();
    int gf2 = p.getStatsEquipo2().getGolesFavor();

    deltaE1.setGolesFavor(gf1);
    deltaE1.setGolesContra(gf2);
    deltaE2.setGolesFavor(gf2);
    deltaE2.setGolesContra(gf1);

    if (gf1 > gf2)
    {
        deltaE1.setPartidosGanados(1);
        deltaE2.setPartidosPerdidos(1);
        e1->setPuntosT(e1->getPuntosT() + 3);
    }
    else if (gf2 > gf1)
    {
        deltaE2.setPartidosGanados(1);
        deltaE1.setPartidosPerdidos(1);
        e2->setPuntosT(e2->getPuntosT() + 3);
    }
    else
    {
        deltaE1.setPartidosEmpatados(1);
        deltaE2.setPartidosEmpatados(1);
        e1->setPuntosT(e1->getPuntosT() + 1);
        e2->setPuntosT(e2->getPuntosT() + 1);
    }

    e1->getStatsHistoricas() += deltaE1;
    e2->getStatsHistoricas() += deltaE2;
    e1->setDiferenciaGolesT(e1->getDiferenciaGolesT() + gf1 - gf2);
    e2->setDiferenciaGoles(e2->getDiferenciaGoles() + gf2 - gf1);

    int minutos = p.isProrroga() ? 120 : 90;
    for (int i = 0; i < 11; i++)
    {
        jugador& j1 = e1->getPlantilla()[convocados1[i]];
        estadisticasjugador delta1;
        delta1.setGoles(p.getStatsEquipo1().getGolesConvocado(i));
        delta1.setMinutosJugados(minutos);
        delta1.setPartidosJugados(1);
        delta1.setTarjetasAmarillas(p.getStatsEquipo1().getTarjetasAmarillasConvocado(i));
        delta1.setTarjetasRojas(p.getStatsEquipo1().getTarjetasRojasConvocado(i));
        delta1.setFaltas(p.getStatsEquipo1().getFaltasConvocado(i));
        j1.getStats() += delta1;

        jugador& j2 = e2->getPlantilla()[convocados2[i]];
        estadisticasjugador delta2;
        delta2.setGoles(p.getStatsEquipo2().getGolesConvocado(i));
        delta2.setMinutosJugados(minutos);
        delta2.setPartidosJugados(1);
        delta2.setTarjetasAmarillas(p.getStatsEquipo2().getTarjetasAmarillasConvocado(i));
        delta2.setTarjetasRojas(p.getStatsEquipo2().getTarjetasRojasConvocado(i));
        delta2.setFaltas(p.getStatsEquipo2().getFaltasConvocado(i));
        j2.getStats() += delta2;
    }

    e1->setGolesFavorT(e1->getGolesFavorT() + gf1);
    e1->setGolesContraT(e1->getGolesContraT() + gf2);
    e2->setGolesFavorT(e2->getGolesFavorT() + gf2);
    e2->setGolesContraT(e2->getGolesContraT() + gf1);

    if (gf1 > gf2)
    {
        e1->setPartidosGanadosT(e1->getPartidosGanadosT() + 1);
        e2->setPartidosPerdidosT(e2->getPartidosPerdidosT() + 1);
    }
    else if (gf2 > gf1)
    {
        e2->setPartidosGanadosT(e2->getPartidosGanadosT() + 1);
        e1->setPartidosPerdidosT(e1->getPartidosPerdidosT() + 1);
    }
    else
    {
        e1->setPartidosEmpatadosT(e1->getPartidosEmpatadosT() + 1);
        e2->setPartidosEmpatadosT(e2->getPartidosEmpatadosT() + 1);
    }

    p.setJugado(true);
}

ostream& operator<<(ostream& os, const simulador& s)
{
    os << "Simulador | alpha: " << s.alpha
       << " | beta: " << s.beta
       << " | mu: " << s.mu;
    return os;
}

int simulador::generarPoissonAleatorio(float lambda)
{
    float L = exp(-lambda);
    int k = 0;
    float p = 1.0f;
    do
    {
        k++;
        p *= (rand() % 10000) / 10000.0f;
    } while (p > L);
    return k - 1;
}
