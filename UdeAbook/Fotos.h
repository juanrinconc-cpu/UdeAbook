#ifndef FOTOS_H
#define FOTOS_H
class foto{
private:
    char* fecha_captura;
    char* ruta;
    long long tamanio;
    int likes;
    static char * copiarCadena(const char* origen);
public:
    foto();
    foto(const char* fecha, const char* r, long long t);
    ~foto();
    const char* getFechaCaptura() const;
    const char* getRuta()const;
    long long getTamanio()const;
    int getLikes()const;
    void setFechaCaptura(const char* fecha);
    void setRuta(const char* r);
    void setTamano(long long t);
    void darLike();
    void quitarLike();
    void mostrar()const;
};

#endif // FOTOS_H
