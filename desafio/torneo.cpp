#include "torneo.h"
#include <iomanip>

torneo::torneo()
{
    equipos = nullptr;
    numEquipos = 0;
    sorteoGrupos = nullptr;
    numEtapas = 0;
    for (int i = 0; i < 7; i++)
        etapas[i] = nullptr;
}

torneo::~torneo()
{
    delete[] equipos;
    delete sorteoGrupos;
    for (int i = 0; i < 7; i++)
        delete etapas[i];
}

torneo::torneo(const torneo& otro)
{
    numEquipos = otro.numEquipos;
    numEtapas = otro.numEtapas;
    equipos = new equipo[numEquipos];
    for (int i = 0; i < numEquipos; i++)
        equipos[i] = otro.equipos[i];
    sorteoGrupos = nullptr;
    for (int i = 0; i < 7; i++)
        etapas[i] = nullptr;
}

torneo& torneo::operator=(const torneo& otro)
{
    if (this != &otro)
    {
        delete[] equipos;
        delete sorteoGrupos;
        for (int i = 0; i < 7; i++)
            delete etapas[i];
        numEquipos = otro.numEquipos;
        numEtapas = otro.numEtapas;
        equipos = new equipo[numEquipos];
        for (int i = 0; i < numEquipos; i++)
            equipos[i] = otro.equipos[i];
        sorteoGrupos = nullptr;
        for (int i = 0; i < 7; i++)
            etapas[i] = nullptr;
    }
    return *this;
}

void torneo::cargarEquipos(const char* archivo)
{
    equipos = new equipo[48];
    lectorcsv lector(archivo);
    lector.leerEquipos(equipos, numEquipos);
    cout << "Equipos cargados: " << numEquipos << endl;
}

void torneo::conformarGrupos()
{
    sorteoGrupos = new sorteo();
    sorteoGrupos->armarBombos(equipos, numEquipos);
    sorteoGrupos->formarGrupos();
    sorteoGrupos->imprimirGrupos();
}

void torneo::simularFaseGrupos()
{
    etapas[0] = new fixture("Fase de Grupos");

    int partidosPorDia[19] = {0};
    int ultimoDia[48];
    for (int i = 0; i < 48; i++) ultimoDia[i] = -99;

    auto getIndiceEquipo = [&](equipo* e) -> int
    {
        for (int i = 0; i < numEquipos; i++)
            if (&equipos[i] == e) return i;
        return -1;
    };

    int pares[6][2] = {{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}};

    for (int g = 0; g < 12; g++)
    {
        grupo& gr = sorteoGrupos->getGrupo(g);
        for (int i = 0; i < 6; i++)
        {
            equipo* e1 = gr.getEquipo(pares[i][0]);
            equipo* e2 = gr.getEquipo(pares[i][1]);
            int idx1 = getIndiceEquipo(e1);
            int idx2 = getIndiceEquipo(e2);

            int diaAsignado = -1;
            for (int d = 0; d < 19 && diaAsignado == -1; d++)
            {
                if (partidosPorDia[d] < 4 &&
                    (ultimoDia[idx1] == -99 || d - ultimoDia[idx1] >= 3) &&
                    (ultimoDia[idx2] == -99 || d - ultimoDia[idx2] >= 3))
                {
                    diaAsignado = d;
                }
            }
            if (diaAsignado == -1) diaAsignado = 18;

            int dia = 20 + diaAsignado;
            int mes = 6;
            if (dia > 30) { dia -= 30; mes = 7; }

            char fecha[12];
            fecha[0] = '0' + dia / 10;
            fecha[1] = '0' + dia % 10;
            fecha[2] = '/';
            fecha[3] = '0' + mes / 10;
            fecha[4] = '0' + mes % 10;
            fecha[5] = '/';
            fecha[6] = '2'; fecha[7] = '0';
            fecha[8] = '2'; fecha[9] = '6';
            fecha[10] = '\0';

            partido* p = new partido();
            p->setFecha(fecha);
            p->setHora("00:00");
            p->setSede("nombreSede");
            p->setArbitro(0, "codArbitro1");
            p->setArbitro(1, "codArbitro2");
            p->setArbitro(2, "codArbitro3");
            p->setEquipo1(e1);
            p->setEquipo2(e2);

            etapas[0]->agregarPartido(p);
            gr.agregarPartido(p);

            partidosPorDia[diaAsignado]++;
            ultimoDia[idx1] = diaAsignado;
            ultimoDia[idx2] = diaAsignado;
        }
    }

    etapas[0]->simularEtapa(sim, true);
    etapas[0]->imprimirResultados();
    etapas[0]->imprimirGoleadores();

    for (int g = 0; g < 12; g++)
        sorteoGrupos->getGrupo(g).ordenarEquipos();

    imprimirTablas();
}

