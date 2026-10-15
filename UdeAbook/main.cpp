#include "Clases.h"
#include <iostream>
using namespace std;


int main() {
    Fecha f;
    f.setFechaTexto("2001-11-25");
    cout << "Fecha leida del archivo: " << f.getFechaTexto() << endl;
    cout << "Fecha actual del sistema: " << f.getFechaActual() << endl;
    cout << "Hora actual del sistema: " << f.getHoraActual() << endl;
    return 0;
}
