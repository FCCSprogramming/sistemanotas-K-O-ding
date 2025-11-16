/*
Autor: Manuel Rojas Tuyen
*/

#include "Funciones.h" // Se incluyen las declaraciones y tambien 'Estructuras.h'
#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::ofstream;
using std::ifstream;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;

// Implementacion de funciones miembro de estructuras

float Notas::calcularPromedio() const {
    return EP * 0.3 + EF * 0.5 + PP * 0.2;
}

string Notas::obtenerEstado() const {
    if (calcularPromedio() >= 10.5) {
        return "Aprobado";
    }
    return "Desaprobado";
}

void Curso::mostrarInformacion() const {
    cout << left
         << setw(8) << codigo << setw(30) << nombre << setw(10) << creditos
         << setw(6) << fixed << setprecision(2) << notas.EP << setw(6) << notas.EF
         << setw(6) << notas.PP << setw(10) << calcularPromedio()
         << setw(12) << obtenerEstado() << endl;
}

float Curso::calcularPromedio() const {
    return notas.calcularPromedio();
}
    
string Curso::obtenerEstado() const {
    return notas.obtenerEstado();
}

void Estudiante::mostrarDatos() const {
    cout << "------------------------------------------" << endl;
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Carrera: " << carrera << endl;
    cout << "Ciclo: " << ciclo << endl;
    cout << "Cursos: " << cantidadCursos << endl;
    cout << "------------------------------------------" << endl;
}

// Implementacion de funciones globales

void mostrarMenu() {
    cout<<R"(=== SISTEMA DE GESTION ACADEMICA UNI ===
1. Registrar estudiante
2. Matricular curso a estudiante
3. Ingresar notas de curso
4. Mostrar informacion de estudiante
5. Generar boleta de notas
6. Mostrar mejor promedio
7. Estudiantes aprobados por curso
8. Reporte general
9. Salir)"<<endl;
}

void limpiarBuffer() {
    cin.clear(); // Se limpia los flags de error de cin
    cin.ignore();
}

void registrarEstudiante(Estudiante estudiantes[], int &cantidad) {
    if (cantidad >= MAX_ESTUDIANTES) 
    {
        cout << "Error, no se pueden registrar mas estudiantes." << endl;
        return;
    }
    cout << "--- REGISTRAR NUEVO ESTUDIANTE ---" << endl;
    Estudiante& nuevo = estudiantes[cantidad];
    cout << "Codigo: ";
    getline(cin, nuevo.codigo);
    cout << "Nombre completo: ";
    getline(cin, nuevo.nombre);
    cout << "Carrera: ";
    getline(cin, nuevo.carrera);
    cout << "Ciclo: ";
    cin >> nuevo.ciclo;
    limpiarBuffer();
    
    nuevo.cantidadCursos = 0; // Se asegura que inicie en 0
    cantidad++;
    cout << "Estudiante registrado con exito." << endl;
}

Estudiante* buscarEstudiante(Estudiante estudiantes[], int cantidad, const string& codigo) {
    for (int i = 0; i < cantidad; ++i) 
    {
        if (estudiantes[i].codigo == codigo) 
        {
            return &estudiantes[i]; // Se retorna la direccion del estudiante
        }
    }
    return nullptr; // Se retorna nullptr si no se encontro el estudiante
}

void mostrarEstudiantes(const Estudiante estudiantes[], int cantidad) {
    if (cantidad == 0) 
    {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }
    cout << "--- LISTA DE ESTUDIANTES ---" << endl;
    for (int i = 0; i < cantidad; ++i) 
    {
        estudiantes[i].mostrarDatos();
    }
}

void matricularCurso(Estudiante &estudiante) {
    if (estudiante.cantidadCursos >= MAX_CURSOS_POR_ESTUDIANTE) 
    {
        cout << "Error, el estudiante ha alcanzado el maximo de cursos." << endl;
        return;
    }
    cout << "--- MATRICULAR CURSO PARA " << estudiante.nombre << " ---" << endl;
    Curso& nuevoCurso = estudiante.cursos[estudiante.cantidadCursos];
    
    cout << "Codigo del curso: ";
    getline(cin, nuevoCurso.codigo);
    cout << "Nombre del curso: ";
    getline(cin, nuevoCurso.nombre);
    cout << "Creditos: ";
    cin >> nuevoCurso.creditos;
    limpiarBuffer();
    cout << "Profesor: ";
    getline(cin, nuevoCurso.profesor);

    estudiante.cantidadCursos++;
    cout << "Curso matriculado con exito." << endl;
}

