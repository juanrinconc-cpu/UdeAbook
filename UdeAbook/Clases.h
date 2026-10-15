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

#endif // CLASES_H
