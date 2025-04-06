#include <iostream>
#include <vector>
#include <string>
#include "curso.h"

using namespace std;

// Función para limpiar la pantalla (multiplataforma)
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    return interaccion();
}
