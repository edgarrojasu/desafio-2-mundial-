#ifndef MEDIDORRECURSOS_H
#define MEDIDORRECURSOS_H

#include <iostream>
using namespace std;

class medidorrecursos {
private:
    long iteraciones;
    long memoriaUsada;
    long llamadasLibrerias;
    char* descripcionLibreria;

public:
    medidorrecursos();
    medidorrecursos(const medidorrecursos& otro);
    ~medidorrecursos();

    long getIteraciones() const;
    long getMemoriaUsada() const;
    long getLlamadasLibrerias() const;
    char* getDescripcionLibreria() const;

    void contarIteracion();
    void sumarMemoria(long bytes);
    void restarMemoria(long bytes);
    void registrarLlamadaLibreria(const char* descripcion);
    void resetear();
    void imprimir() const;

    medidorrecursos& operator=(const medidorrecursos& otro);
    friend ostream& operator<<(ostream& os, const medidorrecursos& m);
};

// instancia global accesible desde cualquier clase
extern medidorrecursos medidor;

#endif // MEDIDORRECURSOS_H
