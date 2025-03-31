#include "numeros.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

// Implementación de la clase Entero
Entero::Entero() : valor(0) {} // Constructor predeterminado, asigna 0

Entero::Entero(int val) : valor(val) {}

int Entero::getValor() const {
    return valor;
}

Numero& Entero::suma(const Numero& otro) {
    // Intentamos hacer un dynamic_cast para verificar si 'otro' es un Entero
    const Entero* otroEntero = dynamic_cast<const Entero*>(&otro);
    
    if (otroEntero) {
        // Si es un Entero, sumamos directamente
        valor += otroEntero->getValor();
    } else {
        // Si no es un Entero, convertimos a string y parseamos
        try {
            valor += std::stoi(otro.toString());
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("No se puede sumar: el valor '" + otro.toString() + "' no es convertible a entero");
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("No se puede sumar: el valor '" + otro.toString() + "' está fuera del rango permitido para enteros");
        }
    }
    
    return *this; // Devolvemos la referencia al objeto actual, permitiendo encadenar operaciones, this es un puntero a la clase actual. 
}

Numero& Entero::resta(const Numero& otro) {
    const Entero* otroEntero = dynamic_cast<const Entero*>(&otro);
    
    if (otroEntero) {
        valor -= otroEntero->getValor();
    } else {
        try {
            valor -= std::stoi(otro.toString());
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("No se puede restar: el valor '" + otro.toString() + "' no es convertible a entero");
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("No se puede restar: el valor '" + otro.toString() + "' está fuera del rango permitido para enteros");
        }
    }
    
    return *this;
}

Numero& Entero::multiplicacion(const Numero& otro) {
    const Entero* otroEntero = dynamic_cast<const Entero*>(&otro);
    
    if (otroEntero) {
        valor *= otroEntero->getValor();
    } else {
        try {
            valor *= std::stoi(otro.toString());
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("No se puede multiplicar: el valor '" + otro.toString() + "' no es convertible a entero");
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("No se puede multiplicar: el valor '" + otro.toString() + "' está fuera del rango permitido para enteros");
        }
    }
    
    return *this; 
}

Numero& Entero::division(const Numero& otro) {
    const Entero* otroEntero = dynamic_cast<const Entero*>(&otro);
    
    int divisor = 0;
    if (otroEntero) {
        divisor = otroEntero->getValor();
    } else {
        try {
            divisor = std::stoi(otro.toString());
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("No se puede dividir: el valor '" + otro.toString() + "' no es convertible a entero");
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("No se puede dividir: el valor '" + otro.toString() + "' está fuera del rango permitido para enteros");
        }
    }
    
    if (divisor == 0) {
        throw std::invalid_argument("Error matemático: división por cero");
    }
    
    valor /= divisor;
    return *this;
}

std::string Entero::toString() const {
    return std::to_string(valor);
}

// Implementación de la clase Real
Real::Real() : valor(0.0) {}

Real::Real(double val) : valor(val) {}

double Real::getValor() const {
    return valor;
}

Numero& Real::suma(const Numero& otro) {
    const Real* otroReal = dynamic_cast<const Real*>(&otro);
    
    if (otroReal) {
        valor += otroReal->getValor();
    } else {
        try {
            valor += std::stod(otro.toString());
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("No se puede sumar: el valor '" + otro.toString() + "' no es convertible a número real");
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("No se puede sumar: el valor '" + otro.toString() + "' está fuera del rango permitido para reales");
        }
    }
    
    return *this;
}

Numero& Real::resta(const Numero& otro) {
    const Real* otroReal = dynamic_cast<const Real*>(&otro);
    
    if (otroReal) {
        valor -= otroReal->getValor();
    } else {
        try {
            valor -= std::stod(otro.toString());
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("No se puede restar: el valor '" + otro.toString() + "' no es convertible a número real");
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("No se puede restar: el valor '" + otro.toString() + "' está fuera del rango permitido para reales");
        }
    }
    
    return *this;
}

