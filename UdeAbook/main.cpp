#include <iostream>
#include <fstream>
#include <cstring>
#include "Usuarios.h"
#include "Clases.h"
#include "Album.h"
#include "Fotos.h"
#include "Mensajes.h"

using namespace std;


char** usuariosLogin = nullptr;
char** contrasenasLogin = nullptr;
int cantidadLogin = 0;

void cargarCredenciales(){
    ifstream archivo("login.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir login.txt" << endl;
        return;
    }

    int capacidad = 10;
    usuariosLogin = new char*[capacidad];
    contrasenasLogin = new char*[capacidad];

    char linea[256];
    while (archivo.getline(linea, sizeof(linea))) {
        if (strlen(linea) == 0) continue;

        char* usuario = strtok(linea, "|");
        char* contrasena = strtok(nullptr, "|");

        if (!usuario || !contrasena) continue;

        if (cantidadLogin == capacidad) {
            capacidad *= 2;
            char** nuevosUsuarios = new char*[capacidad];
            char** nuevasContrasenas = new char*[capacidad];
            for (int i = 0; i < cantidadLogin; i++) {
                nuevosUsuarios[i] = usuariosLogin[i];
                nuevasContrasenas[i] = contrasenasLogin[i];
            }
            delete[] usuariosLogin;
            delete[] contrasenasLogin;
            usuariosLogin = nuevosUsuarios;
            contrasenasLogin = nuevasContrasenas;
        }

        usuariosLogin[cantidadLogin] = new char[strlen(usuario)+1];
        strcpy(usuariosLogin[cantidadLogin], usuario);

        contrasenasLogin[cantidadLogin] = new char[strlen(contrasena)+1];
        strcpy(contrasenasLogin[cantidadLogin], contrasena);

        cantidadLogin++;
    }
    archivo.close();
}


int autenticar() {
    char usuario[60], contrasena[60];
    cout << "Ingrese usuario: ";
    cin >> usuario;
    cout << "Ingrese contrasenia: ";
    cin >> contrasena;

    for (int i = 0; i < cantidadLogin; i++) {
        if (strcmp(usuariosLogin[i], usuario) == 0 &&
            strcmp(contrasenasLogin[i], contrasena) == 0) {
            cout << "Acceso permitido. Bienvenido " << usuariosLogin[i] << endl;
            return i;
        }
    }
    cout << "Usuario o contrasenia incorrectos."<< endl;
    return -1;
}


int main() {
    cargarCredenciales();
    if (cantidadLogin == 0) {
        cout << "No hay credenciales cargadas" << endl;
        return 1;
    }

    int indice = autenticar();
    if (indice < 0) return 1;

    long long it = 0;
    int cantidadUsuarios = 0;
    Usuario** usuarios = cargarUsuarios(cantidadUsuarios, it);

    Usuario* activo = buscarUsuario(usuarios, cantidadUsuarios, usuariosLogin[indice], it);
    if (!activo) {
        cout << "No se encontro el perfil del usuario autenticado" << endl;
        return 1;
    }

    Album* albumActivo = new Album("Principal", "C:/imagenes", "amigos");
    Mensaje** mensajes = new Mensaje*[10];
    int numMensajes = 0;

    char opcion;
    do {
        cout << "\nBienvenido a UdeaBook //" << activo->getNombre() << endl;
        cout << "1. Ver album\n2. Agregar foto\n3. Enviar mensaje\n4. Ver amigos\nS. Salir\nOpcion: ";
        cin >> opcion;

        if (opcion == '1') {
            albumActivo->mostrar_fotos();
        } else if (opcion == '2') {
            char ruta[200], fecha[20];
            long long tam;
            cout << "Ruta de la foto: ";
            cin >> ruta;
            cout << "Fecha (AAAA-MM-DD): ";
            cin >> fecha;
            cout << "Tamaño en bytes: ";
            cin >> tam;
            foto* f = new foto(fecha, ruta, tam);
            albumActivo->agregar_foto(f);
        } else if (opcion == '3') {
            char destino[60], contenido[200], fecha[20];
            cout << "Enviar mensaje a: ";
            cin >> destino;
            Usuario* receptor = buscarUsuario(usuarios, cantidadUsuarios, destino, it);
            if (!receptor) {
                cout << "Usuario no encontrado" << endl;
            } else {
                cout << "Contenido del mensaje: ";
                cin.ignore();
                cin.getline(contenido, 200);
                strcpy(fecha, "2026-10-18");
                mensajes[numMensajes++] = new Mensaje(activo->getNombre(), receptor->getNombre(), contenido, fecha);
                cout << "Mensaje enviado" << endl;
            }
        } else if (opcion == '4') {
            activo->mostrar_amigos();
        }
    } while (opcion != 'S' && opcion != 's');

    delete albumActivo;
    for (int i = 0; i < numMensajes; i++) delete mensajes[i];
    delete[] mensajes;
    for (int i = 0; i < cantidadUsuarios; i++) delete usuarios[i];
    delete[] usuarios;

    for (int i = 0; i < cantidadLogin; i++) {
        delete[] usuariosLogin[i];
        delete[] contrasenasLogin[i];
    }
    delete[] usuariosLogin;
    delete[] contrasenasLogin;

    return 0;
}

