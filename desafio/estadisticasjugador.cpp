#include "estadisticasjugador.h"

estadisticasjugador::estadisticasjugador()
{
    goles = 0;
    asistencias = 0;
    minutosJugados = 0;
    partidosJugados = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
}

estadisticasjugador::estadisticasjugador(const estadisticasjugador& otra)
{
    goles = otra.goles;
    asistencias = otra.asistencias;
    minutosJugados = otra.minutosJugados;
    partidosJugados = otra.partidosJugados;
    tarjetasAmarillas = otra.tarjetasAmarillas;
    tarjetasRojas = otra.tarjetasRojas;
    faltas = otra.faltas;
}

int estadisticasjugador::getGoles() const { return goles; }
int estadisticasjugador::getAsistencias() const { return asistencias; }
int estadisticasjugador::getMinutosJugados() const { return minutosJugados; }
int estadisticasjugador::getPartidosJugados() const { return partidosJugados; }
int estadisticasjugador::getTarjetasAmarillas() const { return tarjetasAmarillas; }
int estadisticasjugador::getTarjetasRojas() const { return tarjetasRojas; }
int estadisticasjugador::getFaltas() const { return faltas; }

void estadisticasjugador::setGoles(int valor) { goles = valor; }
void estadisticasjugador::setAsistencias(int valor) { asistencias = valor; }
void estadisticasjugador::setMinutosJugados(int valor) { minutosJugados = valor; }
void estadisticasjugador::setPartidosJugados(int valor) { partidosJugados = valor; }
void estadisticasjugador::setTarjetasAmarillas(int valor) { tarjetasAmarillas = valor; }
void estadisticasjugador::setTarjetasRojas(int valor) { tarjetasRojas = valor; }
void estadisticasjugador::setFaltas(int valor) { faltas = valor; }

estadisticasjugador& estadisticasjugador::operator+=(const estadisticasjugador& otra)
{
    goles += otra.goles;
    asistencias += otra.asistencias;
    minutosJugados += otra.minutosJugados;
    partidosJugados += otra.partidosJugados;
    tarjetasAmarillas += otra.tarjetasAmarillas;
    tarjetasRojas += otra.tarjetasRojas;
    faltas += otra.faltas;
    return *this;
}

ostream& operator<<(ostream& os, const estadisticasjugador& stats)
{
    os << "Goles: " << stats.goles
       << " | Asistencias: " << stats.asistencias
       << " | Minutos: " << stats.minutosJugados
       << " | Partidos: " << stats.partidosJugados
       << " | Amarillas: " << stats.tarjetasAmarillas
       << " | Rojas: " << stats.tarjetasRojas
       << " | Faltas: " << stats.faltas;
    return os;
}

estadisticasjugador& estadisticasjugador::operator=(const estadisticasjugador& otra)
{
    if (this != &otra) {
        goles = otra.goles;
        asistencias = otra.asistencias;
        minutosJugados = otra.minutosJugados;
        partidosJugados = otra.partidosJugados;
        tarjetasAmarillas = otra.tarjetasAmarillas;
        tarjetasRojas = otra.tarjetasRojas;
        faltas = otra.faltas;
    }
    return *this;
}
