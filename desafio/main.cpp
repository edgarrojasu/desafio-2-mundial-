#include <iostream>
#include "estadisticasequipo.h"
using namespace std;

int main() {
    estadisticasequipo e1;
    e1.setGolesFavor(5);
    e1.setPartidosGanados(2);

    estadisticasequipo e2;
    e2.setGolesFavor(3);
    e2.setPartidosGanados(1);

    e1 += e2;
    cout << e1 << endl;

    return 0;
}
