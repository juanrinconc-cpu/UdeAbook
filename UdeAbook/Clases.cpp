#include "Clases.h"
#include <iostream>
#include <ctime>
#include <fstream>
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

// ======================= Usuario =======================

void Usuario::copiarTexto(char* destino, const char* origen, int max) {
    int i = 0;
    while (origen[i] != '\0' && i < max-1) {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

bool Usuario::compararTexto(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

Usuario::Usuario(const char* c) : amigos(nullptr), num_amigos(0), capacidad(0) {
    copiarTexto(correo, c, 60);
}

Usuario::~Usuario() {
    delete[] amigos;
}

const char* Usuario::getCorreo() const {
    return correo;
}

bool Usuario::esAmigoDe(const Usuario* u) const {
    for (int i = 0; i < num_amigos; i++)
        if (amigos[i] == u) return true;
    return false;
}

bool Usuario::agregarAmigo(Usuario* u) {
    if (u == this || esAmigoDe(u)) return false;
    if (num_amigos == capacidad) {
        int nueva = (capacidad == 0) ? 4 : capacidad * 2;
        Usuario** nuevo = new Usuario*[nueva];
        for (int i = 0; i < num_amigos; i++) nuevo[i] = amigos[i];
        delete[] amigos;
        amigos = nuevo;
        capacidad = nueva;
    }
    amigos[num_amigos++] = u;
    return true;
}

void Usuario::mostrarAmigos() const {
    cout << "Amigos de " << correo << ": ";
    for (int i = 0; i < num_amigos; i++) cout << amigos[i]->getCorreo() << " ";
    cout << endl;
}

// ======================= Plataforma =======================

Plataforma::Plataforma() : usuarios(nullptr), totalUsuarios(0) {}

Plataforma::~Plataforma() {
    for (int i = 0; i < totalUsuarios; i++) delete usuarios[i];
    delete[] usuarios;
}

void Plataforma::cargarUsuarios(const char* archivo) {
    ifstream in(archivo);
    if (!in) { cout << "Error al abrir " << archivo << endl; return; }

    char linea[200];
    int count = 0;
    while (in.getline(linea, 200)) if (linea[0] != '\0') count++;
    if (!in.eof()) { cout << archivo << ": hay una linea de mas de 199 caracteres" << endl; return; }
    in.clear();
    in.seekg(0);

    usuarios = new Usuario*[count];
    totalUsuarios = 0;

    int numLinea = 0;
    while (in.getline(linea, 200)) {
        numLinea++;
        if (linea[0] == '\0') continue;

        char correo[60] = "";
        char buffer[60];
        int campo = 0, j = 0;
        for (int i = 0; ; i++) {
            if (linea[i] == ';' || linea[i] == '\0') {
                buffer[j] = '\0';
                if (campo == 2) Usuario::copiarTexto(correo, buffer, 60);
                campo++;
                j = 0;
                if (linea[i] == '\0') break;
            } else if (j < 59) buffer[j++] = linea[i];
        }
        if (campo < 3 || correo[0] == '\0') {
            cerr << archivo << ":" << numLinea << ": linea invalida, se omite" << endl;
            continue;
        }
        usuarios[totalUsuarios++] = new Usuario(correo);
    }
}

Usuario* Plataforma::buscarPorCorreo(const char* correo) {
    for (int i = 0; i < totalUsuarios; i++)
        if (Usuario::compararTexto(usuarios[i]->getCorreo(), correo))
            return usuarios[i];
    return nullptr;
}

void Plataforma::cargarAmigos(const char* archivo) {
    ifstream in(archivo);
    if (!in) { cerr << "Error al abrir " << archivo << endl; return; }

    char linea[200];
    int numLinea = 0;
    while (in.getline(linea, 200)) {
        numLinea++;
        if (linea[0] == '\0') continue;

        char correo1[60] = "", correo2[60] = "";
        char buffer[60];
        int campo = 0, j = 0;
        for (int i = 0; ; i++) {
            if (linea[i] == ';' || linea[i] == '\0') {
                buffer[j] = '\0';
                if (campo == 0) Usuario::copiarTexto(correo1, buffer, 60);
                if (campo == 1) Usuario::copiarTexto(correo2, buffer, 60);
                campo++;
                j = 0;
                if (linea[i] == '\0') break;
            } else if (j < 59) buffer[j++] = linea[i];
        }
        if (campo != 2 || correo1[0] == '\0' || correo2[0] == '\0') {
            cerr << archivo << ":" << numLinea << ": debe tener exactamente 2 campos" << endl;
            continue;
        }

        Usuario* u1 = buscarPorCorreo(correo1);
        Usuario* u2 = buscarPorCorreo(correo2);
        if (!u1) { cerr << archivo << ":" << numLinea << ": no existe " << correo1 << endl; continue; }
        if (!u2) { cerr << archivo << ":" << numLinea << ": no existe " << correo2 << endl; continue; }
        if (!u1->agregarAmigo(u2)) {
            cerr << archivo << ":" << numLinea << ": amistad repetida o invalida" << endl;
            continue;
        }
        u2->agregarAmigo(u1);
    }
    if (!in.eof()) cerr << archivo << ": se detuvo antes del final (linea demasiado larga)" << endl;
}

void Plataforma::mostrarTodo() {
    for (int i = 0; i < totalUsuarios; i++) usuarios[i]->mostrarAmigos();
}