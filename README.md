# Homework-2: Paradigmas de Programación

<div align="center">
    <hr style="height: 2px; background-color: #0066cc; width: 80%;">
    <h2>🔷 Programación Orientada a Objetos en C++ 🔷</h2>
    <p><em>Universidad de San Andrés - 2025</em></p>
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
            <td>
                <a href="#ejercicio-1-reloj">⏰ Ejercicio 1: Reloj</a>
            </td>
            <td>
                <a href="#ejercicio-2-sistema-de-gestión-de-cursos">🎓 Ejercicio 2: Sistema de Gestión de Cursos</a>
            </td>
        </tr>
        <tr>
            <td>
                <a href="#ejercicio-3-sistema-de-números">🔢 Ejercicio 3: Sistema de Números</a>
            </td>
            <td>
                <a href="#ejercicio-4-sistema-bancario">💰 Ejercicio 4: Sistema Bancario</a>
            </td>
        </tr>
    </table>
</div>

---

## Ejercicio 1: Reloj

En este ejercicio se implementa una clase en C++ que representa un reloj digital con múltiples formatos horarios, demostrando conceptos de sobrecarga de constructores, validación de datos y encapsulamiento.

### Descripción

La clase `Reloj` encapsula la lógica de un reloj digital con formatos de 12 y 24 horas. Este ejercicio demuestra el uso adecuado de:
- Validación robusta de entrada para garantizar valores correctos
- Conversión bidireccional entre formatos horarios
- API completa para manipulación del tiempo
- Tipos `unsigned` para prevenir valores negativos
- Manejo de límites en valores temporales

### Funcionalidades Implementadas

#### 1. Constructores Sobrecargados
La clase implementa múltiples constructores para facilitar la creación de objetos con distintos niveles de detalle:

- **Constructor por defecto**: `Reloj()` → Inicializa a 12:00:00 a.m.
```cpp
Reloj miReloj; // Crea un reloj en 12:00:00 a.m.
```

- **Constructor con hora**: `Reloj(unsigned int h)` → Valida y asigna hora (1-12)
```cpp
Reloj miReloj(3); // Crea un reloj en 3:00:00 a.m.
```

- **Constructor con hora y minutos**: `Reloj(unsigned int h, unsigned int m)`
```cpp
Reloj miReloj(3, 30); // Crea un reloj en 3:30:00 a.m.
```

- **Constructor con hora, minutos y segundos**: `Reloj(unsigned int h, unsigned int m, unsigned int s)`
```cpp
Reloj miReloj(3, 30, 45); // Crea un reloj en 3:30:45 a.m.
```

- **Constructor completo**: `Reloj(unsigned int h, unsigned int m, unsigned int s, bool es_pm)`
```cpp
Reloj miReloj(3, 30, 45, true); // Crea un reloj en 3:30:45 p.m.
```

#### 2. Getters y Setters con Validación

La clase proporciona métodos de acceso que implementan validación robusta:

- **Getters**: `getHora()`, `getMinuto()`, `getSegundo()`, `esPM()`
- **Setters**: Retornan un valor booleano que indica si el valor proporcionado requirió corrección:
  - `setHora(unsigned int h)` → Asegura valores entre 1-12
  - `setMinuto(unsigned int m)` → Asegura valores entre 0-59
  - `setSegundo(unsigned int s)` → Asegura valores entre 0-59
  - `setPM(bool es_pm)` → Establece si la hora es AM o PM

#### 3. Representación de Tiempo

Múltiples opciones para visualizar el tiempo:

- `mostrarHora12()` → Formatea como "hh, mm, ss a.m./p.m."
- `mostrarHora24()` → Formatea como "hh:mm:ss"
- `imprimirHora24()` → Salida directa por consola

### Validación de Datos

La clase implementa dos métodos privados para validación:

1. `validarHora(unsigned int &h)` → Corrige horas fuera del rango 1-12
2. `validarMinSeg(unsigned int &valor)` → Corrige minutos/segundos fuera del rango 0-59

Estos métodos aseguran que los valores internos sean siempre válidos, incluso si los datos de entrada son incorrectos.

### Interfaz de Usuario

La función `interaccion()` proporciona un menú completo para probar todas las funcionalidades:

- Creación de relojes con distintos constructores
- Modificación de componentes del tiempo
- Visualización en formatos de 12 y 24 horas
- Alternancia entre AM y PM

### Compilación y Ejecución

