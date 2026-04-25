#include "equipo.h"

equipo::equipo()
{
    pais = new char[1];
    pais[0] = '\0';
    confederacion = new char[1];
    confederacion[0] = '\0';
    directorTecnico = new char[1];
    directorTecnico[0] = '\0';
    rankingFIFA = 0;
    plantilla = nullptr;
    numJugadores = 0;
    puntos = 0;
    diferenciaGoles = 0;
    puntosT = 0;
    diferenciaGolesT = 0;
    partidosGanadosT = 0;
    partidosEmpatadosT = 0;
    partidosPerdidosT = 0;
    golesFavorT = 0;
    golesContraT = 0;
    promedioGFHistorico = 0.0f;
    promedioGCHistorico = 0.0f;

}

equipo::equipo(const equipo& otro)
{
    pais = new char[strlen(otro.pais) + 1];
    strcpy(pais, otro.pais);
    confederacion = new char[strlen(otro.confederacion) + 1];
    strcpy(confederacion, otro.confederacion);
    directorTecnico = new char[strlen(otro.directorTecnico) + 1];
    strcpy(directorTecnico, otro.directorTecnico);
    rankingFIFA = otro.rankingFIFA;
    numJugadores = otro.numJugadores;
    puntos = otro.puntos;
    diferenciaGoles = otro.diferenciaGoles;
    statsHistoricas = otro.statsHistoricas;
    plantilla = new jugador[numJugadores];

    for (int i = 0; i < numJugadores; i++)
    {
        plantilla[i] = otro.plantilla[i];
    }
    puntosT = otro.puntosT;
    diferenciaGolesT = otro.diferenciaGolesT;
    partidosGanadosT = otro.partidosGanadosT;
    partidosEmpatadosT = otro.partidosEmpatadosT;
    partidosPerdidosT = otro.partidosPerdidosT;
    golesFavorT = otro.golesFavorT;
    golesContraT = otro.golesContraT;
    promedioGFHistorico = otro.promedioGFHistorico;
    promedioGCHistorico = otro.promedioGCHistorico;
}

equipo::~equipo()
{
    delete[] pais;
    delete[] confederacion;
    delete[] directorTecnico;
    delete[] plantilla;
}

equipo& equipo::operator=(const equipo& otro)
{
    if (this != &otro)
    {
        delete[] pais;
        delete[] confederacion;
        delete[] directorTecnico;
        delete[] plantilla;
        pais = new char[strlen(otro.pais) + 1];
        strcpy(pais, otro.pais);
        confederacion = new char[strlen(otro.confederacion) + 1];
        strcpy(confederacion, otro.confederacion);
        directorTecnico = new char[strlen(otro.directorTecnico) + 1];
        strcpy(directorTecnico, otro.directorTecnico);
        rankingFIFA = otro.rankingFIFA;
        numJugadores = otro.numJugadores;
        puntos = otro.puntos;
        diferenciaGoles = otro.diferenciaGoles;
        statsHistoricas = otro.statsHistoricas;
        plantilla = new jugador[numJugadores];
        promedioGFHistorico = otro.promedioGFHistorico;
        promedioGCHistorico = otro.promedioGCHistorico;

        for (int i = 0; i < numJugadores; i++)
        {
            plantilla[i] = otro.plantilla[i];
        }
    }
    return *this;
}

char* equipo::getPais() const { return pais; }
char* equipo::getConfederacion() const { return confederacion; }
char* equipo::getDirectorTecnico() const { return directorTecnico; }
int equipo::getRankingFIFA() const { return rankingFIFA; }
jugador* equipo::getPlantilla() const { return plantilla; }
int equipo::getNumJugadores() const { return numJugadores; }
estadisticasequipo& equipo::getStatsHistoricas() { return statsHistoricas; }
int equipo::getPuntos() const { return puntos; }
int equipo::getDiferenciaGoles() const { return diferenciaGoles; }

void equipo::setPais(const char* valor)
{
    delete[] pais;
    pais = new char[strlen(valor) + 1];
    strcpy(pais, valor);
}

void equipo::setConfederacion(const char* valor)
{
    delete[] confederacion;
    confederacion = new char[strlen(valor) + 1];
    strcpy(confederacion, valor);
}

void equipo::setDirectorTecnico(const char* valor)
{
    delete[] directorTecnico;
    directorTecnico = new char[strlen(valor) + 1];
    strcpy(directorTecnico, valor);
}

void equipo::setRankingFIFA(int valor) { rankingFIFA = valor; }
void equipo::setPuntos(int valor) { puntos = valor; }
void equipo::setDiferenciaGoles(int valor) { diferenciaGoles = valor; }

void equipo::generarPlantilla()
{
    numJugadores = 26;
    plantilla = new jugador[numJugadores];
    for (int i = 0; i < numJugadores; i++)
    {
        string nombre = "nombre" + to_string(i + 1);
        string apellido = "apellido" + to_string(i + 1);
        plantilla[i].setNombre(nombre.c_str());
        plantilla[i].setApellido(apellido.c_str());
        plantilla[i].setNumeroCamiseta(i + 1);
    }
}

bool equipo::operator<(const equipo& otro) const
{
    return rankingFIFA < otro.rankingFIFA;
}

ostream& operator<<(ostream& os, const equipo& e)
{
    os << "Pais: " << e.pais
       << " | Ranking: " << e.rankingFIFA
       << " | Confederacion: " << e.confederacion
       << " | DT: " << e.directorTecnico
       << " | Puntos: " << e.puntos
       << "\n" << e.statsHistoricas;
    return os;
}

int equipo::getPuntosT() const { return puntosT; }
int equipo::getDiferenciaGolesT() const { return diferenciaGolesT; }
int equipo::getGolesFavorT() const { return golesFavorT; }
int equipo::getGolesContraT() const { return golesContraT; }
int equipo::getPartidosGanadosT() const { return partidosGanadosT; }
int equipo::getPartidosEmpatadosT() const { return partidosEmpatadosT; }
int equipo::getPartidosPerdidosT() const { return partidosPerdidosT; }

void equipo::setPuntosT(int valor) { puntosT = valor; }
void equipo::setDiferenciaGolesT(int valor) { diferenciaGolesT = valor; }
void equipo::setGolesFavorT(int valor) { golesFavorT = valor; }
void equipo::setGolesContraT(int valor) { golesContraT = valor; }
void equipo::setPartidosGanadosT(int valor) { partidosGanadosT = valor; }
void equipo::setPartidosEmpatadosT(int valor) { partidosEmpatadosT = valor; }
void equipo::setPartidosPerdidosT(int valor) { partidosPerdidosT = valor; }
float equipo::getPromedioGFHistorico() const { return promedioGFHistorico; }
float equipo::getPromedioGCHistorico() const { return promedioGCHistorico; }
void equipo::setPromedioGFHistorico(float valor) { promedioGFHistorico = valor; }
void equipo::setPromedioGCHistorico(float valor) { promedioGCHistorico = valor; }
