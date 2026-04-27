#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <mysql.h> // Librería C API de MariaDB

using namespace std;

// Configuración de la Base de Datos
const char* HOST = "localhost";
const char* USER = "root";       // Cambia esto por tu usuario
const char* PASS = "admin";     // Cambia esto por tu contraseña
const char* DB = "nexus_academy";

// Estructura requerida (espejo de la tabla)
struct Alumno {
    int id;
    string nombre;
    string apellido;
    string celular;
    float nota_final;
};

// Función para imprimir un alumno en pantalla
void mostrarAlumno(const Alumno& a) {
    cout << "ID: " << a.id 
         << " | Nombre: " << a.nombre << " " << a.apellido 
         << " | Celular: " << a.celular 
         << " | Nota Final: " << fixed << setprecision(2) << a.nota_final << endl;
}

// A. Consulta Individual
void buscarAlumno(MYSQL* conn) {
    string id;
    cout << "\nIngrese el ID o Legajo del alumno: ";
    cin >> id;

    string query = "SELECT * FROM alumnos WHERE id = " + id;
    
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error en la consulta: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (MYSQL_ROW row = mysql_fetch_row(res)) {
        Alumno a = {stoi(row[0]), row[1], row[2], row[3], stof(row[4])};
        cout << "\n--- Ficha del Alumno ---" << endl;
        mostrarAlumno(a);
    } else {
        cout << "No se encontro ningun alumno con el ID: " << id << endl;
    }
    mysql_free_result(res);
}

// B. Ranking: Cuadro de Honor
void cuadroHonor(MYSQL* conn) {
    string query = "SELECT * FROM alumnos ORDER BY nota_final DESC LIMIT 5";
    
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error en la consulta: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    cout << "\n--- Cuadro de Honor (Top 5) ---" << endl;
    while (MYSQL_ROW row = mysql_fetch_row(res)) {
        Alumno a = {stoi(row[0]), row[1], row[2], row[3], stof(row[4])};
        mostrarAlumno(a);
    }
    mysql_free_result(res);
}

// B. Ranking: Alumnos en Riesgo
void alumnosRiesgo(MYSQL* conn) {
    string query = "SELECT * FROM alumnos WHERE nota_final < 4";
    
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error en la consulta: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    cout << "\n--- Alumnos en Riesgo (Nota < 4) ---" << endl;
    while (MYSQL_ROW row = mysql_fetch_row(res)) {
        Alumno a = {stoi(row[0]), row[1], row[2], row[3], stof(row[4])};
        mostrarAlumno(a);
    }
    mysql_free_result(res);
}

// C. Actualizar Nota
void modificarNota(MYSQL* conn) {
    string id, nueva_nota;
    cout << "\nIngrese el ID del alumno: ";
    cin >> id;
    cout << "Ingrese la nueva nota final: ";
    cin >> nueva_nota;

    string query = "UPDATE alumnos SET nota_final = " + nueva_nota + " WHERE id = " + id;
    
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error al actualizar la nota: " << mysql_error(conn) << endl;
    } else {
        if (mysql_affected_rows(conn) > 0) cout << "Nota actualizada con exito.\n";
        else cout << "No se encontro el alumno.\n";
    }
}

// C. Actualizar Celular
void modificarCelular(MYSQL* conn) {
    string id, nuevo_celular;
    cout << "\nIngrese el ID del alumno: ";
    cin >> id;
    cout << "Ingrese el nuevo numero de celular: ";
    cin >> nuevo_celular;

    string query = "UPDATE alumnos SET celular = '" + nuevo_celular + "' WHERE id = " + id;
    
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error al actualizar el celular: " << mysql_error(conn) << endl;
    } else {
         if (mysql_affected_rows(conn) > 0) cout << "Celular actualizado con exito.\n";
         else cout << "No se encontro el alumno.\n";
    }
}

int main() {
    MYSQL* conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0)) {
        cerr << "Error de conexion a la base de datos: " << mysql_error(conn) << endl;
        return 1;
    }

    int opcion;
    do {
        cout << "\n=====================================" << endl;
        cout << "  NEXUS ACADEMY - GESTION ACADEMICA  " << endl;
        cout << "=====================================" << endl;
        cout << "1. Buscar Alumno por ID" << endl;
        cout << "2. Cuadro de Honor (Top 5)" << endl;
        cout << "3. Alumnos en Riesgo (Nota < 4)" << endl;
        cout << "4. Modificar Nota de Alumno" << endl;
        cout << "5. Actualizar Celular de Alumno" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: buscarAlumno(conn); break;
            case 2: cuadroHonor(conn); break;
            case 3: alumnosRiesgo(conn); break;
            case 4: modificarNota(conn); break;
            case 5: modificarCelular(conn); break;
            case 6: cout << "Saliendo del sistema..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcion != 6);

    mysql_close(conn);
    return 0;
}