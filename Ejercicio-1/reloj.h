#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

// Enum para las opciones del menú principal
enum OpcionMenu {
    CREAR_SIN_PARAMETROS = 1,
    CREAR_CON_HORA,
    CREAR_CON_HORA_Y_MINUTOS,
    CREAR_CON_HORA_MINUTOS_Y_SEGUNDOS,
    CREAR_COMPLETO,
    MODIFICAR_HORA,
    MODIFICAR_MINUTOS,
    MODIFICAR_SEGUNDOS,
    CAMBIAR_AM_PM,
    SALIR
};

// Funciones auxiliares para la interfaz de usuario
/**
 * Obtiene un valor entero validado del usuario
 * @param mensaje Mensaje a mostrar al usuario
 * @param min Valor mínimo permitido
 * @param max Valor máximo permitido
 * @return Valor entero validado
 */
unsigned int obtenerValorEntero(const string& mensaje, unsigned int min, unsigned int max);

/**
 * Obtiene una respuesta de tipo sí/no del usuario
 * @param mensaje Mensaje a mostrar al usuario
 * @return true si la respuesta es 'sí', false si es 'no'
 */
bool obtenerRespuestaSiNo(const string& mensaje);

/**
 * Función principal de interacción con el usuario
 * Muestra el menú y gestiona las operaciones con un reloj
 */
void interaccion();

class Reloj {
    // Atributos privados
    private:
        unsigned int hora; // El unsigned int es para que no se pueda ingresar un valor negativo
        unsigned int minuto;
        unsigned int segundo;
        bool pm; // PM = True, AM = False

    public:
        // Métodos públicos

        /**
         * Constructor por defecto
         * Inicializa el reloj a 0h, 0m, 0s a.m.
         */
        Reloj();

        /**
         * Constructor con parámetro de hora
         * @param h Hora (1-12)
         * Inicializa el reloj a hh, 0m, 0s a.m.
         * Si la hora está fuera de rango, se establece por defecto a 12
         */
        Reloj(unsigned int h);

        /**
         * Constructor con parámetros de hora y minutos
         * @param h Hora (1-12)
         * @param m Minutos (0-59)
         * Inicializa el reloj a hh, mm, 0s a.m.
         * Si algún valor está fuera de rango, se ajusta al límite correspondiente
         */
        Reloj(unsigned int h, unsigned int m);

        /**
         * Constructor con parámetros de hora, minutos y segundos
         * @param h Hora (1-12)
         * @param m Minutos (0-59)
         * @param s Segundos (0-59)
         * Inicializa el reloj a hh, mm, ss a.m.
         * Si algún valor está fuera de rango, se ajusta al límite correspondiente
         */
        Reloj(unsigned int h, unsigned int m, unsigned int s);

        /**
         * Constructor completo
         * @param h Hora (1-12)
         * @param m Minutos (0-59)
         * @param s Segundos (0-59)
         * @param es_pm true si es p.m., false si es a.m.
         * Inicializa el reloj a hh, mm, ss a.m./p.m.
         * Si algún valor está fuera de rango, se ajusta al límite correspondiente
         */
        Reloj(unsigned int h, unsigned int m, unsigned int s, bool es_pm);

        // Métodos para obtener valores (getters)
        
        /**
         * Obtiene la hora actual del reloj (1-12)
         * @return Valor de la hora
         */
        unsigned int getHora() const;
        
        /**
         * Obtiene los minutos actuales del reloj (0-59)
         * @return Valor de los minutos
         */
        unsigned int getMinuto() const;
        
        /**
         * Obtiene los segundos actuales del reloj (0-59)
         * @return Valor de los segundos
         */
        unsigned int getSegundo() const;
        
        /**
         * Obtiene si la hora es PM o AM
         * @return true si es p.m., false si es a.m.
         */
        bool esPM() const;

        // Métodos para establecer valores (setters)
        
        /**
         * Establece la hora del reloj
         * @param h Hora (1-12)
         * @return true si el valor es válido, false si se ajustó
         */
        bool setHora(unsigned int h);
        
        /**
         * Establece los minutos del reloj
         * @param m Minutos (0-59)
         * @return true si el valor es válido, false si se ajustó
         */
        bool setMinuto(unsigned int m);
        
        /**
         * Establece los segundos del reloj
         * @param s Segundos (0-59)
         * @return true si el valor es válido, false si se ajustó
         */
        bool setSegundo(unsigned int s);
        
        /**
         * Establece si la hora es PM o AM
         * @param es_pm true si es p.m., false si es a.m.
         */
        void setPM(bool es_pm);

        /**
         * Muestra la hora en formato 12h (HHh, MMm, SSs a.m./p.m.)
         * @return String con la hora formateada
         */
        string mostrarHora12() const;

        /**
         * Muestra la hora en formato 24h (HH:MM:SS)
         * @return String con la hora formateada en sistema de 24 horas
         */
        string mostrarHora24() const;

        /**
         * Imprime en pantalla la hora en formato 24h
         */
        void imprimirHora24() const;

    private:
        /**
         * Valida y corrige el valor de la hora (1-12)
         * @param h Referencia al valor de hora a validar
         * @return true si el valor era válido, false si se ajustó
         */
        bool validarHora(unsigned int &h);
        
        /**
         * Valida y corrige el valor de minutos/segundos (0-59)
         * @param valor Referencia al valor a validar
         * @return true si el valor era válido, false si se ajustó
         */
        bool validarMinSeg(unsigned int &valor);
};