Numero& Real::multiplicacion(const Numero& otro) {
    const Real* otroReal = dynamic_cast<const Real*>(&otro);
    
    if (otroReal) {
        valor *= otroReal->getValor();
    } else {
        try {
            valor *= std::stod(otro.toString());
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("No se puede multiplicar: el valor '" + otro.toString() + "' no es convertible a número real");
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("No se puede multiplicar: el valor '" + otro.toString() + "' está fuera del rango permitido para reales");
        }
    }
    
    return *this;
}

Numero& Real::division(const Numero& otro) {
    const Real* otroReal = dynamic_cast<const Real*>(&otro);
    
    double divisor = 0.0;
    if (otroReal) {
        divisor = otroReal->getValor();
    } else {
        try {
            divisor = std::stod(otro.toString());
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("No se puede dividir: el valor '" + otro.toString() + "' no es convertible a número real");
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("No se puede dividir: el valor '" + otro.toString() + "' está fuera del rango permitido para reales");
        }
    }
    
    if (divisor == 0.0) {
        throw std::invalid_argument("Error matemático: división por cero");
    }
    
    valor /= divisor;
    return *this;
}

std::string Real::toString() const {
    // Formato con 2 decimales
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2) << valor;
    return ss.str();
}

// Implementación de la clase Complejo
Complejo::Complejo() : real(0.0), imaginario(0.0) {}

Complejo::Complejo(double r, double i) : real(r), imaginario(i) {}

double Complejo::getReal() const {
    return real;
}

double Complejo::getImaginario() const {
    return imaginario;
}

Numero& Complejo::suma(const Numero& otro) {
    const Complejo* otroComplejo = dynamic_cast<const Complejo*>(&otro);
    
    if (otroComplejo) {
        real += otroComplejo->getReal();
        imaginario += otroComplejo->getImaginario();
    } else {
        // Si no es un complejo, intentamos interpretar como un real que afecta solo a la parte real
        try {
            real += std::stod(otro.toString());
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("No se puede sumar: el valor '" + otro.toString() + "' no es convertible a número complejo");
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("No se puede sumar: el valor '" + otro.toString() + "' está fuera del rango permitido");
        }
    }
    
    return *this;
}

Numero& Complejo::resta(const Numero& otro) {
    const Complejo* otroComplejo = dynamic_cast<const Complejo*>(&otro);
    
    if (otroComplejo) {
        real -= otroComplejo->getReal();
        imaginario -= otroComplejo->getImaginario();
    } else {
        try {
            real -= std::stod(otro.toString());
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("No se puede restar: el valor '" + otro.toString() + "' no es convertible a número complejo");
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("No se puede restar: el valor '" + otro.toString() + "' está fuera del rango permitido");
        }
    }
    
    return *this;
}

Numero& Complejo::multiplicacion(const Numero& otro) {
    const Complejo* otroComplejo = dynamic_cast<const Complejo*>(&otro);
    
    if (otroComplejo) {
        // (a+bi)(c+di) = Parte Real: (ac-bd) + Parte Imaginaria: (ad+bc)i
        double nuevoReal = real * otroComplejo->getReal() - imaginario * otroComplejo->getImaginario();
        double nuevoImaginario = real * otroComplejo->getImaginario() + imaginario * otroComplejo->getReal();
        
        real = nuevoReal;
        imaginario = nuevoImaginario;
    } else {
        try {
            double escalar = std::stod(otro.toString());
            real *= escalar;
            imaginario *= escalar;
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("No se puede multiplicar: el valor '" + otro.toString() + "' no es convertible a número complejo");
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("No se puede multiplicar: el valor '" + otro.toString() + "' está fuera del rango permitido");
        }
    }
    
    return *this;
}

