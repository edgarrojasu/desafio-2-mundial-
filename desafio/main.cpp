#include <iostream>
#include "estadisticaspartido.h"
using namespace std;

int main() {
    estadisticaspartido ep;
    ep.setGolesFavor(2);
    ep.setGolesContra(1);
    ep.setPosesionBalon(60.5f);
    ep.setConvocado(0, 9);
    ep.setGolesConvocado(0, 2);

    cout << ep << endl;
    cout << "Camiseta convocado 0: " << ep.getConvocado(0) << endl;
    cout << "Goles convocado 0: " << ep.getGolesConvocado(0) << endl;

    return 0;
}
