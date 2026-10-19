#ifndef ALBUM_H
#define ALBUM_H
#include "Fotos.h"

class Album {
private:
    char* nombre;
    char* ruta;
    char* privacidad;
    foto** fotos;
    int num_fotos;
    int capacidad_fotos;

    static char* copiarCadena(const char* origen);

public:
    Album();
    Album(const char* n, const char* r, const char* p);
    ~Album();

    bool agregar_foto(foto* foto);
    void mostrar_fotos();

    const char* getNombre() const;
    const char* getRuta() const;
    const char* getPrivacidad() const;
    int getNumFotos() const;
    int getCapacidadFotos() const;

    void setNombre(const char* n);
    void setRuta(const char* r);
    void setPrivacidad(const char* p);

    foto* getFoto(int indice) const;
    void darLikeFoto(int indice);
    void quitarLikeFoto(int indice);
};
#endif // ALBUM_H
