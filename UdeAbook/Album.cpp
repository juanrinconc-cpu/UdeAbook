#include "Album.h"
#include <iostream>
#include <cstring>
using namespace std;

char* Album::copiarCadena(const char* origen) {
    if (!origen) return nullptr;
    char* destino = new char[strlen(origen) + 1];
    strcpy(destino, origen);
    return destino;
}


Album::Album() : nombre(nullptr), ruta(nullptr), privacidad(nullptr),
    fotos(nullptr), num_fotos(0), capacidad_fotos(0) {}

Album::Album(const char* n, const char* r, const char* p) {
    nombre = copiarCadena(n);
    ruta = copiarCadena(r);
    privacidad = copiarCadena(p);
    fotos = nullptr;
    num_fotos = 0;
    capacidad_fotos = 0;
}

Album::~Album() {
    delete[] nombre;
    delete[] ruta;
    delete[] privacidad;

    for (int i = 0; i < num_fotos; i++) {
        delete fotos[i];
    }
    delete[] fotos;
}

bool Album::agregar_foto(foto* nuevaFoto) {
    if (num_fotos == capacidad_fotos) {
        int nueva = (capacidad_fotos == 0) ? 4 : capacidad_fotos * 2;

        foto** nuevo = new foto*[nueva];
        for (int i = 0; i < num_fotos; i++) {
            nuevo[i] = fotos[i];
        }
        delete[] fotos;
        fotos = nuevo;
        capacidad_fotos = nueva;
    }

    fotos[num_fotos++] = nuevaFoto;
    return true;
}

void Album::mostrar_fotos() {
    cout << "Álbum: ";
    if(nombre){
        cout << nombre << endl;
    }
    else{
        cout << "Sin nombre" << endl;
    }
    cout << "Ruta: ";
    if(ruta){
        cout << ruta << endl;
    }
    else{
        cout << "Sin ruta" << endl;
    }
    cout << "privacidad: ";

    if(privacidad){
        cout << privacidad << endl;
    }
    cout << "Número de fotos: " << num_fotos << endl;

    for (int i = 0; i < num_fotos; i++) {
        cout << "Foto #" << (i+1) << ": ";
        fotos[i]->mostrar();
    }
}
const char* Album::getNombre() const { return nombre; }
const char* Album::getRuta() const { return ruta; }
const char* Album::getPrivacidad() const { return privacidad; }
int Album::getNumFotos() const { return num_fotos; }
int Album::getCapacidadFotos() const { return capacidad_fotos; }

void Album::setNombre(const char* n) {
    delete[] nombre;
    nombre = copiarCadena(n);
}

void Album::setRuta(const char* r) {
    delete[] ruta;
    ruta = copiarCadena(r);
}

void Album::setPrivacidad(const char* p) {
    delete[] privacidad;
    privacidad = copiarCadena(p);
}

foto* Album::getFoto(int indice) const {
    if (indice < 0 || indice >= num_fotos) return nullptr;
    return fotos[indice];
}

void Album::darLikeFoto(int indice) {
    if (indice >= 0 && indice < num_fotos) {
        fotos[indice]->darLike();
    }
}
void Album::quitarLikeFoto(int indice) {
    if (indice >= 0 && indice < num_fotos) {
        fotos[indice]->quitarLike();
    }
}