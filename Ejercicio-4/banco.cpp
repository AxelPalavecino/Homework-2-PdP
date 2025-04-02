#include "banco.h"
#include <iostream>

// CuentaBanco

CuentaBanco::CuentaBanco(const std::string& titular, double saldoInicial): 
    balance(saldoInicial), titularCuenta(titular) {}

void CuentaBanco::depositar(double monto) {
    if (monto > 0) {
        balance += monto;
        std::cout << "Se depositaron $" << monto << " en la cuenta de " << titularCuenta << std::endl;
    } else {
        std::cout << "El monto a depositar debe ser positivo." << std::endl;
    }
}

double CuentaBanco::getBalance() const {
    return balance;
}

std::string CuentaBanco::getTitular() const {
    return titularCuenta;
}

void CuentaBanco::mostrar() const {
    mostrarInfo();
}

void CuentaBanco::setBalance(double nuevoBalance) {
    balance = nuevoBalance;
}

void CuentaBanco::applyFee(double monto) const {
    // Aqui utilizamos const_cast para modificar el balance, ya que applyFee es un método const
    if (monto <= 0) {
        std::cout << "El monto a aplicar como descuento debe ser positivo." << std::endl;
        return;
    }
    if (monto > balance) {
        std::cout << "No se puede aplicar un descuento mayor al balance." << std::endl;
        return;
    }
    CuentaBanco* nonConstThis = const_cast<CuentaBanco*>(this);
    nonConstThis->balance -= monto;
}


// Caja de ahorro

CajaDeAhorro::CajaDeAhorro(const std::string& titular, double saldoInicial)
    : CuentaBanco(titular, saldoInicial), contadorMostrarInfo(0) {
}

bool CajaDeAhorro::retirar(double monto) {
    if (monto <= 0) {
        std::cout << "El monto a retirar debe ser positivo." << std::endl;
        return false;
    }
    
    if (monto > getBalance()) {
        std::cout << "Fondos insuficientes en la Caja de Ahorro." << std::endl;
        return false;
    }
    
    // Si hay suficientes fondos, retiramos el dinero
    setBalance(getBalance() - monto);
    std::cout << "Se retiraron $" << monto << " de la Caja de Ahorro de " << getTitular() << std::endl;
    return true;
}

void CajaDeAhorro::mostrarInfo() const {
    contadorMostrarInfo++;
    
    std::cout << "--- Información de Caja de Ahorro ---" << std::endl;
    std::cout << "Titular: " << getTitular() << std::endl;
    std::cout << "Balance: $" << getBalance() << std::endl;
    
    // Aplica descuento después de mostrar la información más de 2 veces
    if (contadorMostrarInfo > 2) {
        applyFee(20);  // Using the new applyFee method instead of setBalance
        std::cout << "Se aplicó un descuento de $20 por consulta. Nuevo balance: $" << getBalance() << std::endl;
    }
}

// ========== Implementación de CuentaCorriente ==========

CuentaCorriente::CuentaCorriente(const std::string& titular, CajaDeAhorro& caja, double saldoInicial)
    : CuentaBanco(titular, saldoInicial), cajaAhorro(caja) {
}

bool CuentaCorriente::retirar(double monto) {
    if (monto <= 0) {
        std::cout << "El monto a retirar debe ser positivo." << std::endl;
        return false;
    }
    if (monto <= getBalance()) {
        setBalance(getBalance() - monto);
        std::cout << "Se retiraron $" << monto << " de la Cuenta Corriente de " << getTitular() << std::endl;
        return true;
    }
    
    if (monto <= cajaAhorro.getBalance()) {
        // Acceso directo al balance de cajaAhorro usando friend
        cajaAhorro.setBalance(cajaAhorro.getBalance() - monto);
        std::cout << "Fondos insuficientes en Cuenta Corriente. Se retiraron $" << monto 
                  << " de la Caja de Ahorro de " << cajaAhorro.getTitular() << std::endl;
        return true;
    }
    
    std::cout << "Fondos insuficientes en ambas cuentas. No se puede realizar el retiro." << std::endl;
    return false;
}

void CuentaCorriente::mostrarInfo() const {
    std::cout << "--- Información de Cuenta Corriente ---" << std::endl;
    std::cout << "Titular: " << getTitular() << std::endl;
    std::cout << "Balance: $" << getBalance() << std::endl;
    std::cout << "Vinculada a Caja de Ahorro de: " << cajaAhorro.getTitular() << std::endl;
}

