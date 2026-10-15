#include "Clases.h"
#include <iostream>
#include <ctime>
using namespace std;

Fecha::Fecha() {

    fecha_texto=new char[11];
    fecha_actual=new char[12];
    hora_actual=new char[8];

    time_t now = time(nullptr);
    char* fechaCompleta = ctime(&now);

    for (int i = 0; i < 12; i++) {
        fecha_actual[i] = fechaCompleta[4 + i];
    }
    fecha_actual[12] = '\0';


    for (int i = 0; i < 8; i++) {
        hora_actual[i] = fechaCompleta[11 + i];
    }
    hora_actual[8] = '\0';


    fecha_texto[0] = '\0';

}
Fecha::~Fecha() {
    delete[] fecha_texto;
    delete[] fecha_actual;
    delete[] hora_actual;
}

void Fecha::setFechaTexto(const char* f) {
    int i = 0;
    while (f[i] != '\0' && i < 19) {
        fecha_texto[i] = f[i];
        i++;
    }
    fecha_texto[i] = '\0';
}

const char* Fecha::getFechaTexto() const {
    return fecha_texto;
}

const char* Fecha::getFechaActual() const {
    return fecha_actual;
}

const char* Fecha::getHoraActual() const {
    return hora_actual;
}