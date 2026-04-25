#include "fixture.h"

fixture::fixture()
{
    nombreEtapa = new char[1];
    nombreEtapa[0] = '\0';
    capacidad = 32;
    numPartidos = 0;
    partidos = new partido*[capacidad];
    clasificados = nullptr;
    numClasificados = 0;
}

fixture::fixture(const char* etapa)
{
    nombreEtapa = new char[strlen(etapa) + 1];
    strcpy(nombreEtapa, etapa);
    capacidad = 32;
    numPartidos = 0;
    partidos = new partido*[capacidad];
    clasificados = nullptr;
    numClasificados = 0;
}

fixture::fixture(const fixture& otro)
{
    nombreEtapa = new char[strlen(otro.nombreEtapa) + 1];
    strcpy(nombreEtapa, otro.nombreEtapa);
    capacidad = otro.capacidad;
    numPartidos = otro.numPartidos;
    partidos = new partido*[capacidad];
    for (int i = 0; i < numPartidos; i++)
        partidos[i] = otro.partidos[i];
    numClasificados = otro.numClasificados;
    if (numClasificados > 0)
    {
        clasificados = new equipo*[numClasificados];
        for (int i = 0; i < numClasificados; i++)
            clasificados[i] = otro.clasificados[i];
    }
    else
    {
        clasificados = nullptr;
    }
}

fixture::~fixture()
{
    delete[] nombreEtapa;
    for (int i = 0; i < numPartidos; i++)
    {
        delete partidos[i];
        partidos[i] = nullptr;
    }
    delete[] partidos;
    delete[] clasificados;
}

fixture& fixture::operator=(const fixture& otro)
{
    if (this != &otro)
    {
        delete[] nombreEtapa;
        for (int i = 0; i < numPartidos; i++)
            delete partidos[i];
        delete[] partidos;
        delete[] clasificados;

        nombreEtapa = new char[strlen(otro.nombreEtapa) + 1];
        strcpy(nombreEtapa, otro.nombreEtapa);
        capacidad = otro.capacidad;
        numPartidos = otro.numPartidos;
        partidos = new partido*[capacidad];
        for (int i = 0; i < numPartidos; i++)
            partidos[i] = otro.partidos[i];
        numClasificados = otro.numClasificados;
        if (numClasificados > 0)
        {
            clasificados = new equipo*[numClasificados];
            for (int i = 0; i < numClasificados; i++)
                clasificados[i] = otro.clasificados[i];
        }
        else
        {
            clasificados = nullptr;
        }
    }
    return *this;
}

char* fixture::getNombreEtapa() const { return nombreEtapa; }
partido* fixture::getPartido(int i) const { return partidos[i]; }
int fixture::getNumPartidos() const { return numPartidos; }
equipo* fixture::getClasificado(int i) const { return clasificados[i]; }
int fixture::getNumClasificados() const { return numClasificados; }

void fixture::setNombreEtapa(const char* nombre)
{
    delete[] nombreEtapa;
    nombreEtapa = new char[strlen(nombre) + 1];
    strcpy(nombreEtapa, nombre);
}

void fixture::agregarPartido(partido* p)
{
    if (numPartidos >= capacidad)
    {
        capacidad *= 2;
        partido** nuevo = new partido*[capacidad];
        for (int i = 0; i < numPartidos; i++)
            nuevo[i] = partidos[i];
        delete[] partidos;
        partidos = nuevo;
    }
    partidos[numPartidos++] = p;
}

void fixture::agregarClasificado(equipo* e)
{
    equipo** nuevo = new equipo*[numClasificados + 1];
    for (int i = 0; i < numClasificados; i++)
        nuevo[i] = clasificados[i];
    nuevo[numClasificados] = e;
    delete[] clasificados;
    clasificados = nuevo;
    numClasificados++;
}

void fixture::simularEtapa(simulador& sim, bool permitirEmpate)
{
    for (int i = 0; i < numPartidos; i++)
    {
        sim.simular(*partidos[i], permitirEmpate);
    }
}

void fixture::imprimirResultados() const
{
    cout << "\n=== " << nombreEtapa << " ===" << endl;
    for (int i = 0; i < numPartidos; i++)
    {
        cout << *partidos[i] << endl;
        cout << "Stats " << partidos[i]->getEquipo1()->getPais()
             << ": " << partidos[i]->getStatsEquipo1() << endl;
        cout << "Stats " << partidos[i]->getEquipo2()->getPais()
             << ": " << partidos[i]->getStatsEquipo2() << endl;
        cout << "---" << endl;
    }
}

void fixture::imprimirGoleadores() const
{
    cout << "\nGoleadores por partido:" << endl;
    for (int i = 0; i < numPartidos; i++)
    {
        partido* p = partidos[i];
        cout << p->getEquipo1()->getPais() << " vs "
             << p->getEquipo2()->getPais() << endl;

        cout << "  Goleadores " << p->getEquipo1()->getPais() << ": ";
        bool hayGoles = false;
        for (int j = 0; j < 11; j++)
        {
            if (p->getStatsEquipo1().getGolesConvocado(j) > 0)
            {
                cout << "camiseta " << p->getStatsEquipo1().getConvocado(j) << " ";
                hayGoles = true;
            }
        }
        if (!hayGoles) cout << "ninguno";
        cout << endl;

        cout << "  Goleadores " << p->getEquipo2()->getPais() << ": ";
        hayGoles = false;
        for (int j = 0; j < 11; j++)
        {
            if (p->getStatsEquipo2().getGolesConvocado(j) > 0)
            {
                cout << "camiseta " << p->getStatsEquipo2().getConvocado(j) << " ";
                hayGoles = true;
            }
        }
        if (!hayGoles) cout << "ninguno";
        cout << endl;
    }
}

ostream& operator<<(ostream& os, const fixture& f)
{
    os << "=== " << f.nombreEtapa << " ===" << endl;
    os << "Partidos: " << f.numPartidos << endl;
    return os;
}
