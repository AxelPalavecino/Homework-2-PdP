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
    vector<Estudiante*> estudiantesRegistrados;
    vector<Curso*> cursosDisponibles;

    // Crear algunos cursos iniciales
    cursosDisponibles.push_back(new Curso("Programacion"));
    cursosDisponibles.push_back(new Curso("Matematicas"));
    cursosDisponibles.push_back(new Curso("Fisica"));

    int opcion = 0;
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
        cin >> opcion;

        limpiarPantalla();

        switch (opcion) {
            case 1: {
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
            case 2: {
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
            case 3: {
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
            case 4: {
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
            case 5: {
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
            case 6: {
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
            case 7: {
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
            case 8: {
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
            case 9: {
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
            case 10: {
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