Numero& Complejo::division(const Numero& otro) {
    const Complejo* otroComplejo = dynamic_cast<const Complejo*>(&otro);
    
    if (otroComplejo) {
        double c = otroComplejo->getReal();
        double d = otroComplejo->getImaginario();
        
        // Verificar si el divisor es cero
        if (c*c + d*d == 0) {
            throw std::invalid_argument("Error matemático: división por cero complejo");
        }
        
        // (a+bi)/(c+di) = ((ac+bd)/(c²+d²)) + ((bc-ad)/(c²+d²))i
        double denominador = c*c + d*d;
        double nuevoReal = (real*c + imaginario*d) / denominador;
        double nuevoImaginario = (imaginario*c - real*d) / denominador;
        
        real = nuevoReal;
        imaginario = nuevoImaginario;
    } else {
        try {
            double escalar = std::stod(otro.toString());
            
            if (escalar == 0.0) {
                throw std::invalid_argument("Error matemático: división por cero");
            }
            
            real /= escalar;
            imaginario /= escalar;
        } catch (const std::invalid_argument& e) {
            if (e.what() == std::string("Error matemático: división por cero")) {
                throw; // Relanzar la excepción de división por cero sin modificar
            }
            throw std::invalid_argument("No se puede dividir: el valor '" + otro.toString() + "' no es convertible a número complejo");
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("No se puede dividir: el valor '" + otro.toString() + "' está fuera del rango permitido");
        }
    }
    
    return *this;
}

std::string Complejo::toString() const {
    std::ostringstream ss; 
    ss << std::fixed << std::setprecision(2); // fixed y setprecision para formato decimal
    
    ss << real;
    
    if (imaginario >= 0) {
        ss << " + " << imaginario << "i";
    } else {
        ss << " - " << -imaginario << "i";
    }
    
    return ss.str();
}

//==============================================
// FUNCIONES DE PRUEBA
//==============================================

/**
 * @brief Función para probar operaciones con números enteros
 */
void probarEnteros() {
    std::cout << "\nPRUEBA DE NÚMEROS ENTEROS" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Entero a(10);
    Entero b(5);
    
    std::cout << "a = " << a.toString() << std::endl;
    std::cout << "b = " << b.toString() << std::endl;
    
    // Prueba de suma
    try {
        Entero suma = static_cast<Entero&>(a.suma(b));
        std::cout << "a + b = " << suma.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en suma: " << e.what() << std::endl;
    }
    
    // Prueba de resta
    try {
        Entero resta(10);
        resta.resta(b);
        std::cout << "10 - b = " << resta.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en resta: " << e.what() << std::endl;
    }
    
    // Prueba de multiplicación
    try {
        Entero mult(10);
        mult.multiplicacion(b);
        std::cout << "10 * b = " << mult.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en multiplicación: " << e.what() << std::endl;
    }
    
    // Prueba de división
    try {
        Entero div(10);
        div.division(b);
        std::cout << "10 / b = " << div.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en división: " << e.what() << std::endl;
    }
    
    // Prueba de división por cero
    try {
        Entero div2(10);
        Entero cero(0);
        div2.division(cero);
        std::cout << "10 / 0 = " << div2.toString() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Error (esperado): " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error inesperado: " << e.what() << std::endl;
    }
    
    // Prueba de operación con tipo incompatible
    try {
        Entero ent(10);
        Complejo comp(2, 3);
        ent.suma(comp);
        std::cout << "10 + (2+3i) = " << ent.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error (esperado con tipo incompatible): " << e.what() << std::endl;
    }
    
    // Prueba con números negativos
    try {
        Entero neg1(-5);
        Entero neg2(-3);
        Entero res = static_cast<Entero&>(neg1.suma(neg2));
        std::cout << "-5 + -3 = " << res.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en suma de negativos: " << e.what() << std::endl;
    }
    
    // Prueba con números grandes
    try {
        Entero grande1(1000000);
        Entero grande2(2000000);
        Entero res = static_cast<Entero&>(grande1.multiplicacion(grande2));
        std::cout << "1000000 * 2000000 = " << res.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en multiplicación de grandes: " << e.what() << std::endl;
    }
}

/**
 * @brief Función para probar operaciones con números reales
 */
