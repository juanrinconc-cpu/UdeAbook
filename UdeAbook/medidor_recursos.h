#ifndef MEDIDOR_RECURSOS_H
#define MEDIDOR_RECURSOS_H
class MedidorRecursos {
private:
    static long long iteraciones;
public:
    static void reiniciar();
    static void sumar();
    static long long obtener();
};
#endif // MEDIDOR_RECURSOS_H
