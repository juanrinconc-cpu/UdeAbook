#include "Usuarios.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <random>
using namespace std;

void creacion_usuarios() {
    ofstream archivo("usuariosudeabook.txt");
    cout << "ruta del archivo " << filesystem::current_path() << endl;;
    try {
        if (archivo.fail()) {
            throw runtime_error("No se pudo crear el archivo usuarios.txt");
        }

        const char* name_users[] = {"Juan", "Sofia", "Paulina", "Jose", "Victor","Manuel","Sara","Luisa","Tobias","Pepito","Anibal"};
        const char* city[] = {"Cali", "Medellin", "Bogota", "Choco", "Santa Marta"};
        const char* fechanac[] = {"1998-05-12", "2001-11-03", "2002-09-16", "1999-09-17", "2002-12-01"};

        srand(time(0));

        for (int i = 1; i <= 1000; i++) {
            int anio = 2014 + rand() % 12;
            int mes  = 1 + rand() % 12;
            int dia  = 1 + rand() % 30;

            char fecha[11];
            sprintf(fecha, "%04d-%02d-%02d", anio, mes, dia);

            const char* citys = city[rand() % 5];
            const char* names = name_users[rand() % 11];
            const char* naci  = fechanac[rand() % 5];

            archivo << names << i << "|"<< naci << "|"<< names << i << "@correoudebook.com"<<"|"<< citys << "|"<< "Colombia"<< "|"<< fecha << endl;

            if (archivo.fail()) {
                throw runtime_error("Error en la escritura del archivo");
            }
        }

        archivo.close();
        cout << "Archivo usuarios.txt generado con 1000 registros." << endl;
    }
    catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    catch (...) {
        cout << "Error desconocido durante la creacion de usuarios." << endl;
    }
}

void generar_amistades(){
    const int MAX_USERS=1000;
    string* usuarios=new string[MAX_USERS];
    int cantidad_usuarios=0;

    ifstream archivo_usuarios("usuariosudeabook.txt");
    if (!archivo_usuarios.is_open()) {
        cout << "Error: no se pudo abrir usuarios.txt\n";
        delete[] usuarios;
        return;
    }


    string linea;

    while (getline(archivo_usuarios, linea)
           && cantidad_usuarios < MAX_USERS) {

        if (linea.empty()) {
            continue;
        }

        size_t separador = linea.find('|');

        if (separador == string::npos || separador == 0) {
            continue;
        }

        string nombre = linea.substr(0, separador);

        bool existe = false;

        for (int i = 0; i < cantidad_usuarios; i++) {
            if (usuarios[i] == nombre) {
                existe = true;
                break;
            }
        }

        if (!existe) {
            usuarios[cantidad_usuarios] = nombre;
            cantidad_usuarios++;
        }
    }

    archivo_usuarios.close();

    if (cantidad_usuarios < 2) {
        cout << "Error: se necesitan al menos dos usuarios." << endl;
        delete[] usuarios;
        return;
    }

    bool** amistades = new bool*[cantidad_usuarios];

    for (int i = 0; i < cantidad_usuarios; i++) {
        amistades[i] = new bool[cantidad_usuarios];

        for (int j = 0; j < cantidad_usuarios; j++) {
            amistades[i][j] = false;
        }
    }

    random_device rd;
    mt19937 generador(rd());


    int minimoAmigos = 1;
    int maximoAmigos = cantidad_usuarios-1;

    if (cantidad_usuarios - 1 < minimoAmigos) {
        minimoAmigos = cantidad_usuarios - 1;
    }

    if (cantidad_usuarios - 1 < maximoAmigos) {
        maximoAmigos = cantidad_usuarios - 1;
    }

    uniform_int_distribution<int> elegirCantidad(minimoAmigos, maximoAmigos);

    uniform_int_distribution<int> elegirUsuario(0, cantidad_usuarios - 1);

    for (int i = 0; i < cantidad_usuarios; i++) {

        int cantidadDeseada = elegirCantidad(generador);
        int cantidadActual = 0;

        for (int j = 0; j < cantidad_usuarios; j++) {
            if (amistades[i][j]) {
                cantidadActual++;
            }
        }

        int intentos = 0;
        int maxIntentos = cantidad_usuarios * 10;

        while (cantidadActual < cantidadDeseada
               && intentos < maxIntentos) {

            int amigo = elegirUsuario(generador);
            intentos++;

            if (amigo == i) {
                continue;
            }
            if (amistades[i][amigo]) {
                continue;
            }

            amistades[i][amigo] = true;
            amistades[amigo][i] = true;

            cantidadActual++;
        }
    }

    ofstream archivoAmistades("amistades.txt");

    if (!archivoAmistades.is_open()) {
        cout << "Error: no se pudo crear amistades.txt" << endl;

        for (int i = 0; i < cantidad_usuarios; i++) {
            delete[] amistades[i];
        }

        delete[] amistades;
        delete[] usuarios;
        return;
    }

    int totalAmistades = 0;

    for (int i = 0; i < cantidad_usuarios; i++) {
        for (int j = i + 1; j < cantidad_usuarios; j++) {

            if (amistades[i][j]) {
                archivoAmistades  << usuarios[i] << "|"<< usuarios[j] << "\n";
                totalAmistades++;
            }
        }
    }

    archivoAmistades.close();

    cout << "Usuarios leidos: " << cantidad_usuarios << endl;
    cout << "Amistades generadas: " << totalAmistades << endl;
    cout << "Archivo creado: amistades.txt\n";

    for (int i = 0; i < cantidad_usuarios; i++) {
        delete[] amistades[i];
    }

    delete[] amistades;
    delete[] usuarios;
}