void probarReales() {
    std::cout << "\nPRUEBA DE NÚMEROS REALES" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Real a(10.5);
    Real b(3.25);
    
    std::cout << "a = " << a.toString() << std::endl;
    std::cout << "b = " << b.toString() << std::endl;
    
    // Prueba de suma
    try {
        Real suma = static_cast<Real&>(a.suma(b));
        std::cout << "a + b = " << suma.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en suma: " << e.what() << std::endl;
    }
    
    // Prueba de resta
    try {
        Real resta(10.5);
        resta.resta(b);
        std::cout << "10.5 - b = " << resta.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en resta: " << e.what() << std::endl;
    }
    
    // Prueba de multiplicación
    try {
        Real mult(10.5);
        mult.multiplicacion(b);
        std::cout << "10.5 * b = " << mult.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en multiplicación: " << e.what() << std::endl;
    }
    
    // Prueba de división
    try {
        Real div(10.5);
        div.division(b);
        std::cout << "10.5 / b = " << div.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en división: " << e.what() << std::endl;
    }
    
    // Prueba con entero (conversión implícita)
    try {
        Real real(5.5);
        Entero entero(2);
        real.suma(entero);
        std::cout << "5.5 + 2 = " << real.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en suma con entero: " << e.what() << std::endl;
    }
    
    // Prueba con números negativos
    try {
        Real neg1(-1.5);
        Real neg2(-2.5);
        Real res = static_cast<Real&>(neg1.multiplicacion(neg2));
        std::cout << "-1.5 * -2.5 = " << res.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en multiplicación de negativos: " << e.what() << std::endl;
    }
    
    // Prueba con números decimales pequeños
    try {
        Real pequeño1(0.0001);
        Real pequeño2(0.0002);
        Real res = static_cast<Real&>(pequeño1.division(pequeño2));
        std::cout << "0.0001 / 0.0002 = " << res.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en división de pequeños: " << e.what() << std::endl;
    }
    
    // Prueba con un número muy grande y otro muy pequeño
    try {
        Real grande(1000000.5);
        Real pequeño(0.00001);
        Real res = static_cast<Real&>(grande.multiplicacion(pequeño));
        std::cout << "1000000.5 * 0.00001 = " << res.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en multiplicación grande*pequeño: " << e.what() << std::endl;
    }
}

/**
 * @brief Función para probar operaciones con números complejos
 */
