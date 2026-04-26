#include "sorteo.h"
#include "medidorrecursos.h"

sorteo::sorteo()
{
    numGrupos = 12;
    grupos = new grupo[numGrupos];
    medidor.sumarMemoria(sizeof(grupo) * numGrupos);
    for (int i = 0; i < 4; i++) tamBombos[i] = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 12; j++)
            bombos[i][j] = nullptr;

    char letras[12] = {'A','B','C','D','E','F','G','H','I','J','K','L'};
    for (int i = 0; i < 12; i++)
        grupos[i].setLetra(letras[i]);
}

sorteo::sorteo(const sorteo& otro)
{
    numGrupos = otro.numGrupos;
    grupos = new grupo[numGrupos];
    medidor.sumarMemoria(sizeof(grupo) * numGrupos);
    for (int i = 0; i < numGrupos; i++)
        grupos[i] = otro.grupos[i];
    for (int i = 0; i < 4; i++) {
        tamBombos[i] = otro.tamBombos[i];
        for (int j = 0; j < 12; j++)
            bombos[i][j] = otro.bombos[i][j];
    }
}

sorteo::~sorteo()
{
    medidor.restarMemoria(sizeof(grupo) * numGrupos);
    delete[] grupos;
}

sorteo& sorteo::operator=(const sorteo& otro)
{
    if (this != &otro)
    {
        medidor.restarMemoria(sizeof(grupo) * numGrupos);
        delete[] grupos;
        numGrupos = otro.numGrupos;
        grupos = new grupo[numGrupos];
        medidor.sumarMemoria(sizeof(grupo) * numGrupos);
        for (int i = 0; i < numGrupos; i++)
            grupos[i] = otro.grupos[i];
        for (int i = 0; i < 4; i++) {
            tamBombos[i] = otro.tamBombos[i];
            for (int j = 0; j < 12; j++)
                bombos[i][j] = otro.bombos[i][j];
        }
    }
    return *this;
}

grupo* sorteo::getGrupos() const { return grupos; }
grupo& sorteo::getGrupo(int i) const { return grupos[i]; }
int sorteo::getNumGrupos() const { return numGrupos; }

void sorteo::ordenarPorRanking(equipo** lista, int tam)
{
    for (int i = 0; i < tam - 1; i++)
    {
        for (int j = 0; j < tam - i - 1; j++)
        {
            if (lista[j]->getRankingFIFA() > lista[j+1]->getRankingFIFA())
            {
                equipo* temp = lista[j];
                lista[j]     = lista[j+1];
                lista[j+1]   = temp;
            }
        }
    }
}

void sorteo::armarBombos(equipo* equipos, int numEquipos)
{
    equipo* sinUSA[47];
    int tamSinUSA = 0;
    equipo* usa = nullptr;

    for (int i = 0; i < numEquipos; i++)
    {
        if (strcmp(equipos[i].getPais(), "United States") == 0 ||
            strcmp(equipos[i].getPais(), "USA") == 0 ||
            strcmp(equipos[i].getPais(), "United States of America") == 0) {
            usa = &equipos[i];
        }
        else
        {
            sinUSA[tamSinUSA++] = &equipos[i];
        }
    }

    ordenarPorRanking(sinUSA, tamSinUSA);

    if (usa)
    {
        bombos[0][tamBombos[0]++] = usa;
    }

    for (int i = 0; i < 11 && tamSinUSA > 0; i++)
    {
        bombos[0][tamBombos[0]++] = sinUSA[i];
    }
    for (int i = 11; i < 23 && i < tamSinUSA; i++)
    {
        bombos[1][tamBombos[1]++] = sinUSA[i];
    }
    for (int i = 23; i < 35 && i < tamSinUSA; i++)
    {
        bombos[2][tamBombos[2]++] = sinUSA[i];
    }
    for (int i = 35; i < 47 && i < tamSinUSA; i++)
    {
        bombos[3][tamBombos[3]++] = sinUSA[i];
    }
}

bool sorteo::puedeAgregarseAlGrupo(grupo& g, equipo* e) const
{
    const char* conf = e->getConfederacion();
    if (strcmp(conf, "UEFA") == 0)
    {
        return g.contarConfederacion("UEFA") < 2;
    }
    return !g.tieneConfederacion(conf);
}

void sorteo::formarGrupos()
{
    equipo* usa = nullptr;
    int usaIdx = -1;
    for (int i = 0; i < tamBombos[0]; i++)
    {
        if (strcmp(bombos[0][i]->getPais(), "United States") == 0 || strcmp(bombos[0][i]->getPais(), "USA") == 0 ||
            strcmp(bombos[0][i]->getPais(), "United States of America") == 0)
        {
            usa = bombos[0][i];
            usaIdx = i;
            break;
        }
    }
    if (usa)
    {
        grupos[0].agregarEquipo(usa);
    }

    for (int bombo = 0; bombo < 4; bombo++)
    {
        equipo* disponibles[12];
        bool usado[12] = {false};
        int tam = tamBombos[bombo];
        for (int i = 0; i < tam; i++)
            disponibles[i] = bombos[bombo][i];

        if (bombo == 0 && usaIdx >= 0)
            usado[usaIdx] = true;

        for (int g = 0; g < numGrupos; g++)
        {
            if (g == 0 && bombo == 0) continue;

            bool asignado = false;
            int intentos = 0;

            while (!asignado && intentos < 1000)
            {
                int candidatos[12];
                int numCandidatos = 0;
                for (int i = 0; i < tam; i++)
                {
                    if (!usado[i])
                        candidatos[numCandidatos++] = i;
                }

                if (numCandidatos == 0) break;

                int idx = candidatos[rand() % numCandidatos];
                equipo* candidato = disponibles[idx];

                if (puedeAgregarseAlGrupo(grupos[g], candidato))
                {
                    grupos[g].agregarEquipo(candidato);
                    usado[idx] = true;
                    asignado = true;
                }
                intentos++;
            }

            if (!asignado)
            {
                for (int i = 0; i < tam; i++)
                {
                    if (!usado[i])
                    {
                        grupos[g].agregarEquipo(disponibles[i]);
                        usado[i] = true;
                        break;
                    }
                }
            }
        }
    }
}

void sorteo::imprimirGrupos() const
{
    for (int i = 0; i < numGrupos; i++)
    {
        cout << grupos[i] << endl;
    }
}

ostream& operator<<(ostream& os, const sorteo& s)
{
    for (int i = 0; i < s.numGrupos; i++)
        os << s.grupos[i] << endl;
    return os;
}
