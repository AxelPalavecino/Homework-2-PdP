# Homework-2: Paradigmas de Programación

<div align="center">
    <hr style="height: 2px; background-color: #0066cc; width: 80%;">
    <hr style="height: 2px; background-color: #0066cc; width: 80%;">
</div>

## Índice de Contenidos

<div align="center">
    <img src="udesa-logo.jpg" alt="UDESA Logo" width="150">
    <h1>Implementaciones de POO en C++</h1>
</div>

<div align="center">
    <table>
        <tr>
            <td><a href="#ejercicio-1-reloj">Ejercicio 1: Reloj</a></td>
            <td><a href="#ejercicio-2-sistema-de-gestión-de-cursos">Ejercicio 2: Sistema de Gestión de Cursos</a></td>
        </tr>
        <tr>
            <td><a href="#ejercicio-3-sistema-de-números">Ejercicio 3: Sistema de Números</a></td>
            <td><a href="#ejercicio-4-sistema-bancario">Ejercicio 4: Sistema Bancario</a></td>
        </tr>
    </table>
</div>

---

## Ejercicio 1: Reloj

Implementación de una clase para representar un reloj con soporte dual de formatos horarios.

### Descripción

La clase `Reloj` encapsula la lógica de un reloj digital con formato de 12 y 24 horas. Implementa validación robusta de entrada, conversión entre formatos y proporciona una API completa para manipulación de tiempo. Utiliza tipos unsigned para prevenir valores negativos y maneja adecuadamente los límites de valores de tiempo.

### Funcionalidades Implementadas

1. **Constructores Sobrecargados**:
   - `Reloj()` → Inicializa a 12:00:00 a.m.
   - `Reloj(unsigned int h)` → Valida y asigna hora (1-12)
   - `Reloj(unsigned int h, unsigned int m)` → Añade validación para minutos (0-59)
   - `Reloj(unsigned int h, unsigned int m, unsigned int s)` → Añade validación para segundos
   - `Reloj(unsigned int h, unsigned int m, unsigned int s, bool es_pm)` → Constructor completo

2. **Getters/Setters con Validación**:
   - Métodos `getHora()`, `getMinuto()`, `getSegundo()`, `esPM()`
   - Setters que retornan bool indicando si el valor requirió corrección

3. **Representación de Tiempo**:
   - `mostrarHora12()` → Formatea como "hh, mm, ss a.m./p.m."
   - `mostrarHora24()` → Formatea como "hh:mm:ss"
   - `imprimirHora24()` → Salida directa a consola

### Compilación

```bash
# Compilación estándar con optimizaciones
g++ main.cpp reloj.cpp -O2 -Wall -Wextra -std=c++20 -o reloj

# Verificación de fugas de memoria
valgrind --leak-check=full --show-leak-kinds=all ./reloj
```

### Estructura del Código

- **reloj.h**: Definición de la clase con documentación inline
- **reloj.cpp**: Implementación de los métodos y validadores
- **main.cpp**: Interfaz de usuario para pruebas interactivas

---

## Ejercicio 2: Sistema de Gestión de Cursos

Sistema para administración académica que implementa asociación entre entidades y manejo de memoria.

### Descripción

Este sistema demuestra la implementación de una relación de asociación entre clases `Curso` y `Estudiante`. Utiliza punteros para gestionar referencias sin duplicación de datos, implementa límites de capacidad para cursos, y gestiona la persistencia de calificaciones entre sesiones.

### Clases y Responsabilidades

1. **Estudiante**:
   - Manejo de datos personales y académicos
   - Almacenamiento eficiente de notas mediante `std::map<string, float>`
   - Cálculo de promedios con validación de entrada

2. **Curso**:
   - Vector de punteros a `Estudiante` (asociación sin ownership)
   - Restricción de capacidad mediante constante `capacidadMaxima`
   - Ordenamiento alfabético de estudiantes en reportes
   - Constructor de copia que implementa shallow copy intencional

### Características Técnicas

- Utilización de punteros para evitar duplicación de entidades
- Destructor que libera recursos sin eliminar entidades compartidas
- Sobrecarga del operador `<<` para visualización
- Validación de legajos para prevenir duplicados
- Ordenamiento mediante lambda functions con STL

### Comandos de Build

```bash
# Build de producción
g++ -Wall -Werror -std=c++20 main.cpp curso.cpp -o gestion_cursos

# Ejecución con Valgrind para detección de fugas
valgrind --leak-check=full --track-origins=yes ./gestion_cursos
```

