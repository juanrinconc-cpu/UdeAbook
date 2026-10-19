#include "Amistades.h"

amistades::amistades()
    :solicitudes(nullptr), num_solicitudes(0), capacidad_solicitudes(0){
}
amistades::~amistades(){
    delete[]solicitudes;
}

bool amistades:: agregar_Solicitud(Usuario* u){
    if (num_solicitudes==capacidad_solicitudes){
        int nueva;
        if (capacidad_solicitudes==0){
            nueva=4;
        }
        else{
            nueva=capacidad_solicitudes*2;
        }
        Usuario** nuevo = new Usuario*[nueva];
        for(int i=0; i < num_solicitudes;i++){
            nuevo[i]=solicitudes[i];
        }
        delete[]solicitudes;
        solicitudes=nuevo;
        capacidad_solicitudes=nueva;

    }
    solicitudes[num_solicitudes]=u;
    num_solicitudes=num_solicitudes+1;
    return true;
}