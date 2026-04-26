#include "partido.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "medidorrecursos.h"

partido::partido()
{
    fecha = new char[1]; fecha[0] = '\0';
    medidor.sumarMemoria(1);
    hora  = new char[1]; hora[0]  = '\0';
    medidor.sumarMemoria(1);
    sede  = new char[1]; sede[0]  = '\0';
    medidor.sumarMemoria(1);
    for (int i = 0; i < 3; i++)
    {
        arbitros[i] = new char[1];
        arbitros[i][0] = '\0';
    }
    equipo1  = nullptr;
    equipo2  = nullptr;
    prorroga = false;
    jugado   = false;
}

partido::partido(const partido& otro)
{
    fecha = new char[strlen(otro.fecha) + 1];
    medidor.sumarMemoria(strlen(otro.fecha) + 1);
    strcpy(fecha, otro.fecha);
    hora = new char[strlen(otro.hora) + 1];
    medidor.sumarMemoria(strlen(otro.hora) + 1);
    strcpy(hora, otro.hora);
    sede = new char[strlen(otro.sede) + 1];
    medidor.sumarMemoria(strlen(otro.sede) + 1);
    strcpy(sede, otro.sede);
    for (int i = 0; i < 3; i++)
    {
        arbitros[i] = new char[strlen(otro.arbitros[i]) + 1];
        medidor.sumarMemoria(strlen(otro.arbitros[i]) + 1);
        strcpy(arbitros[i], otro.arbitros[i]);
    }
    equipo1       = otro.equipo1;
    equipo2       = otro.equipo2;
    statsEquipo1  = otro.statsEquipo1;
    statsEquipo2  = otro.statsEquipo2;
    prorroga      = otro.prorroga;
    jugado        = otro.jugado;
}

partido::~partido()
{
    medidor.restarMemoria(strlen(fecha) + 1);
    medidor.restarMemoria(strlen(hora) + 1);
    medidor.restarMemoria(strlen(sede) + 1);
    delete[] fecha;
    delete[] hora;
    delete[] sede;
    for (int i = 0; i < 3; i++)
    {
        medidor.restarMemoria(strlen(arbitros[i]) + 1);
        delete[] arbitros[i];
    }
}

partido& partido::operator=(const partido& otro)
{
    if (this != &otro)
    {
        medidor.restarMemoria(strlen(fecha) + 1);
        medidor.restarMemoria(strlen(hora) + 1);
        medidor.restarMemoria(strlen(sede) + 1);
        delete[] fecha;
        delete[] hora;
        delete[] sede;
        for (int i = 0; i < 3; i++)
        {
            medidor.restarMemoria(strlen(arbitros[i]) + 1);
            delete[] arbitros[i];
        }

        fecha = new char[strlen(otro.fecha) + 1];
        medidor.sumarMemoria(strlen(otro.fecha) + 1);
        strcpy(fecha, otro.fecha);
        hora = new char[strlen(otro.hora) + 1];
        medidor.sumarMemoria(strlen(otro.hora) + 1);
        strcpy(hora, otro.hora);
        sede = new char[strlen(otro.sede) + 1];
        medidor.sumarMemoria(strlen(otro.sede) + 1);
        strcpy(sede, otro.sede);
        for (int i = 0; i < 3; i++)
        {
            arbitros[i] = new char[strlen(otro.arbitros[i]) + 1];
            medidor.sumarMemoria(strlen(otro.arbitros[i]) + 1);
            strcpy(arbitros[i], otro.arbitros[i]);
        }
        equipo1      = otro.equipo1;
        equipo2      = otro.equipo2;
        statsEquipo1 = otro.statsEquipo1;
        statsEquipo2 = otro.statsEquipo2;
        prorroga     = otro.prorroga;
        jugado       = otro.jugado;
    }
    return *this;
}

char* partido::getFecha() const { return fecha; }
char* partido::getHora() const { return hora; }
char* partido::getSede() const { return sede; }
char* partido::getArbitro(int i) const { return arbitros[i]; }
equipo* partido::getEquipo1() const { return equipo1; }
equipo* partido::getEquipo2() const { return equipo2; }
estadisticaspartido& partido::getStatsEquipo1() { return statsEquipo1; }
estadisticaspartido& partido::getStatsEquipo2() { return statsEquipo2; }
bool partido::isProrroga() const { return prorroga; }
bool partido::isJugado() const { return jugado; }

void partido::setFecha(const char* valor)
{
    medidor.restarMemoria(strlen(fecha) + 1);
    delete[] fecha;
    fecha = new char[strlen(valor) + 1];
    medidor.sumarMemoria(strlen(valor) + 1);
    strcpy(fecha, valor);
}

void partido::setHora(const char* valor)
{
    medidor.restarMemoria(strlen(hora) + 1);
    delete[] hora;
    hora = new char[strlen(valor) + 1];
    medidor.sumarMemoria(strlen(valor) + 1);
    strcpy(hora, valor);
}

void partido::setSede(const char* valor)
{
    medidor.restarMemoria(strlen(sede) + 1);
    delete[] sede;
    sede = new char[strlen(valor) + 1];
    medidor.sumarMemoria(strlen(valor) + 1);
    strcpy(sede, valor);
}

void partido::setArbitro(int indice, const char* valor)
{
    medidor.restarMemoria(strlen(arbitros[indice]) + 1);
    delete[] arbitros[indice];
    arbitros[indice] = new char[strlen(valor) + 1];
    medidor.sumarMemoria(strlen(valor) + 1);
    strcpy(arbitros[indice], valor);
}

void partido::setEquipo1(equipo* e) { equipo1 = e; }
void partido::setEquipo2(equipo* e) { equipo2 = e; }
void partido::setProrroga(bool valor) { prorroga = valor; }

equipo* partido::getGanador()
{
    if (!jugado) return nullptr;
    int gf1 = statsEquipo1.getGolesFavor();
    int gf2 = statsEquipo2.getGolesFavor();
    if (gf1 > gf2) return equipo1;
    if (gf2 > gf1) return equipo2;
    return nullptr;
}

ostream& operator<<(ostream& os, const partido& p)
{
    os << "Fecha: " << p.fecha
       << " | Hora: " << p.hora
       << " | Sede: " << p.sede
       << "\nArbitros: " << p.arbitros[0]
       << ", " << p.arbitros[1]
       << ", " << p.arbitros[2];
    if (p.equipo1 && p.equipo2)
    {
        os << "\n" << p.equipo1->getPais()
        << " vs " << p.equipo2->getPais();
        if (p.jugado)
        {
            os << "\nResultado: "
               << p.statsEquipo1.getGolesFavor()
               << " - "
               << p.statsEquipo2.getGolesFavor();
            if (p.prorroga)
                os << " (prorroga)";
        }
    }
    return os;
}

void partido::setJugado(bool valor) { jugado = valor; }
