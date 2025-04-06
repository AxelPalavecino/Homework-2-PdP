#include <iomanip>
#include <iostream>
#include "reloj.h"
using namespace std;

// FUNCIONES AUXILIARES (son utilizadas para interactuar con el usuario y no son parte de la clase Reloj)

unsigned int obtenerValorEntero(const string& mensaje, unsigned int min, unsigned int max) {
    unsigned int valor;
    bool valido = false;
    
    do {
        cout << mensaje;
        if (cin >> valor) {
            if (valor >= min && valor <= max) {
                valido = true;
            } else {
                cout << "Error: El valor debe estar entre " << min << " y " << max << endl;
            }
        } else {
            cout << "Error: Ingrese un número entero válido" << endl;
            cin.clear();  // Limpia el estado de error
            cin.ignore(10000, '\n');  // Descarta la entrada incorrecta, el numero 10000 significa que se descartan hasta 10000 caracteres para evitar un bucle infinito
        }
    } while (!valido);
    
    return valor;
}

bool obtenerRespuestaSiNo(const string& mensaje) {
    char respuesta;
    bool valido = false;
    
    do {
        cout << mensaje << " (s/n): ";
        cin >> respuesta;
        
        respuesta = tolower(respuesta);
        if (respuesta == 's' || respuesta == 'n') {
            valido = true;
        } else {
            cout << "Error: Responda con 's' o 'n'" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (!valido);
    
    return (respuesta == 's');
}

// CLASE Reloj

// CONSTRUCTORES

// CONSTRUCTOR por defecto

Reloj::Reloj() : hora(12), minuto(0), segundo(0), pm(false) {}

// CONSTRUCTOR con solo hora
Reloj::Reloj(unsigned int h) : minuto(0), segundo(0), pm(false) {
    validarHora(h);
    hora = h;
}

// CONSTRUCTOR con hora y minutos
Reloj::Reloj(unsigned int h, unsigned int m) : segundo(0), pm(false) {
    validarHora(h);
    validarMinSeg(m);
    hora = h;
    minuto = m;
}

// CONSTRUCTOR con hora, minutos y segundos
Reloj::Reloj(unsigned int h, unsigned int m, unsigned int s) : pm(false) {
    validarHora(h);
    validarMinSeg(m);
    validarMinSeg(s);
    hora = h;
    minuto = m;
    segundo = s;
}

// CONSTRUCTOR completo
Reloj::Reloj(unsigned int h, unsigned int m, unsigned int s, bool es_pm) {
    validarHora(h);
    validarMinSeg(m);
    validarMinSeg(s);
    hora = h;
    minuto = m;
    segundo = s;
    pm = es_pm;
}

// GETTERS

unsigned int Reloj::getHora() const {
    return hora;
}

unsigned int Reloj::getMinuto() const {
    return minuto;
}

unsigned int Reloj::getSegundo() const {
    return segundo;
}

bool Reloj::esPM() const {
    return pm;
}

// SETTERS

bool Reloj::setHora(unsigned int h) {
    bool esValido = validarHora(h);
    hora = h;
    return esValido;
}

bool Reloj::setMinuto(unsigned int m) {
    bool esValido = validarMinSeg(m);
    minuto = m;
    return esValido;
}

bool Reloj::setSegundo(unsigned int s) {
    bool esValido = validarMinSeg(s);
    segundo = s;
    return esValido;
}

void Reloj::setPM(bool es_pm) {
    pm = es_pm;
}

// MÉTODOS PARA MOSTRAR LA HORA

string Reloj::mostrarHora12() const {

    // Stringstream me permite tratar strings como flujos de datos, en este caso, para formatear la hora. Si utilizo string en vez de stringstream, no puedo formatear la hora.
    stringstream ss;
    // setw(2) para que tenga 2 dígitos, setfill('0') para llenar con ceros a la izquierda
    ss << setw(2) << setfill('0') << hora << "h, "
       << setw(2) << setfill('0') << minuto << "m, "
       << setw(2) << setfill('0') << segundo << "s ";
    
    // Agregamos a.m. o p.m. según corresponda
    if (pm) {
        ss << "p.m.";
    } else {
        ss << "a.m.";
    }
    
    return ss.str();
}

string Reloj::mostrarHora24() const {
    // Calculamos la hora en formato 24h
    unsigned int hora24 = hora;
    if (pm && hora != 12) {
        hora24 += 12;  // Si es PM y no es 12, sumamos 12
    } else if (!pm && hora == 12) {
        hora24 = 0;    // Si es AM y es 12, corresponde a 00
    }
    
    // Formateamos la hora
    stringstream ss;
    ss << setw(2) << setfill('0') << hora24 << ":"
       << setw(2) << setfill('0') << minuto << ":"
       << setw(2) << setfill('0') << segundo;
       
    return ss.str();
}

void Reloj::imprimirHora24() const {
    cout << "Hora en formato 24h: " << mostrarHora24() << endl;
}

// METODOS PRIVADOS (son privados, ya que al usuario no le interesa saber cómo funcionan, solo que funcionan)

bool Reloj::validarHora(unsigned int &h) {
    bool esValido = true;
    
    // La hora debe estar entre 1 y 12
    if (h < 1) {
        h = 1;
        esValido = false;
    } else if (h > 12) {
        h = 12;
        esValido = false;
    }
    
    return esValido;
}

bool Reloj::validarMinSeg(unsigned int &valor) {
    bool esValido = true;
    
    // Los minutos y segundos deben estar entre 0 y 59
    if (valor > 59) {
        valor = 59;
        esValido = false;
    }
    
    return esValido;
}

// Nueva función de interacción con el usuario
void interaccion() {
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
}