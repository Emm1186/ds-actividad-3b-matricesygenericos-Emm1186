#include <iostream>
#include "MatrizDinamica.h"

int main() {
    std::cout << "--- Sistema de Análisis de Transformaciones Lineales ---" << std::endl << std::endl;

    std::cout << ">> Prueba de Matriz ENTERA (Matriz A) <<" << std::endl;
    std::cout << "Creando Matriz A (Tipo INT) de 2x3..." << std::endl << std::endl;

    MatrizDinamica<int> A(2, 3);
    A.llenarMatriz();

    std::cout << "\nMatriz A original:" << std::endl;
    A.mostrar();

    // Redimensionar la matriz A
    std::cout << "\n>> Redimensionando Matriz A <<" << std::endl;
    std::cout << "Redimensionando A a 3x3..." << std::endl;
    A.redimensionar(3, 3);
    
    std::cout << "Matriz A después de redimensionar (nuevos valores en 0):" << std::endl;
    A.mostrar();

    // Matriz de (float)
    std::cout << "\n>> Prueba de Multiplicación (Tipo FLOAT) <<" << std::endl;
    std::cout << "Creando Matriz B (Tipo FLOAT) de 3x2..." << std::endl << std::endl;

    MatrizDinamica<float> B(3, 2);
    B.llenarMatriz();

    std::cout << "\nMatriz B:" << std::endl;
    B.mostrar();

    // Convertir A a float para poder multiplicar
    std::cout << "\nCreando Matriz A_float (copia de A en tipo float)..." << std::endl;
    MatrizDinamica<float> A_float(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A_float.setValor(i, j, (float)A.getValor(i, j));
        }
    }

    std::cout << "\n>> Calculando Multiplicación C = A × B <<" << std::endl;
    std::cout << "Matriz A_float (3x3) × Matriz B (3x2)..." << std::endl << std::endl;

    // Realizar la multiplicación
    MatrizDinamica<float> C = MatrizDinamica<float>::multiplicar(A_float, B);

    std::cout << "Matriz C (Resultado 3x2, Tipo FLOAT):" << std::endl;
    C.mostrar();

    // PRUEBA ADICIONAL: Multiplicación con matrices de tipo double
    std::cout << "\n>> Prueba Extra: Matrices de tipo DOUBLE <<" << std::endl;
    
    MatrizDinamica<double> D(2, 2);
    std::cout << "Creando Matriz D (2x2, tipo DOUBLE):" << std::endl;
    D.setValor(0, 0, 1.5);
    D.setValor(0, 1, 2.5);
    D.setValor(1, 0, 3.5);
    D.setValor(1, 1, 4.5);
    D.mostrar();

    MatrizDinamica<double> E(2, 2);
    std::cout << "\nCreando Matriz E (2x2, tipo DOUBLE):" << std::endl;
    E.setValor(0, 0, 2.0);
    E.setValor(0, 1, 1.0);
    E.setValor(1, 0, 1.5);
    E.setValor(1, 1, 2.0);
    E.mostrar();
    std::cout << "\nMultiplicando D × E..." << std::endl;
    MatrizDinamica<double> F = MatrizDinamica<double>::multiplicar(D, E);
    std::cout << "Resultado:" << std::endl;
    F.mostrar();

    std::cout << "\n>> Liberando memoria de todas las matrices... <<" << std::endl;
    std::cout << "(El destructor se llama automáticamente)" << std::endl;
    std::cout << "\nPrograma finalizado exitosamente." << std::endl;

    return 0;
}