void probarComplejos() {
    std::cout << "\nPRUEBA DE NÚMEROS COMPLEJOS" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Complejo a(3.0, 4.0);  // 3 + 4i
    Complejo b(1.0, 2.0);  // 1 + 2i
    
    std::cout << "a = " << a.toString() << std::endl;
    std::cout << "b = " << b.toString() << std::endl;
    
    // Prueba de suma
    try {
        Complejo suma = static_cast<Complejo&>(a.suma(b));
        std::cout << "a + b = " << suma.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en suma: " << e.what() << std::endl;
    }
    
    // Prueba de resta
    try {
        Complejo resta(3.0, 4.0);
        resta.resta(b);
        std::cout << "(3 + 4i) - b = " << resta.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en resta: " << e.what() << std::endl;
    }
    
    // Prueba de multiplicación
    try {
        Complejo mult(3.0, 4.0);
        mult.multiplicacion(b);
        std::cout << "(3 + 4i) * b = " << mult.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en multiplicación: " << e.what() << std::endl;
    }
    
    // Prueba de división
    try {
        Complejo div(3.0, 4.0);
        div.division(b);
        std::cout << "(3 + 4i) / b = " << div.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en división: " << e.what() << std::endl;
    }
    
    // Prueba de división por cero complejo
    try {
        Complejo div2(3.0, 4.0);
        Complejo cero(0.0, 0.0);
        div2.division(cero);
        std::cout << "(3 + 4i) / (0 + 0i) = " << div2.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error (esperado): " << e.what() << std::endl;
    }
    
    // Prueba de operaciones con números reales
    try {
        Complejo c(5.0, 6.0);
        Real r(2.0);
        
        std::cout << "\nOperaciones entre complejo y real:" << std::endl;
        std::cout << "c = " << c.toString() << std::endl;
        std::cout << "r = " << r.toString() << std::endl;
        
        Complejo multCR = static_cast<Complejo&>(c.multiplicacion(r));
        std::cout << "c * r = " << multCR.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en operación con real: " << e.what() << std::endl;
    }
    
    // Prueba de complejos con parte imaginaria negativa
    try {
        Complejo c1(2.0, -3.0);
        Complejo c2(1.0, -1.0);
        std::cout << "\nOperaciones con imaginarios negativos:" << std::endl;
        std::cout << "c1 = " << c1.toString() << std::endl;
        std::cout << "c2 = " << c2.toString() << std::endl;
        
        Complejo resSuma = static_cast<Complejo&>(c1.suma(c2));
        std::cout << "c1 + c2 = " << resSuma.toString() << std::endl;
        
        Complejo resMult = static_cast<Complejo&>(c1.multiplicacion(c2));
        std::cout << "c1 * c2 = " << resMult.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en operación con imaginarios negativos: " << e.what() << std::endl;
    }
    
    // Prueba de complejos puros (solo parte imaginaria)
    try {
        Complejo imaginario1(0.0, 5.0);
        Complejo imaginario2(0.0, 2.0);
        std::cout << "\nOperaciones con imaginarios puros:" << std::endl;
        std::cout << "i1 = " << imaginario1.toString() << std::endl;
        std::cout << "i2 = " << imaginario2.toString() << std::endl;
        
        Complejo resMult = static_cast<Complejo&>(imaginario1.multiplicacion(imaginario2));
        std::cout << "i1 * i2 = " << resMult.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en operación con imaginarios puros: " << e.what() << std::endl;
    }
    
    // Prueba de complejos reales puros (solo parte real)
    try {
        Complejo real1(3.0, 0.0);
        Complejo real2(4.0, 0.0);
        std::cout << "\nOperaciones con complejos de solo parte real:" << std::endl;
        std::cout << "r1 = " << real1.toString() << std::endl;
        std::cout << "r2 = " << real2.toString() << std::endl;
        
        Complejo resDiv = static_cast<Complejo&>(real1.division(real2));
        std::cout << "r1 / r2 = " << resDiv.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en operación con complejos reales puros: " << e.what() << std::endl;
    }
}

/**
 * @brief Función para probar operaciones con tipos incompatibles
 */
void probarTiposIncompatibles() {
    std::cout << "\nPRUEBA DE OPERACIONES CON TIPOS INCOMPATIBLES" << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Intentar sumar un complejo a un entero
    try {
        Entero ent(10);
        Complejo comp(3, 4);
        std::cout << "Intentando: " << ent.toString() << " + " << comp.toString() << std::endl;
        ent.suma(comp);
        std::cout << "Resultado: " << ent.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error capturado: " << e.what() << std::endl;
    }
    
    // Intentar dividir un real por una cadena no numérica
    class NumeroInvalido : public Numero {
    public:
        Numero& suma(const Numero& otro) override { return *this; }
        Numero& resta(const Numero& otro) override { return *this; }
        Numero& multiplicacion(const Numero& otro) override { return *this; }
        Numero& division(const Numero& otro) override { return *this; }
        std::string toString() const override { return "no_soy_un_numero"; }
    };
    
    try {
        Real real(5.5);
        NumeroInvalido invalido;
        std::cout << "Intentando: " << real.toString() << " / " << invalido.toString() << std::endl;
        real.division(invalido);
        std::cout << "Resultado: " << real.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error capturado: " << e.what() << std::endl;
    }
    
    // Intentar operaciones con un número fuera de rango
    class NumeroDesbordado : public Numero {
    public:
        Numero& suma(const Numero& otro) override { return *this; }
        Numero& resta(const Numero& otro) override { return *this; }
        Numero& multiplicacion(const Numero& otro) override { return *this; }
        Numero& division(const Numero& otro) override { return *this; }
        std::string toString() const override { 
            return "9999999999999999999999999999999999999999999999999"; 
        }
    };
    
    try {
        Entero ent(10);
        NumeroDesbordado desbordado;
        std::cout << "Intentando: " << ent.toString() << " + " << desbordado.toString() << std::endl;
        ent.suma(desbordado);
        std::cout << "Resultado: " << ent.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error capturado (esperado): " << e.what() << std::endl;
    }
    
    // Prueba con caracteres especiales
    class NumeroEspecial : public Numero {
    public:
        Numero& suma(const Numero& otro) override { return *this; }
        Numero& resta(const Numero& otro) override { return *this; }
        Numero& multiplicacion(const Numero& otro) override { return *this; }
        Numero& division(const Numero& otro) override { return *this; }
        std::string toString() const override { return "@#$%^&*"; }
    };
    
    try {
        Real real(2.5);
        NumeroEspecial especial;
        std::cout << "Intentando: " << real.toString() << " * " << especial.toString() << std::endl;
        real.multiplicacion(especial);
        std::cout << "Resultado: " << real.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error capturado (esperado): " << e.what() << std::endl;
    }
}