void ingresarNotas(Estudiante &estudiante) {
    if (estudiante.cantidadCursos == 0) 
    {
        cout << "El estudiante no tiene cursos matriculados." << endl;
        return;
    }

    cout << "--- INGRESAR NOTAS PARA " << estudiante.nombre << " ---" << endl;
    mostrarCursosEstudiante(estudiante);
    
    string codigoCurso;
    cout << "Ingrese el codigo del curso para agregar notas: ";
    getline(cin, codigoCurso);

    Curso* cursoEncontrado = nullptr;
    for (int i = 0; i < estudiante.cantidadCursos; ++i) 
    {
        if (estudiante.cursos[i].codigo == codigoCurso) 
        {
            cursoEncontrado = &estudiante.cursos[i];
            break;
        }
    }

    if (cursoEncontrado != nullptr) 
    {
        cout << "Ingrese nota del Examen Parcial (EP): ";
        cin >> cursoEncontrado->notas.EP;
        cout << "Ingrese nota del Examen Final (EF): ";
        cin >> cursoEncontrado->notas.EF;
        cout << "Ingrese el Promedio de Practicas (PP): ";
        cin >> cursoEncontrado->notas.PP;
        limpiarBuffer();
        cout << "Notas ingresadas con exito." << endl;
    } else 
    {
        cout << "Error, curso no encontrado." << endl;
    }
}

void mostrarCursosEstudiante(const Estudiante &estudiante) {
    if (estudiante.cantidadCursos == 0) 
    {
        cout << "No hay cursos matriculados." << endl;
        return;
    }
    cout << "Cursos matriculados:" << endl;
    for (int i = 0; i < estudiante.cantidadCursos; ++i) 
    {
        cout << " - " << estudiante.cursos[i].codigo << ": " << estudiante.cursos[i].nombre << endl;
    }
}

float calcularPromedioPonderado(const Estudiante &estudiante) {
    float sumaPonderada = 0.0;
    int totalCreditos = calcularTotalCreditos(estudiante);

    if (totalCreditos == 0) 
    {
        return 0.0;
    }

    for (int i = 0; i < estudiante.cantidadCursos; ++i) 
    {
        sumaPonderada += estudiante.cursos[i].calcularPromedio() * estudiante.cursos[i].creditos;
    }

    return sumaPonderada/totalCreditos;
}

int calcularTotalCreditos(const Estudiante &estudiante) {
    int total = 0;
    for (int i = 0; i < estudiante.cantidadCursos; ++i) 
    {
        total += estudiante.cursos[i].creditos;
    }
    return total;
}

void generarBoleta(const Estudiante &estudiante) {
    cout << "\n========= BOLETA DE NOTAS ==========" << endl;
    estudiante.mostrarDatos();

    if (estudiante.cantidadCursos > 0) 
    {
        cout << left
             << setw(8) << "Codigo"
             << setw(30) << "Curso"
             << setw(10) << "Creditos"
             << setw(6) << "EP"
             << setw(6) << "EF"
             << setw(6) << "PP"
             << setw(10) << "Promedio"
             << setw(12) << "Estado" << endl;
        cout << "------------------------------------------" << endl;

        for (int i = 0; i < estudiante.cantidadCursos; ++i) 
        {
            estudiante.cursos[i].mostrarInformacion();
        }
        cout << "------------------------------------------" << endl;
    }

    cout << "Promedio ponderado: " << fixed << setprecision(2) << calcularPromedioPonderado(estudiante) << endl;
    cout << "Total de creditos : " << calcularTotalCreditos(estudiante) << endl;
    cout << "====================================" << endl;
}

void mostrarMejorPromedio(const Estudiante estudiantes[], int cantidad) {
    if (cantidad == 0) 
    {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }
    
    float mejorPromedio = -1.0;
    const Estudiante* mejorEstudiante = nullptr;

    for (int i = 0; i < cantidad; ++i) 
    {
        float promActual = calcularPromedioPonderado(estudiantes[i]);
        if (promActual > mejorPromedio) 
        {
            mejorPromedio = promActual;
            mejorEstudiante = &estudiantes[i];
        }
    }

    if (mejorEstudiante != nullptr) 
    {
        cout << "--- MEJOR PROMEDIO DEL CICLO ---" << endl;
        cout << "Estudiante: " << mejorEstudiante->nombre << endl;
        cout << "Codigo    : " << mejorEstudiante->codigo << endl;
        cout << "Promedio ponderado: " << fixed << setprecision(2) << mejorPromedio << endl;
    }
}