```bash
# Compilación estándar con optimizaciones
g++ main.cpp reloj.cpp -O2 -Wall -Wextra -std=c++20 -o reloj

# Verificación de fugas de memoria
valgrind --leak-check=full --show-leak-kinds=all ./reloj

# Ejecución
./reloj
```

### Estructura del Código

- **reloj.h**: Define la clase `Reloj` y funciones auxiliares para la interfaz
  - Documentación inline estilo Doxygen para todos los métodos
  - Enum `OpcionMenu` para las opciones de interfaz

- **reloj.cpp**: Implementa todos los métodos de `Reloj` y funciones auxiliares
  - Validadores privados para garantizar la integridad de los datos
  - Uso de `stringstream` para formateo preciso de salida

- **main.cpp**: Punto de entrada que inicializa la interfaz de usuario

---

## Ejercicio 2: Sistema de Gestión de Cursos

Este ejercicio implementa un sistema de administración académica que demuestra relaciones entre clases, gestión de memoria con punteros y manejo de colecciones en C++.

### Descripción

El sistema modela la administración de cursos y estudiantes, demostrando:
- Relación de asociación (no composición) entre entidades
- Gestión eficiente de objetos compartidos mediante punteros
- Almacenamiento y cálculo de calificaciones
- Operaciones de inscripción y desinscripción

### Modelado del Dominio

El sistema se compone de dos clases principales que interactúan entre sí:

#### 1. Clase `Estudiante`

Representa a un alumno con sus datos personales y académicos:

```cpp
class Estudiante {
private:
    string nombreCompleto;
    int legajo;
    map<string, vector<float>> cursosNotas; // Almacena vectores de notas por curso
    // ...
};
```

**Características:**
- Almacenamiento eficiente de múltiples calificaciones mediante `std::map<string, vector<float>>`
- Posibilidad de registrar varias notas para un mismo curso
- Cálculo de promedios considerando todas las notas de todos los cursos
- Persistencia de calificaciones incluso después de desinscribirse de un curso
- Identificación única mediante legajo

#### 2. Clase `Curso`

Representa un curso con su listado de estudiantes inscritos:

```cpp
class Curso {
private:
    string nombre;
    vector<Estudiante*> estudiantes;
    const int capacidadMaxima = 20;
    // ...
};
```

**Características:**
- Vector de punteros a `Estudiante` (asociación sin ownership)
- Restricción de capacidad máxima (20 estudiantes)
- Ordenamiento alfabético en reportes mediante `std::sort` con lambda functions
- Constructor de copia que implementa shallow copy intencional

### Relación entre Clases

La relación implementada entre `Curso` y `Estudiante` es una **asociación**, no una composición ni una agregación fuerte:

1. Un curso puede contener varios estudiantes
2. Un estudiante puede estar inscrito en varios cursos
3. Los estudiantes existen independientemente de los cursos
4. La destrucción de un curso no implica la destrucción de los estudiantes

Este patrón se implementa mediante:
- Almacenamiento de punteros (`vector<Estudiante*>`) en lugar de objetos
- Destructor que libera el vector pero no los objetos apuntados
- Copia superficial (shallow copy) en el constructor de copia

### Funcionalidades Clave

1. **Gestión de Estudiantes:**
   - Registro de estudiantes con validación de legajo único
   - Asignación de calificaciones por curso
   - Cálculo de promedio general

2. **Gestión de Cursos:**
   - Creación de cursos con nombre único
   - Inscripción/desinscripción de estudiantes
   - Verificación de cupo disponible
   - Reporte ordenado alfabéticamente de estudiantes inscritos

3. **Operador Sobrecargado:**
   - `operator<<` para visualización formateada de cursos y sus estudiantes
   ```cpp
   cout << *curso; // Muestra lista ordenada de estudiantes
   ```

### Interfaz de Usuario

El programa implementa un menú completo con las siguientes opciones:
- Registro de nuevos estudiantes
- Creación de cursos
- Inscripción y desinscripción de estudiantes
- Verificación de inscripciones y cupos
- Asignación de calificaciones
- Copia de cursos existentes

### Manejo de Memoria

El programa implementa gestión correcta de memoria:
- Constructor de copia para duplicar cursos
- Destructor que limpia adecuadamente los recursos
- Liberación de todos los objetos al finalizar

### Manejo de Calificaciones

El sistema implementa un manejo robusto de calificaciones con las siguientes características:

