#include "Clases.h"
#include <iostream>
#include <ctime>
#include <cstring>
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

Usuario::Usuario(): num_amigos(0),amigos(nullptr), total_amigos(0){
    nombre[0]='\0';
    nacimiento[0]='\0';
    correo[0]='\0';
    ciudad[0]='\0';
    pais[0]='\0';
    fecha_registro[0]='\0';

}
Usuario::~Usuario(){
    delete[]amigos;
}

void Usuario::copiar_texto(char *destino,const char* origen,int max){
    int i=0;
    while (origen[i] != '\0' && i < max-1) {
        destino[i]=origen[i];
        i=i+1;
    }
    destino[i]='\0';
}
void Usuario::asignar(const char* n, const char* nac, const char* c, const char* ciu, const char* p, const char* f){
    copiar_texto(nombre, n, 60);
    copiar_texto(nacimiento,nac,12);
    copiar_texto(correo,c,100);
    copiar_texto(ciudad,ciu,30);
    copiar_texto(pais,p,10);
    copiar_texto(fecha_registro,f,12);
}
void Usuario::mostrar(){
    cout << "Usuario: " << nombre << endl;
    cout << "Nacimiento: " << nombre << endl;
    cout << "Correo: " << correo << endl;
    cout << "Pais: " << pais << endl;
    cout << "Unidos desde: " << fecha_registro << endl;
}
const char* Usuario:: getNombre() const {
    return nombre; }
const char* Usuario:: getNacimiento() const {
    return nacimiento; }
const char* Usuario::getCorreo() const {
    return correo; }
const char* Usuario::getCiudad() const {
    return ciudad; }
const char* Usuario::getPais() const {
    return pais; }
const char* Usuario::getFecha_registro() const {
    return fecha_registro; }
int Usuario::getNumAmigos()const{
    return num_amigos;
}
bool Usuario::es_amigo(const Usuario* u){
    for(int i=0; i< num_amigos;i++){
        if(amigos[i]==u){
            return true;
        }
    }
    return false;
}
bool Usuario::agregar_amigo(Usuario* u){
    if (u== this || es_amigo(u)){
        return false;
    }
    if (num_amigos==total_amigos){
        int capacidad;
        if (total_amigos==0){
            capacidad=4;
        }
        else{
            capacidad=total_amigos*2;
        }
        Usuario** capacidad_nueva=new Usuario*[capacidad];
        for(int j=0;j<num_amigos;j++){
            capacidad_nueva[j]=amigos[j];
        }
        delete[]amigos;
        amigos=capacidad_nueva;
        total_amigos=capacidad;
    }
    amigos[num_amigos++]=u;
    return true;
}
void Usuario::mostrar_amigos(){
    cout << "Amigos de " << nombre << ":";
    for (int i = 0; i < num_amigos; ++i) {
        cout << amigos[i]->getNombre() << endl;

    }
}

Usuario** cargarUsuarios(int& cantidad, long long& it) {
    cantidad = 0;
    ifstream archivo("usuariosudeabook.txt");
    if (!archivo.is_open()) return nullptr;

    Usuario** lista = new Usuario*[1000];
    char linea[256];

    while (cantidad < 1000 && archivo.getline(linea, sizeof(linea))) {
        ++it;
        if (strlen(linea) == 0) continue;

        char* campos[6];
        int n = 0;
        char* tok = strtok(linea, "|");
        while (tok && n < 6) {
            campos[n++] = tok;
            tok = strtok(nullptr, "|");
        }
        if (n != 6) continue;

        Usuario* u = new Usuario();
        u->asignar(campos[0], campos[1], campos[2], campos[3], campos[4], campos[5]);
        lista[cantidad++] = u;
    }
    archivo.close();
    return lista;
}

Usuario* buscarUsuario(Usuario** usuarios, int cantidad, const char* nombre, long long& it) {
    for (int i = 0; i < cantidad; i++) {
        it=it+1;
        if (strcmp(usuarios[i]->getNombre(), nombre) == 0) {
            return usuarios[i];
        }
    }
    return nullptr;
}

