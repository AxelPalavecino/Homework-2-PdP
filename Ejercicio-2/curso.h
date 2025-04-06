#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map> // Almacenar par clave-valor
#include <algorithm>

using namespace std;

// FUNCIONES Y DEFINICIONES ADICIONALES

// Enum para las opciones del menú
enum OpcionMenu {
    REGISTRAR_ESTUDIANTE = 1,
    CREAR_CURSO,
    INSCRIBIR_ESTUDIANTE,
    DESINSCRIBIR_ESTUDIANTE,
    VERIFICAR_INSCRIPCION,
    VERIFICAR_CURSO_COMPLETO,
    MOSTRAR_ESTUDIANTES,
    ASIGNAR_NOTA,
    COPIAR_CURSO,
    SALIR
};

/**
 * @brief Función para limpiar la pantalla (multiplataforma)
 */
void limpiarPantalla();

/**
 * @brief Función que gestiona la interacción del usuario con el sistema
 * @return Código de salida del programa
 */
int interaccion();

// CLASES SOLICITADAS

/**
 * @class Estudiante
 * @brief Representa a un estudiante con su información académica
 */
class Estudiante {
private:
    string nombreCompleto;
    int legajo;
    map<string, float> cursosNotas; // map es una estructura de datos que almacena pares clave-valor, 
                                    // donde la clave es el nombre del curso y el valor es la nota
                                    // del estudiante en ese curso, tal como un diccionario.

public:
    /**
     * @brief Constructor de la clase Estudiante
     * @param nombre Nombre completo del estudiante
     * @param leg Número de legajo único del estudiante
     */
    Estudiante(const string& nombre, int leg);

    /**
     * @brief Obtiene el nombre completo del estudiante
     * @return Nombre completo
     */
    string getNombre() const;

    /**
     * @brief Obtiene el legajo del estudiante
     * @return Número de legajo
     */
    int getLegajo() const;

    /**
     * @brief Agrega un curso con su nota al historial del estudiante
     * @param nombreCurso Nombre del curso
     * @param nota Calificación final
     */
    void agregarCursoNota(const string& nombreCurso, float nota);

    /**
     * @brief Calcula el promedio general del estudiante
     * @return Promedio de todas las notas
     */
    float calcularPromedio() const;
};


/**
 * @class Curso
 * @brief Gestiona un curso y sus estudiantes
 */
class Curso {
        
    private:
        string nombre;
        vector<Estudiante*> estudiantes;
        const int capacidadMaxima = 20;

public:
    /**
     * @brief Constructor de la clase Curso
     * @param nombreCurso Nombre del curso
     */
    Curso(const string& nombreCurso);

    /**
     * @brief Constructor de copia para la clase Curso
     * @param otro Curso a copiar
     */
    Curso(const Curso& otro);

    /**
     * @brief Destructor de la clase Curso
     */
    ~Curso();

    /**
     * @brief Inscribe un estudiante al curso
     * @param estudiante Puntero al estudiante a inscribir
     * @return true si la inscripción fue exitosa, false en caso contrario
     */
    bool inscribirEstudiante(Estudiante* estudiante);

    /**
     * @brief Desinscribe un estudiante del curso por su legajo
     * @param legajo Legajo del estudiante a desinscribir
     * @return true si la desinscripción fue exitosa, false en caso contrario
     */
    bool desinscribirEstudiante(int legajo);

    /**
     * @brief Verifica si un estudiante está inscrito en el curso
     * @param legajo Legajo del estudiante a verificar
     * @return true si el estudiante está inscrito, false en caso contrario
     */
    bool estaInscrito(int legajo) const;

    /**
     * @brief Verifica si el curso está completo
     * @return true si el curso alcanzó su capacidad máxima, false en caso contrario
     */
    bool estaCompleto() const;

    /**
     * @brief Obtiene el nombre del curso
     * @return Nombre del curso
     */
    string getNombre() const;

    // Declaración de la función friend
    friend ostream& operator<<(ostream& os, const Curso& curso);
};

/**
 * @brief Sobrecarga del operador de inserción para imprimir la lista de estudiantes
 * @param os Stream de salida
 * @param curso Curso cuyos estudiantes se imprimirán
 * @return Referencia al stream modificado
 */
ostream& operator<<(ostream& os, const Curso& curso); 