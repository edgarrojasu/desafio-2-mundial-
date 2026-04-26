#include "medidorrecursos.h"
#include <cstring>

medidorrecursos medidor;

medidorrecursos::medidorrecursos()
{
    iteraciones = 0;
    memoriaUsada = 0;
    llamadasLibrerias = 0;
    descripcionLibreria = new char[1];
    memoriaUsada += 1;
    descripcionLibreria[0] = '\0';
}

medidorrecursos::medidorrecursos(const medidorrecursos& otro)
{
    iteraciones = otro.iteraciones;
    memoriaUsada = otro.memoriaUsada;
    llamadasLibrerias = otro.llamadasLibrerias;
    descripcionLibreria = new char[strlen(otro.descripcionLibreria) + 1];
    memoriaUsada += strlen(otro.descripcionLibreria) + 1;
    strcpy(descripcionLibreria, otro.descripcionLibreria);
}

medidorrecursos::~medidorrecursos()
{
    memoriaUsada -= strlen(descripcionLibreria) + 1;
    delete[] descripcionLibreria;
}

medidorrecursos& medidorrecursos::operator=(const medidorrecursos& otro)
{
    if (this != &otro)
    {
        memoriaUsada -= strlen(descripcionLibreria) + 1;
        delete[] descripcionLibreria;
        iteraciones = otro.iteraciones;
        memoriaUsada = otro.memoriaUsada;
        llamadasLibrerias = otro.llamadasLibrerias;
        descripcionLibreria = new char[strlen(otro.descripcionLibreria) + 1];
        memoriaUsada += strlen(otro.descripcionLibreria) + 1;
        strcpy(descripcionLibreria, otro.descripcionLibreria);
    }
    return *this;
}

long medidorrecursos::getIteraciones() const { return iteraciones; }
long medidorrecursos::getMemoriaUsada() const { return memoriaUsada; }
long medidorrecursos::getLlamadasLibrerias() const { return llamadasLibrerias; }
char* medidorrecursos::getDescripcionLibreria() const { return descripcionLibreria; }

void medidorrecursos::contarIteracion()
{
    iteraciones++;
}

void medidorrecursos::sumarMemoria(long bytes)
{
    memoriaUsada += bytes;
}

void medidorrecursos::restarMemoria(long bytes)
{
    memoriaUsada -= bytes;
}

void medidorrecursos::registrarLlamadaLibreria(const char* descripcion)
{
    llamadasLibrerias++;
    int lenActual = strlen(descripcionLibreria);
    int lenNueva  = strlen(descripcion);
    char* nuevo   = new char[lenActual + lenNueva + 3];
    memoriaUsada += lenActual + lenNueva + 3;
    strcpy(nuevo, descripcionLibreria);
    if (lenActual > 0)
    {
        nuevo[lenActual]     = ',';
        nuevo[lenActual + 1] = ' ';
        nuevo[lenActual + 2] = '\0';
    }
    strcat(nuevo, descripcion);
    memoriaUsada -= strlen(descripcionLibreria) + 1;
    delete[] descripcionLibreria;
    descripcionLibreria = nuevo;
}

void medidorrecursos::resetear()
{
    iteraciones = 0;
    memoriaUsada = 0;
    llamadasLibrerias = 0;
    delete[] descripcionLibreria;
    descripcionLibreria = new char[1];
    memoriaUsada += 1;
    descripcionLibreria[0] = '\0';
}

void medidorrecursos::imprimir() const
{
    cout << "\n--- Medicion de recursos ---" << endl;
    cout << "Iteraciones:          " << iteraciones << endl;
    cout << "Memoria usada:        " << memoriaUsada << " bytes" << endl;
    cout << "Llamadas a librerias: " << llamadasLibrerias << endl;
    if (llamadasLibrerias > 0)
        cout << "Librerias usadas:     " << descripcionLibreria << endl;
    cout << "----------------------------" << endl;
}

ostream& operator<<(ostream& os, const medidorrecursos& m)
{
    os << "Iteraciones: " << m.iteraciones
       << " | Memoria: " << m.memoriaUsada << " bytes"
       << " | Llamadas librerias: " << m.llamadasLibrerias;
    return os;
}