void torneo::imprimirTablas() const
{
    for (int g = 0; g < 12; g++)
        sorteoGrupos->getGrupo(g).tablaClasificacion();
}

void torneo::configurarDieciseisavos()
{
    etapas[1] = new fixture("Dieciseisavos de Final");

    equipo* primeros[12];
    equipo* segundos[12];
    equipo* terceros[12];

    for (int g = 0; g < 12; g++)
    {
        primeros[g]  = sorteoGrupos->getGrupo(g).getEquipo(0);
        segundos[g]  = sorteoGrupos->getGrupo(g).getEquipo(1);
        terceros[g]  = sorteoGrupos->getGrupo(g).getEquipo(2);
    }

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11 - i; j++)
        {
            if (terceros[j]->getPuntosT() < terceros[j+1]->getPuntosT())
            {
                equipo* tmp = terceros[j];
                terceros[j] = terceros[j+1];
                terceros[j+1] = tmp;
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        partido* p = new partido();
        p->setFecha("10/07/2026");
        p->setHora("00:00");
        p->setSede("nombreSede");
        p->setArbitro(0, "codArbitro1");
        p->setArbitro(1, "codArbitro2");
        p->setArbitro(2, "codArbitro3");
        p->setEquipo1(primeros[i]);
        p->setEquipo2(terceros[i]);
        etapas[1]->agregarPartido(p);
    }

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11 - i; j++)
        {
            if (segundos[j]->getPuntosT() > segundos[j+1]->getPuntosT())
            {
                equipo* tmp = segundos[j];
                segundos[j] = segundos[j+1];
                segundos[j+1] = tmp;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        partido* p = new partido();
        p->setFecha("10/07/2026");
        p->setHora("00:00");
        p->setSede("nombreSede");
        p->setArbitro(0, "codArbitro1");
        p->setArbitro(1, "codArbitro2");
        p->setArbitro(2, "codArbitro3");
        p->setEquipo1(primeros[8 + i]);
        p->setEquipo2(segundos[i]);
        etapas[1]->agregarPartido(p);
    }

    for (int i = 4; i < 12; i += 2)
    {
        partido* p = new partido();
        p->setFecha("10/07/2026");
        p->setHora("00:00");
        p->setSede("nombreSede");
        p->setArbitro(0, "codArbitro1");
        p->setArbitro(1, "codArbitro2");
        p->setArbitro(2, "codArbitro3");
        p->setEquipo1(segundos[i]);
        p->setEquipo2(segundos[i+1]);
        etapas[1]->agregarPartido(p);
    }

    cout << "\n=== Partidos configurados para Dieciseisavos ===" << endl;

    for (int i = 0; i < etapas[1]->getNumPartidos(); i++)
    {
        partido* p = etapas[1]->getPartido(i);
        cout << p->getEquipo1()->getPais()
             << " vs "
             << p->getEquipo2()->getPais() << endl;
    }
}

void torneo::simularEtapa(int indice)
{
    if (!etapas[indice]) return;
    etapas[indice]->simularEtapa(sim, false);
    etapas[indice]->imprimirResultados();
    etapas[indice]->imprimirGoleadores();

    for (int i = 0; i < etapas[indice]->getNumPartidos(); i++)
    {
        equipo* ganador = etapas[indice]->getPartido(i)->getGanador();
        if (ganador)
            etapas[indice]->agregarClasificado(ganador);
    }
}