1. **Almacenamiento múltiple de notas:**
   - Cada curso puede tener múltiples calificaciones para un estudiante
   - Se utiliza un vector de notas para cada curso (`map<string, vector<float>>`)
   - El promedio se calcula sobre todas las notas de todos los cursos

2. **Persistencia de calificaciones:**
   - Cuando un estudiante se desinscribe de un curso, sus calificaciones se mantienen
   - Esto refleja el comportamiento real de sistemas académicos donde el historial se preserva
   - Las notas siguen contando para el promedio general del estudiante
   - Este comportamiento permite mantener un registro académico completo y preciso

3. **Asignación de múltiples notas:**
   - Cada vez que se asigna una nota, se agrega al vector de calificaciones del curso
   - Esto permite registrar parciales, exámenes y otras evaluaciones para el mismo curso

### Compilación y Ejecución

```bash
# Build estándar
g++ -Wall -Werror -std=c++20 main.cpp curso.cpp -o gestion_cursos

# Build con depuración
g++ -g -Wall -Werror -std=c++20 main.cpp curso.cpp -o gestion_cursos

# Análisis de memoria con Valgrind
valgrind --leak-check=full --track-origins=yes ./gestion_cursos
```

### Estructura de Archivos

- **curso.h:** Definiciones de clases con documentación Doxygen
  - Enumeración `OpcionMenu` para las opciones de interfaz
  - Clases `Estudiante` y `Curso`
  - Declaración de la función friend para sobrecarga del operador `<<`

- **curso.cpp:** Implementación de las clases y la interfaz
  - Métodos para mantener la integridad de los datos
  - Implementación del operador sobrecargado
  - Función `interaccion()` para el menú principal

- **main.cpp:** Punto de entrada del programa
  - Llamada a la función de interacción

---

## Ejercicio 3: Sistema de Números

Este ejercicio implementa una jerarquía de clases para operaciones aritméticas con diferentes tipos numéricos, demostrando polimorfismo, herencia, manejo de excepciones y RTTI.

### Descripción

El sistema permite realizar operaciones aritméticas con diferentes tipos numéricos (enteros, reales y complejos) a través de una interfaz común, aprovechando las características avanzadas de OOP:

- **Polimorfismo**: A través de clases derivadas de una base abstracta
- **RTTI**: Uso de `dynamic_cast` para operaciones entre tipos diferentes
- **Excepciones**: Manejo robusto de errores como división por cero
- **Method Chaining**: Diseño que permite encadenar operaciones

### Jerarquía de Clases

#### 1. Clase Abstracta Base: `Numero`

```cpp
class Numero {
public:
    virtual Numero& suma(const Numero& otro) = 0;
    virtual Numero& resta(const Numero& otro) = 0;
    virtual Numero& multiplicacion(const Numero& otro) = 0;
    virtual Numero& division(const Numero& otro) = 0;
    virtual std::string toString() const = 0;
    virtual ~Numero() = default;
};
```

Esta clase define una interfaz común para todos los tipos numéricos mediante:
- Métodos virtuales puros para operaciones aritméticas
- Retorno por referencia para permitir encadenamiento de operaciones
- Destructor virtual para asegurar liberación correcta de recursos

#### 2. Clase Derivada: `Entero`

```cpp
class Entero : public Numero {
private:
    int valor;
public:
    // Constructores y métodos...
};
```

Características:
- Encapsula un valor entero (`int`)
- Implementa operaciones aritméticas básicas
- Convierte otros tipos numéricos a entero si es posible
- Maneja excepciones como división por cero o desbordamiento

Ejemplo de implementación:
```cpp
Numero& Entero::suma(const Numero& otro) {
    const Entero* otroEntero = dynamic_cast<const Entero*>(&otro);
    
    if (otroEntero) {
        valor += otroEntero->getValor();
    } else {
        try {
            valor += std::stoi(otro.toString());
        } catch (const std::exception& e) {
            throw std::invalid_argument("No se puede sumar: valor incompatible");
        }
    }
    
    return *this;
}
```

#### 3. Clase Derivada: `Real`

```cpp
class Real : public Numero {
private:
    double valor;
public:
    // Constructores y métodos...
};
```

Características:
- Encapsula un valor real (`double`)
- Proporciona formateo de salida con precisión controlada
- Maneja la conversión desde otros tipos numéricos

#### 4. Clase Derivada: `Complejo`

```cpp
class Complejo : public Numero {
private:
    double real;
    double imaginario;
public:
    // Constructores y métodos...
};
```