/**
 * @brief Función para probar operaciones mezcladas entre diferentes tipos
 */
void probarOperacionesMezcladas() {
    std::cout << "\nPRUEBA DE OPERACIONES MEZCLADAS ENTRE TIPOS" << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Operaciones mezcladas: Entero con Real
    try {
        Entero ent(5);
        Real real(2.5);
        
        std::cout << "Operaciones entre entero y real:" << std::endl;
        std::cout << "ent = " << ent.toString() << std::endl;
        std::cout << "real = " << real.toString() << std::endl;
        
        // Entero + Real
        Entero resEntero = static_cast<Entero&>(ent.suma(real));
        std::cout << "ent + real = " << resEntero.toString() << " (como Entero)" << std::endl;
        
        // Real + Entero
        Real resReal = static_cast<Real&>(real.suma(ent));
        std::cout << "real + ent = " << resReal.toString() << " (como Real)" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en operaciones Entero-Real: " << e.what() << std::endl;
    }
    
    // Operaciones mezcladas: Real con Complejo
    try {
        Real real(3.5);
        Complejo comp(2.0, 1.0);
        
        std::cout << "\nOperaciones entre real y complejo:" << std::endl;
        std::cout << "real = " << real.toString() << std::endl;
        std::cout << "comp = " << comp.toString() << std::endl;
        
        // Real * Complejo (esto probablemente falle debido a la parte imaginaria)
        try {
            Real resReal = static_cast<Real&>(real.multiplicacion(comp));
            std::cout << "real * comp = " << resReal.toString() << " (como Real)" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error esperado (Real*Complejo): " << e.what() << std::endl;
        }
        
        // Complejo * Real
        Complejo resComp = static_cast<Complejo&>(comp.multiplicacion(real));
        std::cout << "comp * real = " << resComp.toString() << " (como Complejo)" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en operaciones Real-Complejo: " << e.what() << std::endl;
    }
    
    // Operaciones mezcladas: Entero con Complejo
    try {
        Entero ent(4);
        Complejo comp(1.0, 3.0);
        
        std::cout << "\nOperaciones entre entero y complejo:" << std::endl;
        std::cout << "ent = " << ent.toString() << std::endl;
        std::cout << "comp = " << comp.toString() << std::endl;
        
        // Entero / Complejo (probablemente falle)
        try {
            Entero resEnt = static_cast<Entero&>(ent.division(comp));
            std::cout << "ent / comp = " << resEnt.toString() << " (como Entero)" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error esperado (Entero/Complejo): " << e.what() << std::endl;
        }
        
        // Complejo - Entero
        Complejo resComp = static_cast<Complejo&>(comp.resta(ent));
        std::cout << "comp - ent = " << resComp.toString() << " (como Complejo)" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en operaciones Entero-Complejo: " << e.what() << std::endl;
    }
}

/**
 * @brief Función que ejecuta todas las pruebas
 */
void ejecutarPruebas() {
    probarEnteros();
    probarReales();
    probarComplejos();
    probarTiposIncompatibles();
    probarOperacionesMezcladas();
}