### Estructura de Archivos

- **curso.h**: Definiciones de clases con documentación Doxygen
- **curso.cpp**: Implementaciones que garantizan invariantes de clase
- **main.cpp**: Interfaz basada en menús con validación de entrada

---

## Ejercicio 3: Sistema de Números

Implementación de jerarquía de clases para operaciones numéricas con soporte para tipos heterogéneos.

### Descripción

Sistema de tipos numéricos basado en una jerarquía de polimorfismo para representar y operar con enteros, reales y complejos. Implementa operaciones aritméticas tipo-seguras mediante RTTI (dynamic_cast) y manejo de excepciones. Demuestra principios SOLID con separación clara de responsabilidades.

### Jerarquía de Clases

1. **Numero (Abstracta)**:
   - Define interfaz para operaciones con método `virtual` y destructores
   - Métodos puros: `suma()`, `resta()`, `multiplicacion()`, `division()`, `toString()`
   - Diseño basado en Method Chaining para composición de operaciones

2. **Entero**:
   - Encapsula valor de tipo `int`
   - Implementa conversión desde otros tipos numéricos mediante RTTI
   - Validación para evitar division-by-zero con excepciones

3. **Real**:
   - Representa números de punto flotante con `double`
   - Formateo preciso con manipuladores de `std::stringstream`
   - Manejo de errores para operaciones no válidas

4. **Complejo**:
   - Representación canónica `a + bi`
   - Algoritmos de división por conjugados optimizados
   - Detección de casos especiales (división por cero complejo)

### Testing Framework Implementado

- Suite de pruebas automatizadas para cada tipo
- Ejercitación de casos edge: divisiones por cero, conversiones de tipos
- Pruebas de stress con operaciones encadenadas

### Compilación y Ejecución

```bash
# Compilación estándar
g++ -Wall -pedantic main.cpp numeros.cpp -std=c++20 -o numeros

# Ejecución con Valgrind para detección de fugas
valgrind --leak-check=full --track-origins=yes ./numeros
```

### Ficheros

- **numeros.h**: Declaración de jerarquía con herencia y métodos virtuales
- **numeros.cpp**: Implementación con RTTI y exception handling
- **main.cpp**: Pruebas exhaustivas del sistema numérico

---

## Ejercicio 4: Sistema Bancario

Sistema bancario que demuestra conceptos avanzados de OOP: encapsulamiento, herencia, polimorfismo, friend classes y const correctness.

### Descripción

Implementación de un sistema bancario que modela diferentes tipos de cuentas con jerarquía de herencia. Utiliza `friend class` para acceso controlado entre cuentas asociadas, métodos virtuales puros para comportamiento polimórfico y manejo de invariantes mediante métodos `const`. Demuestra el uso correcto de `mutable` para variables que deben modificarse en contextos constantes.

### Arquitectura Implementada

1. **CuentaBanco (Abstracta)**:
   - Encapsula `balance` como miembro privado y `titularCuenta` como protegido
   - Define comportamiento común mediante método virtual puro `mostrarInfo()`
   - Proporciona método `applyFee()` const-correct mediante `const_cast`

2. **CajaDeAhorro**:
   - Variable `mutable` para contar accesos de consulta
   - Validación estricta para evitar sobregiros
   - Descuento automático tras múltiples consultas

3. **CuentaCorriente**:
   - Acceso privilegiado a `CajaDeAhorro` mediante relación `friend`
   - Retiro inteligente que selecciona la fuente de fondos
   - Vinculación permanente a cuenta de ahorro mediante referencia

### Características Técnicas Destacadas

- Uso correcto de `const`, `override` y `friend` para control de acceso
- Implementación de polimorfismo mediante métodos virtuales
- Manejo seguro de estado mutable en contextos const
- Relaciones rígidas entre clases mediante referencias

### Comandos de Compilación

```bash
# Compilación con advertencias estrictas
g++ -Wall -Wextra -Wpedantic main.cpp banco.cpp -std=c++20 -o banco

# Verificación de memoria con Valgrind
valgrind --tool=memcheck --show-reachable=yes --leak-check=full ./banco
```

### Estructura de Código

- **banco.h**: Declaración de jerarquía con relaciones complejas y acceso controlado
- **banco.cpp**: Implementación que mantiene invariantes del sistema bancario
- **main.cpp**: Programa principal para demostración del sistema
