#include <iostream>
#include "numeros.h"

// Declaraciones de funciones de prueba definidas en numeros.cpp
void ejecutarPruebas();

int main() {
    try {
        std::cout << "========================================" << std::endl;
        std::cout << "INICIANDO PRUEBAS DE OPERACIONES CON NÚMEROS" << std::endl;
        std::cout << "========================================" << std::endl;
        
        ejecutarPruebas();
        
        std::cout << "========================================" << std::endl;
        std::cout << "Todas las pruebas completadas." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error no capturado: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido no capturado" << std::endl;
    }
    
    return 0;
}
