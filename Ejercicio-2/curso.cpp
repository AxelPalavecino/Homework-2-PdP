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
     * Por lo tanto, se copian los punteros a los estudiantes del otro curso. Esto es Shallow Copy ya que 
     * no se copian los objetos Estudiante, solo los punteros a ellos.
     * Esto significa que ambos cursos compartirán los mismos objetos Estudiante. 
     */
    for (size_t i = 0; i < otro.estudiantes.size(); i++) {
        estudiantes.push_back(otro.estudiantes[i]);
    }
    // No se necesita copiar la capacidad máxima, ya que es constante
    // y se puede obtener directamente de la clase.
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
    return estudiantes.size() >= static_cast<size_t>(capacidadMaxima);
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

// Función para limpiar la pantalla (multiplataforma)
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int interaccion() {
    vector<Estudiante*> estudiantesRegistrados;
    vector<Curso*> cursosDisponibles;

    // Crear algunos cursos iniciales
    cursosDisponibles.push_back(new Curso("Programacion"));
    cursosDisponibles.push_back(new Curso("Matematicas"));
    cursosDisponibles.push_back(new Curso("Fisica"));

    int opcionInt = 0;
    while (true) {
        cout << "\n===== SISTEMA DE GESTIÓN DE CURSOS =====\n";
        cout << "1. Registrar nuevo estudiante\n";
        cout << "2. Crear nuevo curso\n";
        cout << "3. Inscribir estudiante a curso\n";
        cout << "4. Desinscribir estudiante de curso\n";
        cout << "5. Verificar si un estudiante está inscrito\n";
        cout << "6. Verificar si un curso está completo\n";
        cout << "7. Mostrar lista de estudiantes de un curso\n";
        cout << "8. Asignar nota a estudiante en un curso\n";
        cout << "9. Crear copia de un curso\n";
        cout << "10. Salir\n";
        cout << "Ingrese su opción: ";
        cin >> opcionInt;

        limpiarPantalla();
        
        // Convertir el entero a enum para mayor legibilidad
        OpcionMenu opcion = static_cast<OpcionMenu>(opcionInt);

        switch (opcion) {
            case REGISTRAR_ESTUDIANTE: {
                // Registrar nuevo estudiante
                string nombre;
                int legajo;
                
                cout << "===== REGISTRAR NUEVO ESTUDIANTE =====\n";
                cout << "Ingrese nombre completo: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese número de legajo: ";
                cin >> legajo;
                
                // Verificar si el legajo ya existe
                bool legajoExiste = false;
                for (const auto& est : estudiantesRegistrados) {
                    if (est->getLegajo() == legajo) {
                        legajoExiste = true;
                        break;
                    }
                }
                
                if (legajoExiste) {
                    cout << "Error: Ya existe un estudiante con ese legajo.\n";
                } else {
                    estudiantesRegistrados.push_back(new Estudiante(nombre, legajo));
                    cout << "Estudiante registrado correctamente.\n";
                }
                break;
            }
            case CREAR_CURSO: {
                // Crear nuevo curso
                string nombreCurso;
                
                cout << "===== CREAR NUEVO CURSO =====\n";
                cout << "Ingrese nombre del curso: ";
                cin.ignore();
                getline(cin, nombreCurso);
                
                cursosDisponibles.push_back(new Curso(nombreCurso));
                cout << "Curso creado correctamente.\n";
                break;
            }
            case INSCRIBIR_ESTUDIANTE: {
                // Inscribir estudiante a curso
                int legajo, indiceCurso;
                
                cout << "===== INSCRIBIR ESTUDIANTE A CURSO =====\n";
                
                // Mostrar lista de cursos
                cout << "Cursos disponibles:\n";
                for (size_t i = 0; i < cursosDisponibles.size(); i++) {
                    cout << i + 1 << ". " << cursosDisponibles[i]->getNombre() << endl;
                }
                
                cout << "Seleccione un curso (1-" << cursosDisponibles.size() << "): ";
                cin >> indiceCurso;
                
                if (indiceCurso < 1 || indiceCurso > static_cast<int>(cursosDisponibles.size())) {
                    cout << "Opción inválida.\n";
                    break;
                }
                
                cout << "Ingrese legajo del estudiante: ";
                cin >> legajo;
                
                // Buscar estudiante por legajo
                Estudiante* estudianteEncontrado = nullptr;
                for (auto est : estudiantesRegistrados) {
                    if (est->getLegajo() == legajo) {
                        estudianteEncontrado = est;
                        break;
                    }
                }
                
                if (estudianteEncontrado == nullptr) {
                    cout << "Error: No existe un estudiante con ese legajo.\n";
                } else {
                    bool inscripcionExitosa = cursosDisponibles[indiceCurso - 1]->inscribirEstudiante(estudianteEncontrado);
                    if (inscripcionExitosa) {
                        cout << "Estudiante inscrito correctamente.\n";
                    } else {
                        cout << "Error: No se pudo inscribir al estudiante (curso completo o ya inscrito).\n";
                    }
                }
                break;
            }
            case DESINSCRIBIR_ESTUDIANTE: {
                // Desinscribir estudiante de curso
                int legajo, indiceCurso;
                
                cout << "===== DESINSCRIBIR ESTUDIANTE DE CURSO =====\n";
                
                // Mostrar lista de cursos
                cout << "Cursos disponibles:\n";
                for (size_t i = 0; i < cursosDisponibles.size(); i++) {
                    cout << i + 1 << ". " << cursosDisponibles[i]->getNombre() << endl;
                }
                
                cout << "Seleccione un curso (1-" << cursosDisponibles.size() << "): ";
                cin >> indiceCurso;
                
                if (indiceCurso < 1 || indiceCurso > static_cast<int>(cursosDisponibles.size())) {
                    cout << "Opción inválida.\n";
                    break;
                }
                
                cout << "Ingrese legajo del estudiante: ";
                cin >> legajo;
                
                bool desinscripcionExitosa = cursosDisponibles[indiceCurso - 1]->desinscribirEstudiante(legajo);
                if (desinscripcionExitosa) {
                    cout << "Estudiante desinscrito correctamente.\n";
                } else {
                    cout << "Error: No se pudo desinscribir al estudiante (no está inscrito).\n";
                }
                break;
            }
            case VERIFICAR_INSCRIPCION: {
                // Verificar si un estudiante está inscrito
                int legajo, indiceCurso;
                
                cout << "===== VERIFICAR INSCRIPCIÓN =====\n";
                
                // Mostrar lista de cursos
                cout << "Cursos disponibles:\n";
                for (size_t i = 0; i < cursosDisponibles.size(); i++) {
                    cout << i + 1 << ". " << cursosDisponibles[i]->getNombre() << endl;
                }
                
                cout << "Seleccione un curso (1-" << cursosDisponibles.size() << "): ";
                cin >> indiceCurso;
                
                if (indiceCurso < 1 || indiceCurso > static_cast<int>(cursosDisponibles.size())) {
                    cout << "Opción inválida.\n";
                    break;
                }
                
                cout << "Ingrese legajo del estudiante: ";
                cin >> legajo;
                
                bool estaInscrito = cursosDisponibles[indiceCurso - 1]->estaInscrito(legajo);
                if (estaInscrito) {
                    cout << "El estudiante SÍ está inscrito en este curso.\n";
                } else {
                    cout << "El estudiante NO está inscrito en este curso.\n";
                }
                break;
            }
            case VERIFICAR_CURSO_COMPLETO: {
                // Verificar si un curso está completo
                int indiceCurso;
                
                cout << "===== VERIFICAR SI UN CURSO ESTÁ COMPLETO =====\n";
                
                // Mostrar lista de cursos
                cout << "Cursos disponibles:\n";
                for (size_t i = 0; i < cursosDisponibles.size(); i++) {
                    cout << i + 1 << ". " << cursosDisponibles[i]->getNombre() << endl;
                }
                
                cout << "Seleccione un curso (1-" << cursosDisponibles.size() << "): ";
                cin >> indiceCurso;
                
                if (indiceCurso < 1 || indiceCurso > static_cast<int>(cursosDisponibles.size())) {
                    cout << "Opción inválida.\n";
                    break;
                }
                
                bool estaCompleto = cursosDisponibles[indiceCurso - 1]->estaCompleto();
                if (estaCompleto) {
                    cout << "El curso está completo.\n";
                } else {
                    cout << "El curso NO está completo.\n";
                }
                break;
            }
            case MOSTRAR_ESTUDIANTES: {
                // Mostrar lista de estudiantes de un curso
                int indiceCurso;
                
                cout << "===== MOSTRAR LISTA DE ESTUDIANTES =====\n";
                
                // Mostrar lista de cursos
                cout << "Cursos disponibles:\n";
                for (size_t i = 0; i < cursosDisponibles.size(); i++) {
                    cout << i + 1 << ". " << cursosDisponibles[i]->getNombre() << endl;
                }
                
                cout << "Seleccione un curso (1-" << cursosDisponibles.size() << "): ";
                cin >> indiceCurso;
                
                if (indiceCurso < 1 || indiceCurso > static_cast<int>(cursosDisponibles.size())) {
                    cout << "Opción inválida.\n";
                    break;
                }
                
                cout << *cursosDisponibles[indiceCurso - 1];
                break;
            }
            case ASIGNAR_NOTA: {
                // Asignar nota a estudiante en un curso
                int legajo, indiceCurso;
                float nota;
                
                cout << "===== ASIGNAR NOTA A ESTUDIANTE =====\n";
                
                // Mostrar lista de cursos
                cout << "Cursos disponibles:\n";
                for (size_t i = 0; i < cursosDisponibles.size(); i++) {
                    cout << i + 1 << ". " << cursosDisponibles[i]->getNombre() << endl;
                }
                
                cout << "Seleccione un curso (1-" << cursosDisponibles.size() << "): ";
                cin >> indiceCurso;
                
                if (indiceCurso < 1 || indiceCurso > static_cast<int>(cursosDisponibles.size())) {
                    cout << "Opción inválida.\n";
                    break;
                }
                
                cout << "Ingrese legajo del estudiante: ";
                cin >> legajo;
                
                // Buscar estudiante por legajo
                Estudiante* estudianteEncontrado = nullptr;
                for (auto est : estudiantesRegistrados) {
                    if (est->getLegajo() == legajo) {
                        estudianteEncontrado = est;
                        break;
                    }
                }
                
                if (estudianteEncontrado == nullptr) {
                    cout << "Error: No existe un estudiante con ese legajo.\n";
                } else {
                    // Verificar si está inscrito
                    if (!cursosDisponibles[indiceCurso - 1]->estaInscrito(legajo)) {
                        cout << "Error: El estudiante no está inscrito en este curso.\n";
                        break;
                    }
                    
                    cout << "Ingrese nota (0-10): ";
                    cin >> nota;
                    
                    if (nota < 0 || nota > 10) {
                        cout << "Error: La nota debe estar entre 0 y 10.\n";
                        break;
                    }
                    
                    estudianteEncontrado->agregarCursoNota(cursosDisponibles[indiceCurso - 1]->getNombre(), nota);
                    cout << "Nota asignada correctamente.\n";
                }
                break;
            }
            case COPIAR_CURSO: {
                // Crear copia de un curso
                int indiceCurso;
                string nuevoNombre;
                
                cout << "===== CREAR COPIA DE UN CURSO =====\n";
                
                // Mostrar lista de cursos
                cout << "Cursos disponibles:\n";
                for (size_t i = 0; i < cursosDisponibles.size(); i++) {
                    cout << i + 1 << ". " << cursosDisponibles[i]->getNombre() << endl;
                }
                
                cout << "Seleccione un curso a copiar (1-" << cursosDisponibles.size() << "): ";
                cin >> indiceCurso;
                
                if (indiceCurso < 1 || indiceCurso > static_cast<int>(cursosDisponibles.size())) {
                    cout << "Opción inválida.\n";
                    break;
                }
                
                cout << "Ingrese nombre para el nuevo curso: ";
                cin.ignore();
                getline(cin, nuevoNombre);
                
                // Crear copia del curso seleccionado con el constructor de copia
                Curso* cursoOriginal = cursosDisponibles[indiceCurso - 1];
                Curso* nuevoCurso = new Curso(*cursoOriginal); // Usa el constructor de copia
                
                // El constructor de copia ya copió todos los estudiantes
                // Solo necesitamos crear un curso con el nuevo nombre y copiar manualmente los estudiantes
                Curso* cursoConNuevoNombre = new Curso(nuevoNombre);
                
                // Copiar cada estudiante del curso original al nuevo curso
                for (auto est : estudiantesRegistrados) {
                    if (cursoOriginal->estaInscrito(est->getLegajo())) {
                        cursoConNuevoNombre->inscribirEstudiante(est);
                    }
                }
                
                delete nuevoCurso; // Eliminamos el curso temporal
                cursosDisponibles.push_back(cursoConNuevoNombre);
                cout << "Curso copiado correctamente.\n";
                break;
            }
            case SALIR: {
                // Liberar memoria antes de salir
                for (auto& est : estudiantesRegistrados) {
                    delete est;
                }
                for (auto& curso : cursosDisponibles) {
                    delete curso;
                }
                
                cout << "Gracias por usar el sistema. ¡Hasta pronto!\n";
                return 0;
            }
            default:
                cout << "Opción inválida. Por favor, intente nuevamente.\n";
        }
        
        cout << "\nPresione Enter para continuar...";
        cin.ignore(); // Este es para limpiar el buffer de entrada
        cin.get(); // Espera a que el usuario presione Enter
        limpiarPantalla();
    }
    
    return 0;
}