#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Trabajo {
    string nombreTrabajo;
    float nota;
};

struct Materia {
    string nombreMateria;
    Trabajo trabajos[5];
    int numTrabajos = 0;
};

struct Matricula {
    Materia* materia;
};

struct Estudiante {
    int id;
    string nombre;
    Matricula materias[3];
    int numMaterias = 0;
};

vector<Estudiante> estudiantes;
Materia materiasDisponibles[2];

void inicializarMaterias() {
    materiasDisponibles[0].nombreMateria = "Matematica";
    materiasDisponibles[1].nombreMateria = "Programacion";
    materiasDisponibles[2].nombreMateria = "Didactica";
}

void registrarEstudiante() {
    Estudiante est;
    cout << "Ingrese ID del estudiante: ";
    cin >> est.id;
    cin.ignore();
    cout << "Ingrese nombre del estudiante: ";
    getline(cin, est.nombre);
    estudiantes.push_back(est);
    cout << "Estudiante registrado con exito.\n";
}

void matricularEstudiante() {
    int id;
    cout << "Ingrese ID del estudiante a matricular: ";
    cin >> id;

    for (auto &est : estudiantes) {
        if (est.id == id) {
            cout << "Estudiante encontrado: " << est.nombre << endl;
            cout << "Seleccione materias a matricular (1=Si / 0=No):\n";

            for (int i = 0; i < 3; i++) {
                int opc;
                cout << materiasDisponibles[i].nombreMateria << ": ";
                cin >> opc;
                if (opc == 1 && est.numMaterias < 3) {
                    est.materias[est.numMaterias++].materia = &materiasDisponibles[i];
                }
            }
            return;
        }
    }
    cout << "Estudiante no encontrado.\n";
}

void crearTrabajosPorMateria() {
    for (int i = 0; i < 3; i++) {
        cout << "\nCreando trabajos para: " << materiasDisponibles[i].nombreMateria << endl;
        cout << "¿Cuantos trabajos desea ingresar? (max 5): ";
        int n;
        cin >> n;
        if (n > 5) n = 5;
        materiasDisponibles[i].numTrabajos = n;
        cin.ignore();

        for (int j = 0; j < n; j++) {
            cout << "Nombre del trabajo " << j + 1 << ": ";
            getline(cin, materiasDisponibles[i].trabajos[j].nombreTrabajo);
        }
    }
    cout << "\nTrabajos creados con exito.\n";
}

void asignarNotas() {
    int id;
    cout << "Ingrese ID del estudiante: ";
    cin >> id;

    for (auto &est : estudiantes) {
        if (est.id == id) {
            for (int i = 0; i < est.numMaterias; i++) {
                Materia* mat = est.materias[i].materia;
                cout << "\nNotas para: " << mat->nombreMateria << endl;

                for (int j = 0; j < mat->numTrabajos; j++) {
                    cout << mat->trabajos[j].nombreTrabajo << ": ";
                    cin >> mat->trabajos[j].nota;
                }
            }
            return;
        }
    }
    cout << "Estudiante no encontrado.\n";
}

void mostrarResumenNotas() {
    for (const auto &est : estudiantes) {
        cout << "\nEstudiante: " << est.nombre << " (ID: " << est.id << ")\n";

        for (int i = 0; i < est.numMaterias; i++) {
            Materia* mat = est.materias[i].materia;
            cout << "\nMateria: " << mat->nombreMateria << endl;
            float suma = 0;

            for (int j = 0; j < mat->numTrabajos; j++) {
                cout << "  " << mat->trabajos[j].nombreTrabajo << ": " << mat->trabajos[j].nota << endl;
                suma += mat->trabajos[j].nota;
            }

            if (mat->numTrabajos > 0)
                cout << "  Promedio: " << fixed << setprecision(3) << (suma / mat->numTrabajos) << endl;
        }
    }
}

int main() {
    inicializarMaterias();

    int opcion;
    do {
        cout << "\n===== Menu =====\n";
        cout << "1. Registrar estudiante\n";
        cout << "2. Matricular estudiante\n";
        cout << "3. Crear trabajos\n";
        cout << "4. Asignar notas\n";
        cout << "5. Mostrar resumen de notas\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarEstudiante(); break;
            case 2: matricularEstudiante(); break;
            case 3: crearTrabajosPorMateria(); break;
            case 4: asignarNotas(); break;
            case 5: mostrarResumenNotas(); break;
            case 6: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }

    } while (opcion != 6);

    return 0;
}