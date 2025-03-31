#include "curso.h"

// Implementación de la clase Estudiante
Estudiante::Estudiante(const string& nombre, int leg) : nombreCompleto(nombre), legajo(leg) {}

string Estudiante::getNombre() const {
    return nombreCompleto;
}

int Estudiante::getLegajo() const {
    return legajo;
}

void Estudiante::agregarCursoNota(const string& nombreCurso, float nota) {
    cursosNotas[nombreCurso] = nota;
}

float Estudiante::calcularPromedio() const {
    if (cursosNotas.empty()) {
        return 0.0f;
    }

    float sumaNotas = 0.0f;
    for (const auto& par : cursosNotas) {
        sumaNotas += par.second; // .second toma la nota (nuestros map almacena pares clave-valor, por lo que .first es el nombre del curso y .second es la nota)
    }
    
    return sumaNotas / cursosNotas.size();
}

// Implementación de la clase Curso
Curso::Curso(const string& nombreCurso) : nombre(nombreCurso) {}

Curso::Curso(const Curso& otro) : nombre(otro.nombre) {
    /* 
     * Se realiza una copia superficial (shallow copy) de los punteros a estudiantes.
     * Esto es apropiado porque los estudiantes son entidades que existen
     * independientemente de los cursos y pueden pertenecer a múltiples cursos.
     * No queremos duplicar los objetos estudiante, solo las referencias a ellos.
     */
    for (int i = 0; i < otro.estudiantes.size(); i++) {
        estudiantes.push_back(otro.estudiantes[i]);
    }

    /*
    - No se necesita copiar la capacidad máxima, ya que es constante y se puede obtener directamente de la clase.

    - No se necesita copiar la lista de estudiantes, ya que se hace una copia superficial de los punteros a estudiantes. Esto es apropiado porque los estudiantes son entidades que existen independientemente de los cursos y pueden pertenecer a múltiples cursos.

    - No queremos duplicar los objetos estudiante, solo las referencias a ellos.
    */
}

Curso::~Curso() {
    // No liberamos la memoria de los estudiantes ya que son gestionados externamente
    // Solo limpiamos el vector
    estudiantes.clear();
}

bool Curso::inscribirEstudiante(Estudiante* estudiante) {
    // Verificar si el curso está completo
    if (estaCompleto()) {
        return false;
    }
    
    // Verificar si el estudiante ya está inscrito
    if (estaInscrito(estudiante->getLegajo())) {
        return false;
    }
    
    // Inscribir al estudiante
    estudiantes.push_back(estudiante);
    return true;
}

bool Curso::desinscribirEstudiante(int legajo) {
    for (auto it = estudiantes.begin(); it != estudiantes.end(); ++it) {
        /* 
        Estoy iterandorando sobre el vector estudiantes, begin devuelve un iterador al primer elemento del vector y end devuelve un iterador al final del vector.
        El iterador it se usa para recorrer el vector y eliminar el estudiante que coincide con el legajo proporcionado.
        Puedo utilizar ++it para avanzar al siguiente elemento del vector.
        */

        if ((*it)->getLegajo() == legajo) {
            estudiantes.erase(it);
            return true;
        }
    }
    return false;
}

bool Curso::estaInscrito(int legajo) const {
    for (const auto& estudiante : estudiantes) {
        if (estudiante->getLegajo() == legajo) {
            return true;
        }
    }
    return false;
}

bool Curso::estaCompleto() const {
    return estudiantes.size() >= capacidadMaxima;
}

string Curso::getNombre() const {
    return nombre;
}

// Sobrecarga del operador de inserción (<<)
ostream& operator<<(ostream& os, const Curso& curso) {
    vector<Estudiante*> estudiantesOrdenados = curso.estudiantes;
    
    // Ordenar estudiantes alfabéticamente por nombre
    sort(estudiantesOrdenados.begin(), estudiantesOrdenados.end(), [](Estudiante* a, Estudiante* b) {
        return a->getNombre() < b->getNombre();
    });

    os << "Curso: " << curso.getNombre() << endl;
    os << "Lista de estudiantes (orden alfabético):" << endl;
    
    for (const auto& estudiante : estudiantesOrdenados) {
        os << "- Legajo: " << estudiante->getLegajo() 
           << ", Nombre: " << estudiante->getNombre()
           << ", Promedio: " << estudiante->calcularPromedio() << endl;
    }
    
    return os;
}

/*

La relación que existe entre los objetos curso y estudiante es de asociación, ya que estas dos clases estan relacionadas entre sí, pero no tienen una relación de propiedad.
Un curso puede tener múltiples estudiantes inscritos, y un estudiante puede estar inscrito en múltiples cursos. Por lo tanto, la relación es de tipo "muchos a muchos".
En este caso, la clase Curso tiene un vector de punteros a objetos Estudiante, lo que indica que un curso puede contener múltiples estudiantes. Sin embargo, los objetos Estudiante no son creados ni destruidos por la clase Curso, lo que refuerza la idea de que la relación es de asociación y no de composición.
La clase Curso no es responsable de la creación o destrucción de los objetos Estudiante, lo que significa que la relación es más débil que una relación de composición. En una relación de composición, la clase contenedora (en este caso, Curso) sería responsable de la vida útil de los objetos contenidos (Estudiante), lo que no es el caso aquí.

En resumen, la relación entre Curso y Estudiante es una asociación, donde Curso tiene un vector de punteros a Estudiante, permitiendo que un estudiante esté inscrito en múltiples cursos y un curso tenga múltiples estudiantes. 
La relación es de tipo "muchos a muchos", y la clase Curso no es responsable de la creación o destrucción de los objetos Estudiante, lo que refuerza la idea de que la relación es de asociación y no de composición.

*/