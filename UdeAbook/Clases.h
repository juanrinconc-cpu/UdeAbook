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
    char correo[60];
    Usuario** amigos;
    int num_amigos;
    int capacidad;

    // Funciones auxiliares propias
    static void copiarTexto(char* destino, const char* origen, int max);
    static bool compararTexto(const char* a, const char* b);

public:
    Usuario(const char* c);
    Usuario(const Usuario&) = delete;
    Usuario& operator=(const Usuario&) = delete;
    ~Usuario();

    const char* getCorreo() const;
    bool esAmigoDe(const Usuario* u) const;
    bool agregarAmigo(Usuario* u);
    void mostrarAmigos() const;

    // Para que Plataforma pueda usar compararTexto
    friend class Plataforma;
};
class Plataforma {
private:
    Usuario** usuarios;
    int totalUsuarios;

public:
    Plataforma();
    ~Plataforma();

    void cargarUsuarios(const char* archivo);
    void cargarAmigos(const char* archivo);
    Usuario* buscarPorCorreo(const char* correo);
    void mostrarTodo();
};
#endif // CLASES_H
