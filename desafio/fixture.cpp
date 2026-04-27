#include "fixture.h"
#include <iomanip>
#include <string>
#include "medidorrecursos.h"

fixture::fixture()
{
    nombreEtapa = new char[1];
    medidor.sumarMemoria(1);
    nombreEtapa[0] = '\0';
    capacidad = 32;
    numPartidos = 0;
    partidos = new partido*[capacidad];
    medidor.sumarMemoria(sizeof(partido*) * capacidad);
    clasificados = nullptr;
    numClasificados = 0;
}

fixture::fixture(const char* etapa)
{
    nombreEtapa = new char[strlen(etapa) + 1];
    medidor.sumarMemoria(strlen(etapa) + 1);
    strcpy(nombreEtapa, etapa);
    capacidad = 32;
    numPartidos = 0;
    partidos = new partido*[capacidad];
    medidor.sumarMemoria(sizeof(partido*) * capacidad);
    clasificados = nullptr;
    numClasificados = 0;
}

fixture::fixture(const fixture& otro)
{
    nombreEtapa = new char[strlen(otro.nombreEtapa) + 1];
    medidor.sumarMemoria(strlen(otro.nombreEtapa) + 1);
    strcpy(nombreEtapa, otro.nombreEtapa);
    capacidad = otro.capacidad;
    numPartidos = otro.numPartidos;
    partidos = new partido*[capacidad];
    medidor.sumarMemoria(sizeof(partido*) * capacidad);
    for (int i = 0; i < numPartidos; i++)
        partidos[i] = otro.partidos[i];
    numClasificados = otro.numClasificados;
    if (numClasificados > 0)
    {
        clasificados = new equipo*[numClasificados];
        medidor.sumarMemoria(sizeof(equipo*) * numClasificados);
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
    medidor.restarMemoria(strlen(nombreEtapa) + 1);
    delete[] nombreEtapa;
    for (int i = 0; i < numPartidos; i++)
    {
        medidor.restarMemoria(sizeof(partido));
        delete partidos[i];
        partidos[i] = nullptr;
    }
    medidor.restarMemoria(sizeof(partido*) * capacidad);
    medidor.restarMemoria(sizeof(equipo*) * numClasificados);
    delete[] partidos;
    delete[] clasificados;
}

fixture& fixture::operator=(const fixture& otro)
{
    if (this != &otro)
    {
        medidor.restarMemoria(strlen(nombreEtapa) + 1);
        delete[] nombreEtapa;
        for (int i = 0; i < numPartidos; i++)
        {
            medidor.restarMemoria(sizeof(partido));
            delete partidos[i];
        }
        medidor.restarMemoria(sizeof(partido*) * capacidad);
        medidor.restarMemoria(sizeof(equipo*) * numClasificados);
        delete[] partidos;
        delete[] clasificados;

        nombreEtapa = new char[strlen(otro.nombreEtapa) + 1];
        medidor.sumarMemoria(strlen(otro.nombreEtapa) + 1);
        strcpy(nombreEtapa, otro.nombreEtapa);
        capacidad = otro.capacidad;
        numPartidos = otro.numPartidos;
        partidos = new partido*[capacidad];
        medidor.sumarMemoria(sizeof(partido*) * capacidad);
        for (int i = 0; i < numPartidos; i++)
            partidos[i] = otro.partidos[i];
        numClasificados = otro.numClasificados;
        if (numClasificados > 0)
        {
            clasificados = new equipo*[numClasificados];
            medidor.sumarMemoria(sizeof(equipo*) * numClasificados);
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
    medidor.restarMemoria(strlen(nombreEtapa) + 1);
    delete[] nombreEtapa;
    nombreEtapa = new char[strlen(nombre) + 1];
    medidor.sumarMemoria(strlen(nombre) + 1);
    strcpy(nombreEtapa, nombre);
}

void fixture::agregarPartido(partido* p)
{
    if (numPartidos >= capacidad)
    {
        int capAnterior = capacidad;
        capacidad *= 2;
        partido** nuevo = new partido*[capacidad];
        medidor.sumarMemoria(sizeof(partido*) * capacidad);
        for (int i = 0; i < numPartidos; i++)
            nuevo[i] = partidos[i];
        medidor.restarMemoria(sizeof(partido*) * capAnterior);
        delete[] partidos;
        partidos = nuevo;
    }
    partidos[numPartidos++] = p;
}

void fixture::agregarClasificado(equipo* e)
{
    equipo** nuevo = new equipo*[numClasificados + 1];
    medidor.sumarMemoria(sizeof(equipo*) * (numClasificados + 1));
    for (int i = 0; i < numClasificados; i++)
        nuevo[i] = clasificados[i];
    nuevo[numClasificados] = e;
    medidor.restarMemoria(sizeof(equipo*) * numClasificados);
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
    cout << "\n";
    cout << string(60, '=') << endl;
    cout << "  " << nombreEtapa << endl;
    cout << string(60, '=') << endl;

    for (int i = 0; i < numPartidos; i++)
    {
        partido* p = partidos[i];
        cout << "\nPartido " << (i + 1) << endl;
        cout << string(40, '-') << endl;
        cout << left
             << setw(3)  << "Fecha:"
             << setw(15) << p->getFecha()
             << "  Hora: " << p->getHora()
             << "  Sede: " << p->getSede() << endl;
        cout << "Arbitros: "
             << p->getArbitro(0) << ", "
             << p->getArbitro(1) << ", "
             << p->getArbitro(2) << endl;
        cout << string(40, '-') << endl;

        cout << left
             << setw(25) << p->getEquipo1()->getPais()
             << setw(5)  << p->getStatsEquipo1().getGolesFavor()
             << " - "
             << setw(5)  << p->getStatsEquipo2().getGolesFavor()
             << p->getEquipo2()->getPais();
        if (p->isProrroga())
            cout << " (prorroga)";
        cout << endl;

        cout << string(40, '-') << endl;

        cout << left
             << setw(25) << p->getEquipo1()->getPais()
             << "Posesion: "
             << fixed << setprecision(1)
             << p->getStatsEquipo1().getPosesionBalon() << "%" << endl;

        cout << left
             << setw(25) << p->getEquipo2()->getPais()
             << "Posesion: "
             << fixed << setprecision(1)
             << p->getStatsEquipo2().getPosesionBalon() << "%" << endl;
    }
    cout << string(60, '=') << endl;
}

void fixture::imprimirGoleadores() const
{
    cout << "\n";
    cout << string(60, '-') << endl;
    cout << "  Goleadores " << nombreEtapa << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < numPartidos; i++)
    {
        partido* p = partidos[i];
        cout << "\n" << p->getEquipo1()->getPais()
             << " vs "
             << p->getEquipo2()->getPais() << endl;

        cout << "  " << left << setw(25) << p->getEquipo1()->getPais() << ": ";
        bool hayGoles = false;
        for (int j = 0; j < 11; j++)
        {
            if (p->getStatsEquipo1().getGolesConvocado(j) > 0)
            {
                cout << "camiseta " << p->getStatsEquipo1().getConvocado(j)
                << " (" << p->getStatsEquipo1().getGolesConvocado(j) << ") ";
                hayGoles = true;
            }
        }
        if (!hayGoles) cout << "sin goles";
        cout << endl;

        cout << "  " << left << setw(25) << p->getEquipo2()->getPais() << ": ";
        hayGoles = false;
        for (int j = 0; j < 11; j++)
        {
            if (p->getStatsEquipo2().getGolesConvocado(j) > 0)
            {
                cout << "camiseta " << p->getStatsEquipo2().getConvocado(j)
                << " (" << p->getStatsEquipo2().getGolesConvocado(j) << ") ";
                hayGoles = true;
            }
        }
        if (!hayGoles) cout << "sin goles";
        cout << endl;
    }
    cout << string(60, '-') << endl;
}

ostream& operator<<(ostream& os, const fixture& f)
{
    os << "=== " << f.nombreEtapa << " ===" << endl;
    os << "Partidos: " << f.numPartidos << endl;
    return os;
}
