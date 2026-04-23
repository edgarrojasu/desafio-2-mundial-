#include "estadisticasequipo.h"

estadisticasequipo::estadisticasequipo()
{
    golesFavor = 0;
    golesContra = 0;
    partidosGanados = 0;
    partidosEmpatados = 0;
    partidosPerdidos = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
}

estadisticasequipo::estadisticasequipo(const estadisticasequipo& otra)
{
    golesFavor = otra.golesFavor;
    golesContra = otra.golesContra;
    partidosGanados = otra.partidosGanados;
    partidosEmpatados = otra.partidosEmpatados;
    partidosPerdidos = otra.partidosPerdidos;
    tarjetasAmarillas = otra.tarjetasAmarillas;
    tarjetasRojas = otra.tarjetasRojas;
    faltas = otra.faltas;
}

int estadisticasequipo::getGolesFavor() const { return golesFavor; }
int estadisticasequipo::getGolesContra() const { return golesContra; }
int estadisticasequipo::getPartidosGanados() const { return partidosGanados; }
int estadisticasequipo::getPartidosEmpatados() const { return partidosEmpatados; }
int estadisticasequipo::getPartidosPerdidos() const { return partidosPerdidos; }
int estadisticasequipo::getTarjetasAmarillas() const { return tarjetasAmarillas; }
int estadisticasequipo::getTarjetasRojas() const { return tarjetasRojas; }
int estadisticasequipo::getFaltas() const { return faltas; }

void estadisticasequipo::setGolesFavor(int valor) { golesFavor = valor; }
void estadisticasequipo::setGolesContra(int valor) { golesContra = valor; }
void estadisticasequipo::setPartidosGanados(int valor) { partidosGanados = valor; }
void estadisticasequipo::setPartidosEmpatados(int valor) { partidosEmpatados = valor; }
void estadisticasequipo::setPartidosPerdidos(int valor) { partidosPerdidos = valor; }
void estadisticasequipo::setTarjetasAmarillas(int valor) { tarjetasAmarillas = valor; }
void estadisticasequipo::setTarjetasRojas(int valor) { tarjetasRojas = valor; }
void estadisticasequipo::setFaltas(int valor) { faltas = valor; }

estadisticasequipo& estadisticasequipo::operator+=(const estadisticasequipo& otra)
{
    golesFavor += otra.golesFavor;
    golesContra += otra.golesContra;
    partidosGanados += otra.partidosGanados;
    partidosEmpatados += otra.partidosEmpatados;
    partidosPerdidos += otra.partidosPerdidos;
    tarjetasAmarillas += otra.tarjetasAmarillas;
    tarjetasRojas += otra.tarjetasRojas;
    faltas += otra.faltas;
    return *this;
}

ostream& operator<<(ostream& os, const estadisticasequipo& stats)
{
    os << "GF: " << stats.golesFavor
       << " | GC: " << stats.golesContra
       << " | PG: " << stats.partidosGanados
       << " | PE: " << stats.partidosEmpatados
       << " | PP: " << stats.partidosPerdidos
       << " | Amarillas: " << stats.tarjetasAmarillas
       << " | Rojas: " << stats.tarjetasRojas
       << " | Faltas: " << stats.faltas;
    return os;
}

estadisticasequipo& estadisticasequipo::operator=(const estadisticasequipo& otra)
{
    if (this != &otra) {
        golesFavor = otra.golesFavor;
        golesContra = otra.golesContra;
        partidosGanados = otra.partidosGanados;
        partidosEmpatados = otra.partidosEmpatados;
        partidosPerdidos = otra.partidosPerdidos;
        tarjetasAmarillas = otra.tarjetasAmarillas;
        tarjetasRojas = otra.tarjetasRojas;
        faltas = otra.faltas;
    }
    return *this;
}
