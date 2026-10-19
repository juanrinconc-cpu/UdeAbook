#ifndef CLASES_H
#define CLASES_H

class Fecha {
private:
    char* fecha_texto;   // fecha leída (ej: del archivo)
    char* fecha_actual;  // fecha actual del sistema
    char* hora_actual;   // hora actual del sistema

public:
    Fecha();                          // constructor
    ~Fecha();                         // destructor
    void setFechaTexto(const char* f);// asignar fecha leída
    const char* getFechaTexto() const;// devolver fecha leída
    const char* getFechaActual() const;// devolver fecha actual
    const char* getHoraActual() const;// devolver hora actual
};

class Usuario {
private:
    char nombre[60];
    char nacimiento[12];
    char correo[100];
    char ciudad[30];
    char pais[10];
    char fecha_registro[12];

    int num_amigos;
    Usuario** amigos;
    int total_amigos;

public:
    Usuario();
    ~Usuario();
    void asignar(const char* n, const char* nac, const char* c, const char* ciu, const char* p, const char* f);
    void mostrar();
    static void copiar_texto(char *destino,const char* origen,int max);
    const char* getNombre() const;
    const char* getNacimiento() const;
    const char* getCorreo() const;
    const char* getCiudad() const;
    const char* getPais() const;
    const char* getFecha_registro() const;
    static bool comparar_texto(const char* a, const char* b);
    bool es_amigo(const Usuario* u);
    bool agregar_amigo(Usuario* u);
    void mostrar_amigos();
};
#endif // CLASES_H