Características:
- Representa números con parte real e imaginaria
- Implementa aritmética compleja (multiplicación, división por conjugados)
- Formatea la salida en forma canónica (a ± bi)

### Operaciones entre Tipos Distintos

El sistema implementa operaciones entre tipos numéricos distintos mediante:

1. **Conversión segura con RTTI**:
   ```cpp
   const Entero* otroEntero = dynamic_cast<const Entero*>(&otro);
   if (otroEntero) {
       // Operación entre tipos iguales
   } else {
       // Intento de convertir el otro tipo
   }
   ```

2. **Conversión a través de representaciones string**:
   ```cpp
   try {
       valor += std::stod(otro.toString());
   } catch (const std::exception& e) {
       throw std::invalid_argument("Valor incompatible");
   }
   ```

3. **Manejo jerárquico para operaciones complejas**:
   - Complejos pueden operar con reales y enteros
   - Reales pueden operar con enteros
   - Enteros tienen conversiones más restrictivas

### Sistema de Pruebas

El sistema incluye un framework de pruebas completo que verifica:

1. **Operaciones con tipos homogéneos**:
   - Entero con Entero, Real con Real, Complejo con Complejo

2. **Operaciones con tipos heterogéneos**:
   - Entero con Real, Real con Complejo, etc.

3. **Casos especiales**:
   - División por cero
   - Operaciones con valores límite
   - Conversiones imposibles

4. **Comportamiento con errores**:
   - Verificación de excepciones lanzadas correctamente
   - Recuperación de operaciones fallidas

### Compilación y Ejecución

```bash
# Compilación estándar
g++ -Wall -pedantic main.cpp numeros.cpp -std=c++20 -o numeros

# Compilación con información de depuración
g++ -g -Wall -pedantic main.cpp numeros.cpp -std=c++20 -o numeros

# Ejecución con Valgrind para detección de fugas
valgrind --leak-check=full --track-origins=yes ./numeros

# Ejecución normal
./numeros
```

### Estructura de Archivos

- **numeros.h**: Declaración de la jerarquía de clases
  - Clase abstracta `Numero`
  - Clases derivadas: `Entero`, `Real`, `Complejo`
  - Documentación de la API

- **numeros.cpp**: Implementación de las clases
  - Operaciones aritméticas con verificación de tipos
  - Gestión de excepciones
  - Funciones de prueba automatizadas

- **main.cpp**: Programa principal para ejecutar las pruebas
  - Inicialización del sistema de pruebas
  - Captura de excepciones no manejadas

---

## Ejercicio 4: Sistema Bancario

Este ejercicio implementa un sistema bancario que demuestra conceptos avanzados de programación orientada a objetos: herencia, polimorfismo, clases friend, const correctness y manejo del estado mutable.

### Descripción

El sistema modela diferentes tipos de cuentas bancarias que permiten operaciones como depósitos y retiros. Además, implementa mecanismos avanzados como:

- Relaciones privilegiadas entre cuentas (vinculación de cuenta corriente y caja de ahorro)
- Modificación controlada de estado en contextos constantes
- Comportamiento polimórfico mediante métodos virtuales
- Protección de invariantes de clase

### Arquitectura del Sistema

#### 1. Clase Base Abstracta: `CuentaBanco`

```cpp
class CuentaBanco {
private:
    double balance;
    virtual void mostrarInfo() const = 0;
protected:
    std::string titularCuenta;
public:
    // Métodos...
};
```

Características:
- Encapsulación de `balance` como miembro privado
- Protección de `titularCuenta` para acceso por clases derivadas
- Método abstracto `mostrarInfo()` para implementación polimórfica
- Métodos públicos para operaciones comunes (depósitos, consultas)

#### 2. Clase Derivada: `CajaDeAhorro`

```cpp
class CajaDeAhorro : public CuentaBanco {
private:
    mutable int contadorMostrarInfo;
    void mostrarInfo() const override;
public:
    // Métodos...
    friend class CuentaCorriente;
};
```

Características:
- Implementa retiros con validación de fondos disponibles
- Utiliza `mutable` para permitir modificar el contador en métodos const
- Aplica descuentos automáticos tras múltiples consultas
- Proporciona acceso privilegiado a `CuentaCorriente` mediante friendship

#### 3. Clase Derivada: `CuentaCorriente`

```cpp
class CuentaCorriente : public CuentaBanco {
private:
    CajaDeAhorro& cajaAhorro;
    void mostrarInfo() const override;
public:
    // Métodos...
};
```

