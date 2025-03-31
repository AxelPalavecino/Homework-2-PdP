#include <iostream>
#include "reloj.h"

using namespace std;

int main() {
    int opcionInt;
    OpcionMenu opcion;
    bool continuar = true;
    
    Reloj miReloj;
    
    cout << "=== Programa de prueba de la clase Reloj ===" << endl;
    
    while (continuar) {
        cout << "\nReloj actual: " << miReloj.mostrarHora12() << endl;
        cout << "En formato 24h: " << miReloj.mostrarHora24() << endl;
        
        cout << "\nSeleccione una opción:" << endl;
        cout << "1. Crear un reloj sin parámetros" << endl;
        cout << "2. Crear un reloj con hora" << endl;
        cout << "3. Crear un reloj con hora y minutos" << endl;
        cout << "4. Crear un reloj con hora, minutos y segundos" << endl;
        cout << "5. Crear un reloj completo (hora, minutos, segundos, am/pm)" << endl;
        cout << "6. Modificar hora" << endl;
        cout << "7. Modificar minutos" << endl;
        cout << "8. Modificar segundos" << endl;
        cout << "9. Cambiar entre AM/PM" << endl;
        cout << "10. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcionInt;
        
        if (opcionInt >= CREAR_SIN_PARAMETROS && opcionInt <= SALIR) {
            opcion = static_cast<OpcionMenu>(opcionInt);
        } else {
            cout << "Opción no válida. Por favor, intente nuevamente." << endl;
            continue;
        }
        
        switch (opcion) {
            case CREAR_SIN_PARAMETROS: {
                miReloj = Reloj();
                cout << "Reloj creado con valores por defecto: " << miReloj.mostrarHora12() << endl;
                break;
            }
            case CREAR_CON_HORA: {
                unsigned int h = obtenerValorEntero("Ingrese la hora (1-12): ", 1, 12);
                miReloj = Reloj(h);
                cout << "Reloj creado: " << miReloj.mostrarHora12() << endl;
                break;
            }
            case CREAR_CON_HORA_Y_MINUTOS: {
                unsigned int h = obtenerValorEntero("Ingrese la hora (1-12): ", 1, 12);
                unsigned int m = obtenerValorEntero("Ingrese los minutos (0-59): ", 0, 59);
                miReloj = Reloj(h, m);
                cout << "Reloj creado: " << miReloj.mostrarHora12() << endl;
                break;
            }
            case CREAR_CON_HORA_MINUTOS_Y_SEGUNDOS: {
                unsigned int h = obtenerValorEntero("Ingrese la hora (1-12): ", 1, 12);
                unsigned int m = obtenerValorEntero("Ingrese los minutos (0-59): ", 0, 59);
                unsigned int s = obtenerValorEntero("Ingrese los segundos (0-59): ", 0, 59);
                miReloj = Reloj(h, m, s);
                cout << "Reloj creado: " << miReloj.mostrarHora12() << endl;
                break;
            }
            case CREAR_COMPLETO: {
                unsigned int h = obtenerValorEntero("Ingrese la hora (1-12): ", 1, 12);
                unsigned int m = obtenerValorEntero("Ingrese los minutos (0-59): ", 0, 59);
                unsigned int s = obtenerValorEntero("Ingrese los segundos (0-59): ", 0, 59);
                bool es_pm = obtenerRespuestaSiNo("¿Es PM?");
                miReloj = Reloj(h, m, s, es_pm);
                cout << "Reloj creado: " << miReloj.mostrarHora12() << endl;
                break;
            }
            case MODIFICAR_HORA: {
                unsigned int h = obtenerValorEntero("Ingrese la nueva hora (1-12): ", 1, 12);
                if (!miReloj.setHora(h)) {
                    cout << "La hora ingresada fue ajustada a un valor válido" << endl;
                }
                cout << "Reloj actualizado: " << miReloj.mostrarHora12() << endl;
                break;
            }
            case MODIFICAR_MINUTOS: {
                unsigned int m = obtenerValorEntero("Ingrese los nuevos minutos (0-59): ", 0, 59);
                if (!miReloj.setMinuto(m)) {
                    cout << "Los minutos ingresados fueron ajustados a un valor válido" << endl;
                }
                cout << "Reloj actualizado: " << miReloj.mostrarHora12() << endl;
                break;
            }
            case MODIFICAR_SEGUNDOS: {
                unsigned int s = obtenerValorEntero("Ingrese los nuevos segundos (0-59): ", 0, 59);
                if (!miReloj.setSegundo(s)) {
                    cout << "Los segundos ingresados fueron ajustados a un valor válido" << endl;
                }
                cout << "Reloj actualizado: " << miReloj.mostrarHora12() << endl;
                break;
            }
            case CAMBIAR_AM_PM: {
                bool actual = miReloj.esPM();
                cout << "Actualmente el reloj está en " << (actual ? "PM" : "AM") << endl;
                miReloj.setPM(!actual);
                cout << "Ahora el reloj está en " << (!actual ? "PM" : "AM") << endl;
                cout << "Reloj actualizado: " << miReloj.mostrarHora12() << endl;
                break;
            }
            case SALIR: {
                continuar = false;
                cout << "Programa finalizado. ¡Adiós!" << endl;
                break;
            }
        }
    }
    
    return 0;
}
