#include "grupo.h"
#include <iomanip>
#include "medidorrecursos.h"

grupo::grupo()
{
    letra = ' ';
    numEquipos = 0;
    numPartidos = 0;
    for (int i = 0; i < 4; i++) equipos[i]  = nullptr;
    for (int i = 0; i < 6; i++) partidos[i] = nullptr;
}

grupo::grupo(const grupo& otro)
{
    letra      = otro.letra;
    numEquipos  = otro.numEquipos;
    numPartidos = otro.numPartidos;
    for (int i = 0; i < 4; i++) equipos[i]  = otro.equipos[i];
    for (int i = 0; i < 6; i++) partidos[i] = otro.partidos[i];
}

grupo::~grupo()
{
    for (int i = 0; i < numPartidos; i++)
    {
        delete partidos[i];
        partidos[i] = nullptr;
    }
}

grupo& grupo::operator=(const grupo& otro)
{
    if (this != &otro)
    {
        letra      = otro.letra;
        numEquipos  = otro.numEquipos;
        numPartidos = otro.numPartidos;
        for (int i = 0; i < 4; i++) equipos[i]  = otro.equipos[i];
        for (int i = 0; i < 6; i++) partidos[i] = otro.partidos[i];
    }
    return *this;
}

char grupo::getLetra() const { return letra; }
equipo* grupo::getEquipo(int i) const { return equipos[i]; }
partido* grupo::getPartido(int i) const { return partidos[i]; }
int grupo::getNumEquipos() const { return numEquipos; }
int grupo::getNumPartidos() const { return numPartidos; }

void grupo::setLetra(char valor) { letra = valor; }

void grupo::agregarEquipo(equipo* e)
{
    if (numEquipos < 4)
        equipos[numEquipos++] = e;
}

void grupo::agregarPartido(partido* p)
{
    if (numPartidos < 6)
        partidos[numPartidos++] = p;
}

bool grupo::tieneConfederacion(const char* confederacion) const
{
    for (int i = 0; i < numEquipos; i++)
    {
        if (strcmp(equipos[i]->getConfederacion(), confederacion) == 0)
            return true;
    }
    return false;
}

int grupo::contarConfederacion(const char* confederacion) const
{
    int count = 0;
    for (int i = 0; i < numEquipos; i++)
    {
        if (strcmp(equipos[i]->getConfederacion(), confederacion) == 0)
            count++;
    }
    return count;
}

void grupo::ordenarEquipos()
{
    for (int i = 0; i < numEquipos - 1; i++)
    {
        for (int j = 0; j < numEquipos - i - 1; j++)
        {
            bool intercambiar = false;
            if (equipos[j]->getPuntosT() < equipos[j+1]->getPuntosT())
            {
                intercambiar = true;
            }
            else if (equipos[j]->getPuntosT() == equipos[j+1]->getPuntosT())
            {
                if (equipos[j]->getDiferenciaGolesT() < equipos[j+1]->getDiferenciaGolesT())
                {
                    intercambiar = true;
                }
                else if (equipos[j]->getDiferenciaGolesT() == equipos[j+1]->getDiferenciaGolesT())
                {
                    if (equipos[j]->getGolesFavorT() < equipos[j+1]->getGolesFavorT())
                    {
                        intercambiar = true;
                    }
                }
            }
            if (intercambiar)
            {
                equipo* temp  = equipos[j];
                equipos[j]    = equipos[j+1];
                equipos[j+1]  = temp;
            }
        }
    }
}

void grupo::tablaClasificacion() const
{
    cout << "\nGRUPO " << letra << endl;
    cout << left
         << setw(25) << "Equipo"
         << setw(5)  << "PJ"
         << setw(5)  << "PG"
         << setw(5)  << "PE"
         << setw(5)  << "PP"
         << setw(5)  << "GF"
         << setw(5)  << "GC"
         << setw(5)  << "DG"
         << setw(5)  << "PTS"
         << endl;
    cout << string(60, '-') << endl;
    for (int i = 0; i < numEquipos; i++)
    {
        equipo* e = equipos[i];
        int pj = e->getPartidosGanadosT()
                 + e->getPartidosEmpatadosT()
                 + e->getPartidosPerdidosT();
        cout << left
             << setw(25) << e->getPais()
             << setw(5)  << pj
             << setw(5)  << e->getPartidosGanadosT()
             << setw(5)  << e->getPartidosEmpatadosT()
             << setw(5)  << e->getPartidosPerdidosT()
             << setw(5)  << e->getGolesFavorT()
             << setw(5)  << e->getGolesContraT()
             << setw(5)  << e->getDiferenciaGolesT()
             << setw(5)  << e->getPuntosT()
             << endl;
    }
}

ostream& operator<<(ostream& os, const grupo& g)
{
    os << "Grupo " << g.letra << ":" << endl;
    for (int i = 0; i < g.numEquipos; i++)
    {
        os << "  " << g.equipos[i]->getPais()
        << " (" << g.equipos[i]->getConfederacion() << ")"
        << endl;
    }
    return os;
}
