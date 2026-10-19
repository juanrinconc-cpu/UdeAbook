#ifndef USUARIOS_H
#define USUARIOS_H

/* Nota: esta función crea 1000 registros de usuarios, este documento es de prueba y no es necesario ejecutarlo
 cada vez que se ejecuta el programa puesto que este se almacena en un archivo .txt */

void creacion_usuarios();
/* Nota: esta función crea amigos aleatorios, este documento es de prueba y no es necesario ejecutarlo
 cada vez que se ejecuta el programa puesto que este se almacena en un archivo .txt */
void generar_amistades();
void creacion_usuarios();
void generar_amistades();


class Usuario;

Usuario** cargarUsuarios(int& cantidad, long long& it);
Usuario* buscarUsuario(Usuario** usuarios, int cantidad, const char* nombre, long long& it);
#endif // USUARIOS_H
