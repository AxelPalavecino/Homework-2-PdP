#include <iomanip>
#include <iostream>
#include "reloj.h"
using namespace std;

// Implementación de funciones auxiliares
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
            cin.ignore(10000, '\n');  // Descarta la entrada incorrecta
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

// Constructor por defecto
Reloj::Reloj() : hora(12), minuto(0), segundo(0), pm(false) {}

// Constructor con solo hora
Reloj::Reloj(unsigned int h) : minuto(0), segundo(0), pm(false) {
    validarHora(h);
    hora = h;
}

// Constructor con hora y minutos
Reloj::Reloj(unsigned int h, unsigned int m) : segundo(0), pm(false) {
    validarHora(h);
    validarMinSeg(m);
    hora = h;
    minuto = m;
}

// Constructor con hora, minutos y segundos
Reloj::Reloj(unsigned int h, unsigned int m, unsigned int s) : pm(false) {
    validarHora(h);
    validarMinSeg(m);
    validarMinSeg(s);
    hora = h;
    minuto = m;
    segundo = s;
}

// Constructor completo
Reloj::Reloj(unsigned int h, unsigned int m, unsigned int s, bool es_pm) {
    validarHora(h);
    validarMinSeg(m);
    validarMinSeg(s);
    hora = h;
    minuto = m;
    segundo = s;
    pm = es_pm;
}

// Getters
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

// Setters
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

// Métodos para mostrar la hora
string Reloj::mostrarHora12() const {
    // Usamos stringstream para construir el string con formato
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

// Métodos privados de validación
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

