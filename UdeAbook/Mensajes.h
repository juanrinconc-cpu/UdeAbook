#ifndef MENSAJES_H
#define MENSAJES_H
class Mensaje{
private:
    char* emisor;
    char* receptor;
    char* mensaje_enviado;
    char* fecha_envio;
    bool leido;
public:
    Mensaje();
    Mensaje( const char* _e, const char* _r, const char* _m, const char* _f);
    ~Mensaje();
    static char* copiar_cadena(const char* origen);
    const char * getEmisor();
    const char* getReceptor();
    const char * getContenido();
    const char* getFechaEnvio();
    bool estaLeido();

    void setContenido(const char* c);
    void setFechaEnvio(const char* f);
    void marcarLeido();
    void mostrar();
};

#endif // MENSAJES_H