void estudiantesAprobadosCurso(const Estudiante estudiantes[], int cantidad) {
    if (cantidad == 0) 
    {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }
    
    string codigoCurso;
    cout << "Ingrese el codigo del curso a consultar: ";
    getline(cin, codigoCurso);

    cout << "\n--- ESTUDIANTES APROBADOS EN EL CURSO " << codigoCurso << " ---" << endl;
    bool encontrados = false;
    for (int i = 0; i < cantidad; ++i) 
    {
        for (int j = 0; j < estudiantes[i].cantidadCursos; ++j) 
        {
            if (estudiantes[i].cursos[j].codigo == codigoCurso && estudiantes[i].cursos[j].obtenerEstado() == "Aprobado") 
            {
                cout << " - " << estudiantes[i].codigo << " | " << estudiantes[i].nombre << endl;
                encontrados = true;
                break; // Si el estudiante ha aprobado, entonces no es necesario seguir buscando en sus cursos
            }
        }
    }

    if (!encontrados) 
    {
        cout << "No se encontraron estudiantes aprobados para ese curso." << endl;
    }
}

void reporteGeneral(const Estudiante estudiantes[], int cantidad) {
    if (cantidad == 0) 
    {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }
    
    cout << "\n=============== REPORTE GENERAL DE ESTUDIANTES ===============" << endl;
    cout << left 
         << setw(12) << "Codigo"
         << setw(30) << "Nombre"
         << setw(30) << "Carrera"
         << setw(8) << "Cursos"
         << setw(10) << "Creditos"
         << setw(10) << "Prom. ponderado" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    for (int i = 0; i < cantidad; ++i) 
    {
        cout << left
             << setw(12) << estudiantes[i].codigo
             << setw(30) << estudiantes[i].nombre
             << setw(30) << estudiantes[i].carrera
             << setw(8) << estudiantes[i].cantidadCursos
             << setw(10) << calcularTotalCreditos(estudiantes[i])
             << setw(10) << fixed << setprecision(2) << calcularPromedioPonderado(estudiantes[i]) << endl;
    }
    cout << "================================================================" << endl;
}

// Trabajando con archivos
void guardarDatos(const Estudiante estudiantes[], int cantidad) {
    ofstream archivo(NOMBRE_ARCHIVO); // Se abre el archivo en modo escritura 

    if (!archivo.is_open()) 
    {
        cout << "Error, no se pudo abrir el archivo para guardar." << endl;
        return;
    }

    // Se guarda la cantidad total de estudiantes en la primera linea
    archivo << cantidad << endl;

    for (int i = 0; i < cantidad; ++i) 
    {
        const Estudiante& est = estudiantes[i];
        // Para mayor orden, se separan los datos con '|'
        archivo << est.codigo << '|' << est.nombre << '|' << est.carrera << '|' << est.ciclo << endl;
        
        // Se guarda la cantidad de cursos de este estudiante
        archivo << est.cantidadCursos << endl;

        for (int j = 0; j < est.cantidadCursos; ++j) 
        {
            const Curso& cur = est.cursos[j];
            // Se guardan los datos del curso y sus notas en una linea
            archivo << cur.codigo << '|' << cur.nombre << '|' << cur.creditos << '|' << cur.profesor << '|'
                    << cur.notas.EP << '|' << cur.notas.EF << '|' << cur.notas.PP << endl;
        }
    }

    archivo.close();
}

void cargarDatos(Estudiante estudiantes[], int &cantidad) {
    ifstream archivo(NOMBRE_ARCHIVO); // Se abre el archivo en modo lectura

    if (!archivo.is_open()) 
    {
        // Si el archivo no existe, es la primera vez que se ejecuta, por lo tanto no es un error
        cout << "Archivo de datos no encontrado. Se iniciara un nuevo registro." << endl;
        cantidad = 0;
        return;
    }

    archivo >> cantidad; // Se lee la cantidad total de estudiantes
    archivo.ignore();

    string linea;
    for (int i = 0; i < cantidad; ++i) 
    {
        Estudiante& est = estudiantes[i];
        
        getline(archivo, est.codigo, '|');
        getline(archivo, est.nombre, '|');
        getline(archivo, est.carrera, '|');
        string ciclo_str;
        getline(archivo, ciclo_str);
        est.ciclo = stoi(ciclo_str);

        string cant_cursos_str;
        getline(archivo, cant_cursos_str);
        est.cantidadCursos = stoi(cant_cursos_str);
        
        for (int j = 0; j < est.cantidadCursos; ++j) 
        {
            Curso& cur = est.cursos[j];
            
            getline(archivo, cur.codigo, '|');
            getline(archivo, cur.nombre, '|');
            string creditos_str;
            getline(archivo, creditos_str, '|');
            cur.creditos = stoi(creditos_str);
            getline(archivo, cur.profesor, '|');
            
            string ep_str, ef_str, pp_str;
            getline(archivo, ep_str, '|');
            getline(archivo, ef_str, '|');
            getline(archivo, pp_str);
            
            cur.notas.EP = stof(ep_str);
            cur.notas.EF = stof(ef_str);
            cur.notas.PP = stof(pp_str);
        }
    }

    archivo.close();
    cout << "\nSe cargaron " << cantidad << " estudiantes desde el archivo.\n" << endl;
}