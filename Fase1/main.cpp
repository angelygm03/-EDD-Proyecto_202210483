#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "listaEnlazada/headers/mylist.h"

using namespace std;
using json = nlohmann::json;

// Credenciales de usuario
const string ADMIN_USER = "admin@gmail.com";
const string ADMIN_PASSWORD = "EDD2S2024";

void cargarDesdeJson(const string& filename, MyList& lista) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << filename << endl;
        return;
    }

    json usuarios;
    archivo >> usuarios;

    for (const auto& usuario : usuarios) {
        lista.insert(
            usuario["nombres"],
            usuario["apellidos"],
            usuario["fecha de nacimiento"],
            usuario["correo"],
            usuario["contraseña"]
        );
    }
}

int mostrarMenu() {
    int opcion;
    cout << "*************************************\n";
    cout << "    BIENVENIDO A SOCIAL STRUCTURE      \n";
    cout << "*************************************\n";
    cout << "1. Iniciar sesion \n";
    cout << "3. Informacion \n";
    cout << "4. Salir \n";
    cout << "Ingrese una opcion: ";
    cin >> opcion;
    return opcion;
}

void mostrarMenuAdmin(MyList& lista) {
    int opcion;
    do {
        cout << "********** MENU ADMINISTRADOR **********\n";
        cout << "1. Carga de usuarios \n";
        cout << "2. Carga de relaciones \n";
        cout << "3. Carga de publicaciones \n";
        cout << "4. Gestion de usuarios \n";
        cout << "5. Reportes \n";
        cout << "6. Salir \n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string filename;
                cout << "Ingrese el nombre del archivo JSON: ";
                cin >> filename;
                cargarDesdeJson(filename, lista);
                break;
            }
            case 4: {
                lista.print();
                break;
            }
            case 5: {
                cout << "********** Reportes **********\n";
                lista.print();
                break;
            }           
            case 6: {
                return;
            }
            default: {
                cout << "Opcion invalida. Intentelo de nuevo.\n";
            }
        }
    } while (opcion != 6);
}

void mostrarMenuUsuario() {
    cout << "********** Opciones **********\n";
    cout << "1. Perfil \n";
    cout << "2. Solicitudes \n";
    cout << "3. Publicaciones \n";
    cout << "4. Reportes \n";
    cout << "5. Salir \n";
}

int main() {
    MyList lista;
    int opcion;
    do {
        opcion = mostrarMenu();
        switch (opcion) {
            case 1: {
                string usuario, password;
                cout << "Ingrese usuario: ";
                cin >> usuario;
                cout << "Ingrese contrasenia: ";
                cin >> password;

                // Validar credenciales
                if (usuario == ADMIN_USER && password == ADMIN_PASSWORD) {
                    mostrarMenuAdmin(lista);
                } else {
                    mostrarMenuUsuario();
                }
                break;
            }
            case 3: {
                cout << "Nombre: Angely Lucrecia Garcia Martinez\n";
                cout << "Carne: 202210483 \n";
                cout << "Curso: Estructura de Datos \n";
                cout << "Seccion: B \n";
                cout << "Segundo semestre 2024 \n";
                break;
            }
            case 4: {
                cout << "Gracias por usar Social Structure. ¡Hasta luego!\n";
                cout << "Saliendo...";
                break;
            }
            default:
                cout << "Opcion invalida. Intentelo de nuevo.\n";
        }
    } while (opcion != 4);
    return 0;
}
