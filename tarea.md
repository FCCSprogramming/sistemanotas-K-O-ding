### Tarea 

Desarrolla un sistema de gestión académica para la UNI que permita administrar la información de estudiantes, cursos y sus calificaciones. El sistema debe utilizar estructuras en C++ para organizar los datos de manera eficiente. Su implementación debe 

    - Aplicar conceptos de estructuras en C++
    - Implementar arreglos de estructuras
    - Usar anidamiento de estructuras
    - Trabajar con punteros a estructuras
    - Pasar estructuras como parámetros de funciones
    - Implementar funciones miembro en estructuras

Estructuras requeridas

```cpp
struct Notas {
    float EP;  // Examen Parcial (30%)
    float EF;  // Examen Final (50%)
    float PP;  // Promedio de Prácticas (20%)
    
    // Función para calcular promedio final
    float calcularPromedio() {
        return EP * 0.3 + EF * 0.5 + PP * 0.2;
    }
    
    // Función para determinar estado
    string obtenerEstado() {
        float prom = calcularPromedio();
        if (prom >= 10.5) return "Aprobado";
        else return "Desaprobado";
    }
};
```

```cpp
struct Curso {
    string codigo;
    string nombre;
    int creditos;
    string profesor;
    Notas notas;  // Estructura anidada
    
    void mostrarInformacion() {
        // Implementar: mostrar información del curso
    }
};
```

```cpp
struct Estudiante {
    string codigo;
    string nombre;
    string carrera;
    int ciclo;
    Curso cursos[6];  // Máximo 6 cursos por estudiante
    int cantidadCursos;
    
    void mostrarDatos() {
        // Implementar: mostrar datos del estudiante
    }
};
```

Requisitos del Sistema

**Funciones Básicas** 

1.1 Gestión de Estudiantes
```cpp
// Prototipos de funciones a implementar
void registrarEstudiante(Estudiante estudiantes[], int &cantidad);
void mostrarEstudiantes(const Estudiante estudiantes[], int cantidad);
Estudiante* buscarEstudiante(Estudiante estudiantes[], int cantidad, string codigo);
```
1.2 Gestión de Cursos por Estudiante
```cpp
void matricularCurso(Estudiante &estudiante);
void ingresarNotas(Estudiante &estudiante);
void mostrarCursosEstudiante(const Estudiante &estudiante);
```


**Funciones Avanzadas**

2.1 Cálculos Académicos
```cpp
float calcularPromedioPonderado(const Estudiante &estudiante);
int calcularTotalCreditos(const Estudiante &estudiante);
void generarBoleta(const Estudiante &estudiante);
``` 

2.2 Reportes del Sistema
```cpp
void mostrarMejorPromedio(const Estudiante estudiantes[], int cantidad);
void estudiantesAprobadosCurso(const Estudiante estudiantes[], int cantidad, string codigoCurso);
void reporteGeneral(const Estudiante estudiantes[], int cantidad);
```

**Menú Principal**

El sistema debe incluir un menú interactivo con las siguientes opciones:

```text
=== SISTEMA DE GESTIÓN ACADÉMICA UNI ===
1. Registrar estudiante
2. Matricular curso a estudiante
3. Ingresar notas de curso
4. Mostrar información de estudiante
5. Generar boleta de notas
6. Mostrar mejor promedio
7. Estudiantes aprobados por curso
8. Reporte general
9. Salir

Ejemplo de Implementación Esperada

Entrada/Salida Esperada:

=== REGISTRAR ESTUDIANTE ===
Código: 202300001
Nombre: Ana García Pérez
Carrera: Ciencia de la Computación
Ciclo: 3

=== MATRICULAR CURSO ===
Estudiante: 202300001 - Ana García Pérez
Código curso: CC112
Nombre: Fundamentos de Programación
Créditos: 4
Profesor: Dr. Carlos Ruiz

=== INGRESAR NOTAS ===
Curso: CC112 - Fundamentos de Programación 
Examen Parcial: 15
Examen Final: 16
Promedio de Prácticas: 17

=== BOLETA DE NOTAS ===
Estudiante: Ana García Pérez (202300001)
Carrera: Ciencia de la Computación - Ciclo: 3

Código  Curso                     Créditos  EP   EF   PP   Promedio  Estado
CC112 Fundamentos de Programación 4         15   16   17   15.90     Aprobado
CC201   Base de Datos             3         14   13   16   13.70     Aprobado

Promedio Ponderado: 14.95
Total Créditos: 7
```

**Implementaciones opcionales**

1. Usar Punteros para Búsqueda Eficiente
```cpp
Estudiante** obtenerEstudiantesAprobados(const Estudiante estudiantes[], int cantidad, int &aprobadosCount);
```

2. Estructura Anidada para Fechas
```cpp
struct Fecha {
    int dia, mes, año;
};

struct Matricula {
    Curso curso;
    Fecha fechaMatricula;
    bool estado; // true: activo, false: retirado
};
```

3. Función para Ordenar Estudiantes
```cpp
void ordenarEstudiantesPorPromedio(Estudiante estudiantes[], int cantidad);

```