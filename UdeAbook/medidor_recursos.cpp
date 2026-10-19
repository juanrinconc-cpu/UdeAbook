#include "medidor_recursos.h"

long long MedidorRecursos::iteraciones = 0;
void MedidorRecursos::reiniciar(){
    iteraciones=0;
}
void MedidorRecursos::sumar(){
    iteraciones=iteraciones+1;
}
long long MedidorRecursos::obtener(){
    return iteraciones;
}