void torneo::simularTorneo()
{
    simularEtapa(1);

    etapas[2] = new fixture("Octavos de Final");
    for (int i = 0; i < etapas[1]->getNumClasificados(); i += 2)
    {
        partido* p = new partido();
        p->setFecha("10/07/2026");
        p->setHora("00:00");
        p->setSede("nombreSede");
        p->setArbitro(0, "codArbitro1");
        p->setArbitro(1, "codArbitro2");
        p->setArbitro(2, "codArbitro3");
        p->setEquipo1(etapas[1]->getClasificado(i));
        p->setEquipo2(etapas[1]->getClasificado(i + 1));
        etapas[2]->agregarPartido(p);
    }
    simularEtapa(2);

    etapas[3] = new fixture("Cuartos de Final");
    for (int i = 0; i < etapas[2]->getNumClasificados(); i += 2)
    {
        partido* p = new partido();
        p->setFecha("10/07/2026");
        p->setHora("00:00");
        p->setSede("nombreSede");
        p->setArbitro(0, "codArbitro1");
        p->setArbitro(1, "codArbitro2");
        p->setArbitro(2, "codArbitro3");
        p->setEquipo1(etapas[2]->getClasificado(i));
        p->setEquipo2(etapas[2]->getClasificado(i + 1));
        etapas[3]->agregarPartido(p);
    }
    simularEtapa(3);

    etapas[4] = new fixture("Semifinales");
    for (int i = 0; i < etapas[3]->getNumClasificados(); i += 2)
    {
        partido* p = new partido();
        p->setFecha("10/07/2026");
        p->setHora("00:00");
        p->setSede("nombreSede");
        p->setArbitro(0, "codArbitro1");
        p->setArbitro(1, "codArbitro2");
        p->setArbitro(2, "codArbitro3");
        p->setEquipo1(etapas[3]->getClasificado(i));
        p->setEquipo2(etapas[3]->getClasificado(i + 1));
        etapas[4]->agregarPartido(p);
    }
    simularEtapa(4);

    etapas[5] = new fixture("Tercer Puesto");
    equipo* perdedor1 = nullptr;
    equipo* perdedor2 = nullptr;

    for (int i = 0; i < etapas[4]->getNumPartidos(); i++)
    {
        partido* ps = etapas[4]->getPartido(i);
        equipo* ganador = ps->getGanador();
        equipo* perdedor = (ganador == ps->getEquipo1())
                               ? ps->getEquipo2()
                               : ps->getEquipo1();
        if (i == 0) perdedor1 = perdedor;
        if (i == 1) perdedor2 = perdedor;
    }

    if (perdedor1 && perdedor2)
    {
        partido* p = new partido();
        p->setFecha("10/07/2026");
        p->setHora("00:00");
        p->setSede("nombreSede");
        p->setArbitro(0, "codArbitro1");
        p->setArbitro(1, "codArbitro2");
        p->setArbitro(2, "codArbitro3");
        p->setEquipo1(perdedor1);
        p->setEquipo2(perdedor2);
        etapas[5]->agregarPartido(p);
    }
    simularEtapa(5);

    etapas[6] = new fixture("Final");
    if (etapas[4]->getNumClasificados() >= 2)
    {
        partido* p = new partido();
        p->setFecha("10/07/2026");
        p->setHora("00:00");
        p->setSede("nombreSede");
        p->setArbitro(0, "codArbitro1");
        p->setArbitro(1, "codArbitro2");
        p->setArbitro(2, "codArbitro3");
        p->setEquipo1(etapas[4]->getClasificado(0));
        p->setEquipo2(etapas[4]->getClasificado(1));
        etapas[6]->agregarPartido(p);
    }
    simularEtapa(6);
}

