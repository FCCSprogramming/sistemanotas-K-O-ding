/*
Autor: Manuel Rojas Tuyen
*/

#include "Funciones.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;

int main() {
    Estudiante listaEstudiantes[MAX_ESTUDIANTES];
    int numEstudiantes = 0;
    int opcion;

    cargarDatos(listaEstudiantes, numEstudiantes);

    do
    {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        // Se valida entrada numerica
        if (cin.fail()) 
        {
            cout << "Error, ingrese un numero valido." << endl;
            limpiarBuffer();
            opcion = 0; // Se fuerza a que la opcion sea invalida
        } else 
        {
            limpiarBuffer(); // Se limpia el buffer
        }

        switch (opcion) 
        {
            case 1: 
            {
                registrarEstudiante(listaEstudiantes, numEstudiantes);
                guardarDatos(listaEstudiantes, numEstudiantes);
                break;
            }
            case 2: 
            {
                string cod;
                cout << "Ingrese el codigo del estudiante: ";
                getline(cin, cod);
                const string codigo = cod;
                Estudiante* est = buscarEstudiante(listaEstudiantes, numEstudiantes, codigo);
                if (est != nullptr) 
                {
                    matricularCurso(*est);
                    guardarDatos(listaEstudiantes, numEstudiantes);
                } else 
                {
                    cout << "Error, estudiante no encontrado." << endl;
                }
                break;
            }
            case 3: 
            {
                string cod;
                cout << "Ingrese el codigo del estudiante: ";
                getline(cin, cod);
                const string codigo = cod;
                Estudiante* est = buscarEstudiante(listaEstudiantes, numEstudiantes, codigo);
                if (est != nullptr) 
                {
                    ingresarNotas(*est);
                    guardarDatos(listaEstudiantes, numEstudiantes);
                } else 
                {
                    cout << "Error, estudiante no encontrado." << endl;
                }
                break;
            }
            case 4: 
            {
                string cod;
                cout << "Ingrese el codigo del estudiante: ";
                getline(cin, cod);
                const string codigo = cod;
                const Estudiante* est = buscarEstudiante(listaEstudiantes, numEstudiantes, codigo);
                if (est != nullptr) 
                {
                    est->mostrarDatos();
                    mostrarCursosEstudiante(*est);
                } else 
                {
                    cout << "Error, estudiante no encontrado." << endl;
                }
                break;
            }
            case 5: 
            {
                string cod;
                cout << "Ingrese el codigo del estudiante: ";
                getline(cin, cod);
                const string codigo = cod;
                const Estudiante* est = buscarEstudiante(listaEstudiantes, numEstudiantes, codigo);
                if (est != nullptr) 
                {
                    generarBoleta(*est);
                } else 
                {
                    cout << "Error, estudiante no encontrado." << endl;
                }
                break;
            }
            case 6: 
            {
                mostrarMejorPromedio(listaEstudiantes, numEstudiantes);
                break;
            }
            case 7: 
            {
                estudiantesAprobadosCurso(listaEstudiantes, numEstudiantes);
                break;
            }
            case 8: 
            {
                reporteGeneral(listaEstudiantes, numEstudiantes);
                break;
            }
            case 9:
                cout << "Saliendo del sistema. Hasta luego! :D" << endl;
                break;
            default:
                cout << "Opcion invalida, intente de nuevo." << endl;
                break;
        }
        if (opcion != 9) // Se implementa una pausa antes de la siguiente eleccion
        { 
            cout << "\nPresione 'Enter' para continuar...";
            cin.get();
        }

    } while (opcion != 9);

    return 0;
}