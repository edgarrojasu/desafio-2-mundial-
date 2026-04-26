#include "lectorcsv.h"
#include "medidorrecursos.h"

lectorcsv::lectorcsv(const char* archivo)
{
    nombreArchivo = new char[strlen(archivo) + 1];
    medidor.sumarMemoria(strlen(archivo) + 1);
    strcpy(nombreArchivo, archivo);
}

lectorcsv::lectorcsv(const lectorcsv& otro)
{
    nombreArchivo = new char[strlen(otro.nombreArchivo) + 1];
    medidor.sumarMemoria(strlen(otro.nombreArchivo) + 1);
    strcpy(nombreArchivo, otro.nombreArchivo);
}

lectorcsv::~lectorcsv()
{
    medidor.restarMemoria(strlen(nombreArchivo) + 1);
    delete[] nombreArchivo;
}

bool lectorcsv::leerEquipos(equipo* equipos, int& numEquipos)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "Error: no se pudo abrir " << nombreArchivo << endl;
        return false;
    }

    string linea;
    getline(archivo, linea);
    getline(archivo, linea);

    numEquipos = 0;
    while (getline(archivo, linea) && numEquipos < 48)
    {
        medidor.contarIteracion();
        medidor.registrarLlamadaLibreria("ifstream::getline");
        if (linea.empty()) continue;

        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();

        stringstream ss(linea);
        string ranking, pais, dt, federacion, confederacion;
        string gf, gc, pg, pe, pp;

        getline(ss, ranking,       ';');
        getline(ss, pais,          ';');
        getline(ss, dt,            ';');
        getline(ss, federacion,    ';');
        getline(ss, confederacion, ';');
        getline(ss, gf,            ';');
        getline(ss, gc,            ';');
        getline(ss, pg,            ';');
        getline(ss, pe,            ';');
        getline(ss, pp,            ';');

        equipos[numEquipos].setRankingFIFA(stoi(ranking));
        equipos[numEquipos].setPais(pais.c_str());
        equipos[numEquipos].setDirectorTecnico(dt.c_str());
        equipos[numEquipos].setConfederacion(confederacion.c_str());
        equipos[numEquipos].getStatsHistoricas().setGolesFavor(stoi(gf));
        equipos[numEquipos].getStatsHistoricas().setGolesContra(stoi(gc));
        equipos[numEquipos].getStatsHistoricas().setPartidosGanados(stoi(pg));
        equipos[numEquipos].getStatsHistoricas().setPartidosEmpatados(stoi(pe));
        equipos[numEquipos].getStatsHistoricas().setPartidosPerdidos(stoi(pp));
        equipos[numEquipos].generarPlantilla();

        int pt = stoi(pg) + stoi(pe) + stoi(pp);
        float promGF = (pt > 0) ? (float)stoi(gf) / pt : 1.35f;
        float promGC = (pt > 0) ? (float)stoi(gc) / pt : 1.35f;
        if (promGF <= 0) promGF = 0.1f;
        if (promGC <= 0) promGC = 0.1f;
        equipos[numEquipos].setPromedioGFHistorico(promGF);
        equipos[numEquipos].setPromedioGCHistorico(promGC);

        numEquipos++;
    }

    archivo.close();
    return true;
}

void lectorcsv::escribirJugadores(equipo* equipos, int numEquipos)
{
    ofstream archivo("jugadores.csv");
    archivo << "pais;camiseta;nombre;apellido;goles;asistencias;minutosJugados;partidosJugados;tarjetasAmarillas;tarjetasRojas;faltas\n";

    for (int i = 0; i < numEquipos; i++)
    {
        for (int j = 0; j < equipos[i].getNumJugadores(); j++)
        {
            jugador& jug = equipos[i].getPlantilla()[j];
            archivo << equipos[i].getPais()                  << ";"
                    << jug.getNumeroCamiseta()                << ";"
                    << jug.getNombre()                       << ";"
                    << jug.getApellido()                     << ";"
                    << jug.getStats().getGoles()             << ";"
                    << jug.getStats().getAsistencias()       << ";"
                    << jug.getStats().getMinutosJugados()    << ";"
                    << jug.getStats().getPartidosJugados()   << ";"
                    << jug.getStats().getTarjetasAmarillas() << ";"
                    << jug.getStats().getTarjetasRojas()     << ";"
                    << jug.getStats().getFaltas()            << "\n";
        }
    }
    archivo.close();
    cout << "Archivo jugadores.csv generado correctamente." << endl;
}

void lectorcsv::leerJugadores(equipo* equipos, int numEquipos)
{
    ifstream archivo("jugadores.csv");
    if (!archivo.is_open())
    {
        cout << "Error: no se pudo abrir jugadores.csv" << endl;
        return;
    }

    string linea;
    getline(archivo, linea);

    while (getline(archivo, linea))
    {
        if (linea.empty()) continue;

        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();

        stringstream ss(linea);
        string pais, camiseta, nombre, apellido;
        string goles, asistencias, minutos, partidos, amarillas, rojas, faltas;

        getline(ss, pais,        ';');
        getline(ss, camiseta,    ';');
        getline(ss, nombre,      ';');
        getline(ss, apellido,    ';');
        getline(ss, goles,       ';');
        getline(ss, asistencias, ';');
        getline(ss, minutos,     ';');
        getline(ss, partidos,    ';');
        getline(ss, amarillas,   ';');
        getline(ss, rojas,       ';');
        getline(ss, faltas,      ';');

        for (int i = 0; i < numEquipos; i++)
        {
            if (pais == equipos[i].getPais())
            {
                int idx = stoi(camiseta) - 1;
                jugador& jug = equipos[i].getPlantilla()[idx];
                jug.getStats().setGoles(stoi(goles));
                jug.getStats().setAsistencias(stoi(asistencias));
                jug.getStats().setMinutosJugados(stoi(minutos));
                jug.getStats().setPartidosJugados(stoi(partidos));
                jug.getStats().setTarjetasAmarillas(stoi(amarillas));
                jug.getStats().setTarjetasRojas(stoi(rojas));
                jug.getStats().setFaltas(stoi(faltas));
                break;
            }
        }
    }
    archivo.close();
    cout << "Jugadores cargados correctamente." << endl;
}