Características:
- Mantiene una referencia permanente a una `CajaDeAhorro`
- Implementa retiros inteligentes que pueden usar fondos de la caja de ahorro
- Accede a miembros protegidos de `CajaDeAhorro` mediante relación de amistad

### Relaciones entre Clases

El sistema implementa dos tipos de relaciones:

1. **Herencia**: Las clases `CajaDeAhorro` y `CuentaCorriente` heredan de `CuentaBanco`.
   - Comparten la interfaz básica y comportamiento
   - Sobrescriben comportamiento específico mediante polimorfismo

2. **Amistad**: La clase `CuentaCorriente` es friend de `CajaDeAhorro`.
   - Permite acceso controlado entre clases relacionadas
   - Habilita la implementación de retiros desde la caja de ahorro vinculada
   - Mantiene la encapsulación para el resto del sistema

### Técnicas Avanzadas Implementadas

#### 1. Const Correctness

El sistema implementa "const correctness" de manera rigurosa:
- Métodos de consulta marcados como `const`
- Parámetros que no serán modificados pasados por referencia constante
- Retorno de valores inmutables mediante `const`

Ejemplo:
```cpp
void applyFee(double monto) const {
    CuentaBanco* nonConstThis = const_cast<CuentaBanco*>(this);
    nonConstThis->balance -= monto;
}
```

#### 2. Modificación de Miembros Mutables

La clase `CajaDeAhorro` utiliza un contador mutable para realizar modificaciones en métodos constantes:

```cpp
void CajaDeAhorro::mostrarInfo() const {
    contadorMostrarInfo++; // Modificación legal en método const
    // ...
}
```

#### 3. Friend Class para Acceso Controlado

La relación de amistad permite a `CuentaCorriente` acceder a funcionalidad protegida de `CajaDeAhorro`:

```cpp
bool CuentaCorriente::retirar(double monto) {
    // ...
    if (monto <= cajaAhorro.getBalance()) {
        cajaAhorro.setBalance(cajaAhorro.getBalance() - monto);
        return true;
    }
    // ...
}
```

#### 4. Referencias para Relaciones Permanentes

La clase `CuentaCorriente` mantiene una referencia permanente a `CajaDeAhorro`:

```cpp
CuentaCorriente::CuentaCorriente(const std::string& titular, CajaDeAhorro& caja, double saldoInicial)
    : CuentaBanco(titular, saldoInicial), cajaAhorro(caja) {
}
```

Esto asegura que:
- La relación es obligatoria (no puede haber una cuenta corriente sin caja de ahorro asociada)
- La relación no puede cambiar durante la vida del objeto
- No es posible crear referencias nulas o inválidas

### Escenarios de Prueba

El sistema incluye una función completa de prueba (`testSistemaBancario()`) que verifica:

1. **Creación de cuentas**:
   - Caja de ahorro con saldo inicial
   - Cuenta corriente vinculada a la caja de ahorro

2. **Operaciones básicas**:
   - Depósitos en ambos tipos de cuenta
   - Retiros estándar de cada cuenta

3. **Escenarios avanzados**:
   - Retiro que excede el saldo de la caja de ahorro
   - Retiro de cuenta corriente usando fondos de la caja de ahorro
   - Intento de retiro cuando no hay fondos suficientes en ninguna cuenta

4. **Comportamiento const y mutable**:
   - Aplicación de descuentos por consultas múltiples
   - Modificación segura de estado mutable en contextos const

### Compilación y Ejecución

```bash
# Compilación estándar
g++ -Wall -Wextra -Wpedantic main.cpp banco.cpp -std=c++20 -o banco

# Compilación con información de depuración
g++ -g -Wall -Wextra -Wpedantic main.cpp banco.cpp -std=c++20 -o banco

# Verificación de memoria con Valgrind
valgrind --tool=memcheck --show-reachable=yes --leak-check=full ./banco

# Ejecución normal
./banco
```

### Estructura del Código

- **banco.h**: Definición de la jerarquía de clases
  - Documentación detallada de la API
  - Especificación de la relación de amistad
  - Declaración de métodos virtuales y constantes

- **banco.cpp**: Implementación de las clases
  - Validación de operaciones bancarias
  - Comportamiento para escenarios especiales
  - Función de prueba integrada

- **main.cpp**: Programa principal
  - Inicialización del sistema de prueba
````
