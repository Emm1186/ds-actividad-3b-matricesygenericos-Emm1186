#ifndef MATRIZDINAMICA_H
#define MATRIZDINAMICA_H

#include <iostream>
#include <iomanip>

// Clase genérica para manejar matrices dinámicas de cualquier tipo numérico
template <typename T>
class MatrizDinamica {
private:
    T** datos;      // Puntero doble para la matriz 2D
    int filas;      // Número de filas
    int columnas;   // Número de columnas

public:
    // CONSTRUCTOR: Crea la matriz y asigna memoria
    MatrizDinamica(int f, int c) {
        filas = f;
        columnas = c;
        
        // Paso 1: Crear el arreglo de punteros (las filas)
        datos = new T*[filas];
        
        // Paso 2: Para cada fila, crear un arreglo de datos (las columnas)
        for (int i = 0; i < filas; i++) {
            datos[i] = new T[columnas];
            
            // Inicializar todos los valores en 0
            for (int j = 0; j < columnas; j++) {
                datos[i][j] = 0;
            }
        }
    }

    // DESTRUCTOR: Libera toda la memoria para evitar fugas
    ~MatrizDinamica() {
        // Primero liberar cada fila (las columnas)
        for (int i = 0; i < filas; i++) {
            delete[] datos[i];
        }
        // Después liberar el arreglo de punteros (las filas)
        delete[] datos;
    }

    // CONSTRUCTOR DE COPIA: Necesario para copiar matrices correctamente
    MatrizDinamica(const MatrizDinamica& otra) {
        filas = otra.filas;
        columnas = otra.columnas;
        
        // Crear nueva memoria
        datos = new T*[filas];
        for (int i = 0; i < filas; i++) {
            datos[i] = new T[columnas];
            // Copiar los valores
            for (int j = 0; j < columnas; j++) {
                datos[i][j] = otra.datos[i][j];
            }
        }
    }

    // Método para obtener el número de filas
    int getFilas() const {
        return filas;
    }

    // Método para obtener el número de columnas
    int getColumnas() const {
        return columnas;
    }

    // Método para establecer un valor en una posición específica
    void setValor(int i, int j, T valor) {
        if (i >= 0 && i < filas && j >= 0 && j < columnas) {
            datos[i][j] = valor;
        }
    }

    // Método para obtener un valor de una posición específica
    T getValor(int i, int j) const {
        if (i >= 0 && i < filas && j >= 0 && j < columnas) {
            return datos[i][j];
        }
        return 0;
    }

    // MÉTODO DE REDIMENSIÓN: Cambia el tamaño de la matriz conservando datos
    void redimensionar(int nuevaF, int nuevaC) {
        // Paso 1: Crear una nueva matriz temporal con las nuevas dimensiones
        T** nuevaMatriz = new T*[nuevaF];
        for (int i = 0; i < nuevaF; i++) {
            nuevaMatriz[i] = new T[nuevaC];
            // Inicializar en 0
            for (int j = 0; j < nuevaC; j++) {
                nuevaMatriz[i][j] = 0;
            }
        }

        // Paso 2: Copiar los datos antiguos que quepan en la nueva matriz
        int filasACopiar = (filas < nuevaF) ? filas : nuevaF;
        int columnasACopiar = (columnas < nuevaC) ? columnas : nuevaC;
        
        for (int i = 0; i < filasACopiar; i++) {
            for (int j = 0; j < columnasACopiar; j++) {
                nuevaMatriz[i][j] = datos[i][j];
            }
        }

        // Paso 3: Liberar la memoria de la matriz antigua
        for (int i = 0; i < filas; i++) {
            delete[] datos[i];
        }
        delete[] datos;

        // Paso 4: Asignar la nueva matriz como la matriz actual
        datos = nuevaMatriz;
        filas = nuevaF;
        columnas = nuevaC;
    }

    // MÉTODO DE MULTIPLICACIÓN MATRICIAL: A × B = C
    static MatrizDinamica<T> multiplicar(const MatrizDinamica<T>& A, const MatrizDinamica<T>& B) {
        // Validación: El número de columnas de A debe ser igual al número de filas de B
        if (A.columnas != B.filas) {
            std::cout << "ERROR: No se pueden multiplicar. Dimensiones incompatibles." << std::endl;
            // Retornar una matriz vacía 1x1
            return MatrizDinamica<T>(1, 1);
        }

        // Crear la matriz resultado C con dimensiones: filas de A × columnas de B
        MatrizDinamica<T> C(A.filas, B.columnas);

        // Realizar la multiplicación usando la fórmula estándar
        // C[i][j] = suma de A[i][k] * B[k][j] para todos los k
        for (int i = 0; i < A.filas; i++) {
            for (int j = 0; j < B.columnas; j++) {
                T suma = 0;
                
                // Calcular el valor de C[i][j]
                for (int k = 0; k < A.columnas; k++) {
                    suma += A.datos[i][k] * B.datos[k][j];
                }
                
                C.datos[i][j] = suma;
            }
        }

        return C;
    }

    // Método para mostrar la matriz en pantalla
    void mostrar() const {
        for (int i = 0; i < filas; i++) {
            std::cout << "| ";
            for (int j = 0; j < columnas; j++) {
                std::cout << std::setw(6) << datos[i][j] << " | ";
            }
            std::cout << std::endl;
        }
    }

    // Método para llenar la matriz pidiendo datos al usuario
    void llenarMatriz() {
        std::cout << "Ingresar valores para la matriz (" << filas << "x" << columnas << "):" << std::endl;
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                std::cout << "Elemento[" << i << "," << j << "]: ";
                std::cin >> datos[i][j];
            }
        }
    }
};

#endif // MATRIZDINAMICA_H
