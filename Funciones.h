/*
Autor: Manuel Rojas Tuyen
*/

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "Estructuras.h" // Se incluyen las estructuras de 'Estructuras.h'

// Prototipos de funciones
void mostrarMenu();
void limpiarBuffer();

void registrarEstudiante(Estudiante estudiantes[], int &cantidad);
Estudiante* buscarEstudiante(Estudiante estudiantes[], int cantidad, const std::string& codigo);

void matricularCurso(Estudiante &estudiante);
void ingresarNotas(Estudiante &estudiante);
void mostrarCursosEstudiante(const Estudiante &estudiante);

float calcularPromedioPonderado(const Estudiante &estudiante);
int calcularTotalCreditos(const Estudiante &estudiante);
void generarBoleta(const Estudiante &estudiante);

void mostrarMejorPromedio(const Estudiante estudiantes[], int cantidad);
void estudiantesAprobadosCurso(const Estudiante estudiantes[], int cantidad);
void reporteGeneral(const Estudiante estudiantes[], int cantidad);

void guardarDatos(const Estudiante estudiantes[], int cantidad);
void cargarDatos(Estudiante estudiantes[], int &cantidad);

#endif