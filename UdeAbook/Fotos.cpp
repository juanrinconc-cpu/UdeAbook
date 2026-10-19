#include "Fotos.h"
#include<cstring>
#include<iostream>
using namespace std;

foto::foto():fecha_captura(nullptr), ruta(nullptr), tamanio(0), likes(0){

}
char* foto::copiarCadena(const char* origen) {
    if (!origen) return nullptr;
    char* destino = new char[strlen(origen) + 1];
    strcpy(destino, origen);
    return destino;
}
foto::foto(const char* fecha, const char* r, long long t){
    fecha_captura= copiarCadena(fecha);
    ruta=copiarCadena(r);
    tamanio= t;
    likes=0;
}
foto::~foto() {
    delete[] fecha_captura;
    delete[] ruta;
}


const char* foto::getFechaCaptura() const {
    return fecha_captura;
}
const char* foto::getRuta() const {
    return ruta;
}
long long foto::getTamanio() const {
    return tamanio;
}
int foto::getLikes() const {
    return likes;
}
void foto::setFechaCaptura(const char* fecha) {
    delete[] fecha_captura;
    fecha_captura = copiarCadena(fecha);
}
void foto::setRuta(const char* r) {
    delete[] ruta;
    ruta = copiarCadena(r);
}
void foto::setTamano(long long t) {
    tamanio = t;
}
void foto::darLike() {
    likes=likes+1; }
void foto::quitarLike() {
    if (likes > 0){
        likes=likes-1;
    }
}


void foto::mostrar() const{
    cout << "foto en:";
    if (ruta){
        cout << ruta << endl;
    }
    else{
        cout << "Ruta no encontrada" << endl;
    }
    cout << "Fecha de publicación: ";
    if(fecha_captura){
        cout << fecha_captura << endl;
    }
    else{
        cout << "Sin fecha registrada: " << endl;
    }
    cout << "Tamanio" << tamanio << endl;
    cout << "likes" << likes << endl;
}