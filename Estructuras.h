#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <iostream>
#include <string>
#include <iomanip>

// Constantes globales
const int MAX_ESTUDIANTES = 50;
const int MAX_CURSOS_POR_ESTUDIANTE = 6;
const std::string NOMBRE_ARCHIVO = "datos_academicos.txt";

// Definicion de estructuras
struct Notas {
    float EP = 0;
    float EF = 0;
    float PP = 0;

    float calcularPromedio() const;
    std::string obtenerEstado() const;
};

struct Curso {
    std::string codigo;
    std::string nombre;
    int creditos;
    std::string profesor;
    Notas notas;

    void mostrarInformacion() const;
    float calcularPromedio() const;
    std::string obtenerEstado() const;
};

struct Estudiante {
    std::string codigo;
    std::string nombre;
    std::string carrera;
    int ciclo;
    Curso cursos[MAX_CURSOS_POR_ESTUDIANTE];
    int cantidadCursos = 0;

    void mostrarDatos() const;
};

#endif