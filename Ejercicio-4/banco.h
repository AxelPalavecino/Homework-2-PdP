#pragma once

#include <string>
#include <iostream>

// Declaración forward de CajaDeAhorro para uso en friend
class CajaDeAhorro;

/**
 * @class CuentaBanco
 * @brief Clase abstracta base para representar una cuenta bancaria genérica
 */
class CuentaBanco {
private:
    double balance;
    /**
     * @brief Muestra la información de la cuenta (método virtual puro)
     * @return void
     */
    virtual void mostrarInfo() const = 0;

protected:
    std::string titularCuenta;

public:
    /**
     * @brief Constructor de la clase CuentaBanco
     * @param titular Nombre del titular de la cuenta
     * @param saldoInicial Saldo inicial de la cuenta (por defecto 0.0)
     */
    CuentaBanco(const std::string& titular, double saldoInicial = 0.0);
    
    /**
     * @brief Destructor virtual de la clase CuentaBanco
     */
    virtual ~CuentaBanco() = default;
    
    /**
     * @brief Deposita una cantidad de dinero en la cuenta
     * @param monto Cantidad a depositar
     * @return void
     */
    void depositar(double monto);
    
    /**
     * @brief Retira una cantidad de dinero de la cuenta (método virtual puro)
     * @param monto Cantidad a retirar
     * @return bool Indica si la operación fue exitosa
     */
    virtual bool retirar(double monto) = 0;
    
    /**
     * @brief Obtiene el balance actual de la cuenta
     * @return double Balance actual
     */
    double getBalance() const;
    
    /**
     * @brief Obtiene el nombre del titular de la cuenta
     * @return std::string Nombre del titular
     */
    std::string getTitular() const;
    
    /**
     * @brief Método público para mostrar información (llama al método privado)
     * @return void
     */
    void mostrar() const;
    
    /**
     * @brief Aplica una comisión o cargo al balance, seguro para usar desde métodos const
     * @param monto Cantidad a reducir del balance
     */
    void applyFee(double monto) const;
    
protected:
    /**
     * @brief Establece el balance de la cuenta
     * @param nuevoBalance Nuevo valor del balance
     */
    void setBalance(double nuevoBalance);  // Reverted to non-const
};

/**
 * @class CajaDeAhorro
 * @brief Clase que representa una caja de ahorro
 */
class CajaDeAhorro : public CuentaBanco {
private:
    mutable int contadorMostrarInfo;    // Contador para aplicar descuento
                                        // mutable para poder modificar en un método const
    
    /**
     * @brief Implementación de mostrarInfo para CajaDeAhorro
     * @return void
     */
    void mostrarInfo() const override;

public:
    /**
     * @brief Constructor de la clase CajaDeAhorro
     * @param titular Nombre del titular de la cuenta
     * @param saldoInicial Saldo inicial de la cuenta (por defecto 0.0)
     */
    CajaDeAhorro(const std::string& titular, double saldoInicial = 0.0);
    
    /**
     * @brief Implementación de retirar para CajaDeAhorro
     * @param monto Cantidad a retirar
     * @return bool True si el retiro fue exitoso, false en caso contrario
     */
    bool retirar(double monto) override;
    
    // Friend para que CuentaCorriente pueda acceder a los datos privados
    friend class CuentaCorriente;
};

/**
 * @class CuentaCorriente
 * @brief Clase que representa una cuenta corriente
 */
class CuentaCorriente : public CuentaBanco {
private:

    CajaDeAhorro& cajaAhorro; // Referencia a la caja de ahorro asociada
    
    /**
     * @brief Implementación de mostrarInfo para CuentaCorriente
     * @return void
     */
    void mostrarInfo() const override;

public:
    /**
     * @brief Constructor de la clase CuentaCorriente
     * @param titular Nombre del titular de la cuenta
     * @param caja Referencia a una CajaDeAhorro asociada
     * @param saldoInicial Saldo inicial de la cuenta (por defecto 0.0)
     */
    CuentaCorriente(const std::string& titular, CajaDeAhorro& caja, double saldoInicial = 0.0);
    
    /**
     * @brief Implementación de retirar para CuentaCorriente
     * @param monto Cantidad a retirar
     * @return bool True si el retiro fue exitoso, false en caso contrario
     */
    bool retirar(double monto) override;
};

/**
 * @brief Función para probar el sistema bancario
 */
void testSistemaBancario();