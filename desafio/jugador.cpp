#include "jugador.h"
#include "medidorrecursos.h"

jugador::jugador()
{
    nombre = new char[1];
    medidor.sumarMemoria(1);
    nombre[0] = '\0';
    apellido = new char[1];
    medidor.sumarMemoria(1);
    apellido[0] = '\0';
    numeroCamiseta = 0;
}

jugador::jugador(const jugador& otro)
{
    nombre = new char[strlen(otro.nombre) + 1];
    medidor.sumarMemoria(strlen(otro.nombre) + 1);
    strcpy(nombre, otro.nombre);
    apellido = new char[strlen(otro.apellido) + 1];
    medidor.sumarMemoria(strlen(otro.apellido) + 1);
    strcpy(apellido, otro.apellido);
    numeroCamiseta = otro.numeroCamiseta;
    stats = otro.stats;
}

jugador::~jugador()
{
    medidor.restarMemoria(strlen(nombre) + 1);
    medidor.restarMemoria(strlen(apellido) + 1);
    delete[] nombre;
    delete[] apellido;
}

jugador& jugador::operator=(const jugador& otro)
{
    if (this != &otro)
    {
        medidor.restarMemoria(strlen(nombre) + 1);
        medidor.restarMemoria(strlen(apellido) + 1);
        delete[] nombre;
        delete[] apellido;
        nombre = new char[strlen(otro.nombre) + 1];
        medidor.sumarMemoria(strlen(otro.nombre) + 1);
        strcpy(nombre, otro.nombre);
        apellido = new char[strlen(otro.apellido) + 1];
        medidor.sumarMemoria(strlen(otro.apellido) + 1);
        strcpy(apellido, otro.apellido);
        numeroCamiseta = otro.numeroCamiseta;
        stats = otro.stats;
    }
    return *this;
}

char* jugador::getNombre() const { return nombre; }
char* jugador::getApellido() const { return apellido; }
int jugador::getNumeroCamiseta() const { return numeroCamiseta; }
estadisticasjugador& jugador::getStats() { return stats; }

void jugador::setNombre(const char* valor)
{
    medidor.restarMemoria(strlen(nombre) + 1);
    delete[] nombre;
    nombre = new char[strlen(valor) + 1];
    medidor.sumarMemoria(strlen(valor) + 1);
    strcpy(nombre, valor);
}

void jugador::setApellido(const char* valor)
{
    medidor.restarMemoria(strlen(apellido) + 1);
    delete[] apellido;
    apellido = new char[strlen(valor) + 1];
    medidor.sumarMemoria(strlen(valor) + 1);
    strcpy(apellido, valor);
}

void jugador::setNumeroCamiseta(int valor)
{
    numeroCamiseta = valor;
}

bool jugador::operator==(const jugador& otro) const
{
    return numeroCamiseta == otro.numeroCamiseta;
}

ostream& operator<<(ostream& os, const jugador& j)
{
    os << "Camiseta: " << j.numeroCamiseta
       << " | Nombre: " << j.nombre
       << " " << j.apellido
       << " | " << j.stats;
    return os;
}
