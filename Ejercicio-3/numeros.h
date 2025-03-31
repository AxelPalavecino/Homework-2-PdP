#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std; 

/**
 * @brief Interfaz que define operaciones básicas para diferentes tipos de números
 */
class Numero {
public:
    virtual Numero& suma(const Numero& otro) = 0;
    virtual Numero& resta(const Numero& otro) = 0;
    virtual Numero& multiplicacion(const Numero& otro) = 0;
    virtual Numero& division(const Numero& otro) = 0;
    virtual std::string toString() const = 0;
    virtual ~Numero() = default;
};

/**
 * @brief Clase que implementa operaciones para números enteros
 */
class Entero : public Numero {
    private:
        int valor;
    
public:
    /**
     * @brief Constructor predeterminado
     */
    Entero();
    
    /**
     * @brief Constructor con valor inicial
     * @param val Valor entero inicial
     */
    explicit Entero(int val);
    
    /**
     * @brief Obtener el valor entero
     * @return Valor entero almacenado
     */
    int getValor() const;
    
    /**
     * @brief Suma este entero con otro número
     * @param otro Número a sumar
     * @return Referencia a este objeto modificado
     */
    Numero& suma(const Numero& otro) override; // Como vimos en la clase, override no hace nada, solo es una palabra clave para indicar que la función está sobreescribiendo una función virtual de la clase base
    
    /**
     * @brief Resta otro número de este entero
     * @param otro Número a restar
     * @return Referencia a este objeto modificado
     */
    Numero& resta(const Numero& otro) override;
    
    /**
     * @brief Multiplica este entero por otro número
     * @param otro Número por el cual multiplicar
     * @return Referencia a este objeto modificado
     */
    Numero& multiplicacion(const Numero& otro) override;
    
    /**
     * @brief Divide este entero por otro número
     * @param otro Número por el cual dividir
     * @return Referencia a este objeto modificado
     * @throws std::invalid_argument si el divisor es cero
     */
    Numero& division(const Numero& otro) override;
    
    /**
     * @brief Convierte el entero a string
     * @return Representación del entero como string
     */
    std::string toString() const override;
};

/**
 * @brief Clase que implementa operaciones para números reales
 */
class Real : public Numero {
private:
    double valor;
    
public:
    /**
     * @brief Constructor predeterminado
     */
    Real();
    
    /**
     * @brief Constructor con valor inicial
     * @param val Valor real inicial
     */
    explicit Real(double val);
    
    /**
     * @brief Obtener el valor real
     * @return Valor real almacenado
     */
    double getValor() const;
    
    /**
     * @brief Suma este real con otro número
     * @param otro Número a sumar
     * @return Referencia a este objeto modificado
     */
    Numero& suma(const Numero& otro) override;
    
    /**
     * @brief Resta otro número de este real
     * @param otro Número a restar
     * @return Referencia a este objeto modificado
     */
    Numero& resta(const Numero& otro) override;
    
    /**
     * @brief Multiplica este real por otro número
     * @param otro Número por el cual multiplicar
     * @return Referencia a este objeto modificado
     */
    Numero& multiplicacion(const Numero& otro) override;
    
    /**
     * @brief Divide este real por otro número
     * @param otro Número por el cual dividir
     * @return Referencia a este objeto modificado
     * @throws std::invalid_argument si el divisor es cero
     */
    Numero& division(const Numero& otro) override;
    
    /**
     * @brief Convierte el real a string
     * @return Representación del real como string
     */
    std::string toString() const override;
};

/**
 * @brief Clase que implementa operaciones para números complejos
 */
class Complejo : public Numero {
private:
    double real;
    double imaginario;
    
public:
    /**
     * @brief Constructor predeterminado
     */
    Complejo();
    
    /**
     * @brief Constructor con valores iniciales
     * @param r Parte real
     * @param i Parte imaginaria
     */
    Complejo(double r, double i);
    
    /**
     * @brief Obtener la parte real
     * @return Parte real del número complejo
     */
    double getReal() const;
    
    /**
     * @brief Obtener la parte imaginaria
     * @return Parte imaginaria del número complejo
     */
    double getImaginario() const;
    
    /**
     * @brief Suma este complejo con otro número
     * @param otro Número a sumar
     * @return Referencia a este objeto modificado
     */
    Numero& suma(const Numero& otro) override;
    
    /**
     * @brief Resta otro número de este complejo
     * @param otro Número a restar
     * @return Referencia a este objeto modificado
     */
    Numero& resta(const Numero& otro) override;
    
    /**
     * @brief Multiplica este complejo por otro número
     * @param otro Número por el cual multiplicar
     * @return Referencia a este objeto modificado
     */
    Numero& multiplicacion(const Numero& otro) override;
    
    /**
     * @brief Divide este complejo por otro número
     * @param otro Número por el cual dividir
     * @return Referencia a este objeto modificado
     * @throws std::invalid_argument si el divisor es cero
     */
    Numero& division(const Numero& otro) override;
    
    /**
     * @brief Convierte el complejo a string
     * @return Representación del complejo como string
     */
    std::string toString() const override;
};

// Añadir la declaración de las funciones de prueba al final del archivo
void probarEnteros();
void probarReales();
void probarComplejos();
void probarTiposIncompatibles();
void probarOperacionesMezcladas();
void ejecutarPruebas();