// Función de prueba del sistema bancario
void testSistemaBancario() {
    std::cout << "\n=====================================================" << std::endl;
    std::cout << "             PRUEBA DEL SISTEMA BANCARIO              " << std::endl;
    std::cout << "=====================================================" << std::endl;
    
    // PARTE 1: Creación de cuentas
    std::cout << "\n===== CREACIÓN DE CUENTAS =====" << std::endl;
    CajaDeAhorro caja("Juan Pérez", 1000);
    std::cout << "✓ Caja de Ahorro creada para " << caja.getTitular() << " con $" << caja.getBalance() << std::endl;
    
    CuentaCorriente corriente("Juan Pérez", caja, 500);
    std::cout << "✓ Cuenta Corriente creada para " << corriente.getTitular() << " con $" << corriente.getBalance() << std::endl;
    
    // PARTE 2: Operaciones básicas
    std::cout << "\n===== OPERACIONES BÁSICAS =====" << std::endl;
    
    // Mostrar información inicial
    std::cout << "\n>> Información inicial:" << std::endl;
    caja.mostrar();
    corriente.mostrar();
    
    // Realizar depósitos
    std::cout << "\n>> Realizando depósitos:" << std::endl;
    caja.depositar(200);     // Saldo: 1200
    corriente.depositar(300); // Saldo: 800
    
    std::cout << "\n>> Información post-depósito:" << std::endl;
    std::cout << "Caja de Ahorro: $" << caja.getBalance() << std::endl;
    std::cout << "Cuenta Corriente: $" << corriente.getBalance() << std::endl;
    
    // Realizar retiros exitosos
    std::cout << "\n>> Realizando retiros válidos:" << std::endl;
    bool retiroCaja = caja.retirar(100);          // Saldo: 1100
    std::cout << "Retiro de Caja de Ahorro " << (retiroCaja ? "exitoso" : "fallido") << std::endl;
    
    bool retiroCorriente = corriente.retirar(200); // Saldo: 600
    std::cout << "Retiro de Cuenta Corriente " << (retiroCorriente ? "exitoso" : "fallido") << std::endl;
    
    std::cout << "\n>> Información post-retiro válido:" << std::endl;
    std::cout << "Caja de Ahorro: $" << caja.getBalance() << std::endl;
    std::cout << "Cuenta Corriente: $" << corriente.getBalance() << std::endl;
    
    // PARTE 3: Escenarios especiales
    std::cout << "\n===== ESCENARIOS ESPECIALES =====" << std::endl;
    
    // Escenario 1: Retiro que excede balance de caja de ahorro
    std::cout << "\n>> Escenario 1: Retiro que excede balance de Caja de Ahorro" << std::endl;
    retiroCaja = caja.retirar(2000);
    std::cout << "Retiro de $2000 de Caja de Ahorro " << (retiroCaja ? "exitoso" : "fallido") << std::endl;
    std::cout << "Balance actual de Caja de Ahorro: $" << caja.getBalance() << std::endl;
    
    // Escenario 2: Retiro de cuenta corriente usando fondos de caja de ahorro
    std::cout << "\n>> Escenario 2: Retiro de Cuenta Corriente usando fondos de Caja de Ahorro" << std::endl;
    retiroCorriente = corriente.retirar(700); // Corriente: 600, se usan 100 de Caja
    std::cout << "Retiro de $700 de Cuenta Corriente " << (retiroCorriente ? "exitoso" : "fallido") << std::endl;
    std::cout << "Balance actual de Cuenta Corriente: $" << corriente.getBalance() << std::endl;
    std::cout << "Balance actual de Caja de Ahorro: $" << caja.getBalance() << std::endl;
    
    // Escenario 3: Retiro cuando no hay fondos en ninguna cuenta
    std::cout << "\n>> Escenario 3: Retiro cuando no hay fondos suficientes en ambas cuentas" << std::endl;
    // Primero agotamos los fondos
    caja.retirar(caja.getBalance() - 50); // Dejamos solo 50 en la caja
    corriente.retirar(corriente.getBalance() - 50); // Dejamos solo 50 en la corriente
    
    std::cout << "Balances reducidos para prueba:" << std::endl;
    std::cout << "Caja de Ahorro: $" << caja.getBalance() << std::endl;
    std::cout << "Cuenta Corriente: $" << corriente.getBalance() << std::endl;
    
    // Intentamos retirar más de lo disponible en ambas cuentas
    retiroCorriente = corriente.retirar(200);
    std::cout << "Retiro de $200 cuando hay fondos insuficientes: " << (retiroCorriente ? "exitoso" : "fallido") << std::endl;
    
    // PARTE 4: Verificación de descuento por consulta
    std::cout << "\n===== VERIFICACIÓN DE DESCUENTO POR CONSULTA =====" << std::endl;
    std::cout << "\n>> Primera consulta (ya se hizo una al inicio):" << std::endl;
    caja.mostrar();
    
    std::cout << "\n>> Segunda consulta (límite antes del descuento):" << std::endl;
    caja.mostrar();
    
    std::cout << "\n>> Tercera consulta (se aplica descuento de $20):" << std::endl;
    caja.mostrar();
    
    std::cout << "\n>> Cuarta consulta (se aplica otro descuento de $20):" << std::endl;
    caja.mostrar();
    
    std::cout << "\n=====================================================" << std::endl;
    std::cout << "             PRUEBA FINALIZADA                        " << std::endl;
    std::cout << "=====================================================" << std::endl;
}
