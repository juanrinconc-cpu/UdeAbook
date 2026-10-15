#include "Usuarios.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <filesystem>
using namespace std;

void creacion_usuarios() {
    ofstream archivo("usuariosudeabook.txt");
    cout << "ruta del archivo " << filesystem::current_path() << endl;;
    try {
        if (archivo.fail()) {
            throw runtime_error("No se pudo crear el archivo usuarios.txt");
        }

        const char* name_users[] = {"Juan", "Sofia", "Paulina", "Jose", "Victor"};
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
            const char* names = name_users[rand() % 5];
            const char* naci  = fechanac[rand() % 5];

            archivo << names << i << ";"<< naci << ";"<< names << i << "@correoudebook.com;"<< citys << ";"<< "Colombia"<< endl;
            cout <<names << i << ";"<< naci << ";"<< names << "@correoudebook.com;"<< citys << ";"<< "Colombia"<< endl;

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
        cout << "Error desconocido durante la creación de usuarios." << endl;
    }
}