void torneo::generarEstadisticas()
{
    cout << "\n========================================" << endl;
    cout << "    ESTADISTICAS FINALES DEL TORNEO" << endl;
    cout << "========================================" << endl;

    equipo* campeon = nullptr;
    if (etapas[6] && etapas[6]->getNumPartidos() > 0)
        campeon = etapas[6]->getPartido(0)->getGanador();

    equipo* tercero = nullptr;
    equipo* cuarto = nullptr;
    if (etapas[5] && etapas[5]->getNumPartidos() > 0)
    {
        tercero = etapas[5]->getPartido(0)->getGanador();
        cuarto = (tercero == etapas[5]->getPartido(0)->getEquipo1())
                     ? etapas[5]->getPartido(0)->getEquipo2()
                     : etapas[5]->getPartido(0)->getEquipo1();
    }
    equipo* subcampeon = nullptr;
    if (campeon && etapas[6]->getNumPartidos() > 0)
    {
        partido* final = etapas[6]->getPartido(0);
        subcampeon = (campeon == final->getEquipo1())
                         ? final->getEquipo2()
                         : final->getEquipo1();
    }

    cout << "\n1. Ranking top 4:" << endl;
    if (campeon)   cout << "  1° " << campeon->getPais() << endl;
    if (subcampeon)cout << "  2° " << subcampeon->getPais() << endl;
    if (tercero)   cout << "  3° " << tercero->getPais() << endl;
    if (cuarto)    cout << "  4° " << cuarto->getPais() << endl;

    if (campeon)
    {
        cout << "\n2. Maximo goleador de " << campeon->getPais() << ":" << endl;
        int maxGoles = 0;
        int maxCamiseta = 0;
        for (int i = 0; i < campeon->getNumJugadores(); i++)
        {
            if (campeon->getPlantilla()[i].getStats().getGoles() > maxGoles)
            {
                maxGoles = campeon->getPlantilla()[i].getStats().getGoles();
                maxCamiseta = campeon->getPlantilla()[i].getNumeroCamiseta();
            }
        }
        cout << "  Camiseta " << maxCamiseta << " con " << maxGoles << " goles" << endl;
    }

    cout << "\n3. Top 3 goleadores del torneo:" << endl;
    equipo* topEquipo[3] = {nullptr};
    int topCamiseta[3] = {0};
    int topGoles[3] = {0};

    for (int e = 0; e < numEquipos; e++)
    {
        for (int j = 0; j < equipos[e].getNumJugadores(); j++)
        {
            int g = equipos[e].getPlantilla()[j].getStats().getGoles();
            if (g > topGoles[2])
            {
                topGoles[2] = g;
                topEquipo[2] = &equipos[e];
                topCamiseta[2] = equipos[e].getPlantilla()[j].getNumeroCamiseta();
                // ordenar
                for (int k = 2; k > 0 && topGoles[k] > topGoles[k-1]; k--)
                {
                    int tg = topGoles[k]; topGoles[k] = topGoles[k-1]; topGoles[k-1] = tg;
                    int tc = topCamiseta[k]; topCamiseta[k] = topCamiseta[k-1]; topCamiseta[k-1] = tc;
                    equipo* te = topEquipo[k]; topEquipo[k] = topEquipo[k-1]; topEquipo[k-1] = te;
                }
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (topEquipo[i])
            cout << "  " << (i+1) << ". " << topEquipo[i]->getPais()
                 << " camiseta " << topCamiseta[i]
                 << " — " << topGoles[i] << " goles" << endl;
    }

    cout << "\n4. Equipo con mas goles historicos:" << endl;
    equipo* masGoles = &equipos[0];
    for (int i = 1; i < numEquipos; i++)
    {
        if (equipos[i].getStatsHistoricas().getGolesFavor() >
            masGoles->getStatsHistoricas().getGolesFavor())
            masGoles = &equipos[i];
    }
    cout << "  " << masGoles->getPais()
         << " con " << masGoles->getStatsHistoricas().getGolesFavor()
         << " goles historicos" << endl;

    const char* etapasNombres[3] = {"R16", "R8", "R4"};
    int etapasIdx[3] = {1, 2, 3};
    cout << "\n5. Confederacion con mayor presencia:" << endl;
    for (int e = 0; e < 3; e++)
    {
        if (!etapas[etapasIdx[e]]) continue;
        int conteo[6] = {0};
        const char* confs[6] = {"UEFA","CONMEBOL","CONCACAF","CAF","AFC","OFC"};
        for (int i = 0; i < etapas[etapasIdx[e]]->getNumPartidos(); i++)
        {
            partido* p = etapas[etapasIdx[e]]->getPartido(i);
            for (int c = 0; c < 6; c++)
            {
                if (strcmp(p->getEquipo1()->getConfederacion(), confs[c]) == 0) conteo[c]++;
                if (strcmp(p->getEquipo2()->getConfederacion(), confs[c]) == 0) conteo[c]++;
            }
        }
        int maxIdx = 0;
        for (int c = 1; c < 6; c++)
            if (conteo[c] > conteo[maxIdx]) maxIdx = c;
        cout << "  " << etapasNombres[e] << ": " << confs[maxIdx]
             << " (" << conteo[maxIdx] << " equipos)" << endl;
    }
}

ostream& operator<<(ostream& os, const torneo& t) {
    os << "Torneo FIFA 2026 | Equipos: " << t.numEquipos << endl;
    return os;
}
