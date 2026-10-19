#ifndef AMISTADES_H
#define AMISTADES_H
#include "Clases.h"
class amistades{
private:
    Usuario** solicitudes;
    int num_solicitudes;
    int capacidad_solicitudes;
public:
    amistades();
    ~amistades();
    bool agregar_Solicitud(Usuario* u);
    bool hay_solicitudes();
    void mostrar_Solicitudes();
    bool aceptar_solicitudes();

};

#endif // AMISTADES_H
