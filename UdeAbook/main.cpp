#include "Clases.h"
#include <iostream>
using namespace std;


int main() {
    Plataforma p;
    p.cargarUsuarios("usuariosudeabook.txt");
    p.cargarAmigos("Amigos.txt");
    p.mostrarTodo();
    return 0;
}
