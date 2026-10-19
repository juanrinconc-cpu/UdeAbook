#include "Mensajes.h"
#include <iostream>
#include <cstring>
using namespace std;

Mensaje::Mensaje():
    emisor(nullptr), receptor(nullptr), mensaje_enviado(nullptr), fecha_envio(nullptr), leido(false){
}
Mensaje::Mensaje(const char* e, const char* r, const char* c, const char * f){
    emisor= copiar_cadena(e);
    receptor = copiar_cadena(r);
    mensaje_enviado =copiar_cadena(c);
    fecha_envio= copiar_cadena(f);
    leido=false;
}
Mensaje::~Mensaje(){
    delete[] emisor;
    delete[] receptor;
    delete[] mensaje_enviado;
    delete[]fecha_envio;
}

const char* Mensaje::getEmisor() {
    return emisor;

}
const char* Mensaje::getReceptor(){
    return receptor;
}
const char* Mensaje::getContenido(){
    return mensaje_enviado;
}
const char* Mensaje::getFechaEnvio(){
    return fecha_envio;
}
bool Mensaje::estaLeido(){
    return leido;
}

void Mensaje::setContenido(const char * c){
    delete[]mensaje_enviado;
    mensaje_enviado= copiar_cadena(c);

}
void Mensaje::setFechaEnvio(const char * f){
    delete[]fecha_envio;
    fecha_envio=copiar_cadena(f);
}
void Mensaje::marcarLeido(){
    leido=true;
}


char* Mensaje::copiar_cadena(const char* origen){
    if (!origen){
        return nullptr;
    }
    char* destino= new char[strlen(origen)+1];
    strcpy(destino,origen);
    return destino;
}

void Mensaje::mostrar(){
    if (!emisor){
        cout << "No existe información del emisor" << endl;
    }
    else{
        cout << "De: " << emisor << endl;
    }
    if (!fecha_envio){
        cout << "No registra fecha " << endl;
    }
    else{
        cout <<"Enviado el: " << fecha_envio << endl;

    }
    if(!mensaje_enviado){
        cout << "El mensaje esta vacio " << endl;
    }
    else{
        cout << mensaje_enviado << endl;
        if (leido){
            cout << "Leido" << endl;
        }
        else{
            cout << "No leido" << endl;
        }
    }

}

