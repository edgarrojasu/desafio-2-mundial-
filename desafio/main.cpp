#include <iostream>
#include "estadisticasjugador.h"
using namespace std;

int main()
{
    estadisticasjugador e1;
    e1.setGoles(3);
    e1.setFaltas(2);

    estadisticasjugador e2;
    e2.setGoles(1);
    e2.setFaltas(1);

    e1 += e2;
    cout << e1 << endl;

    return 0;
}
