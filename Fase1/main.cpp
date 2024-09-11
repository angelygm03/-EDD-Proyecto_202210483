#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <nlohmann/json.hpp>
#include "listaEnlazada/headers/mylist.h"
#include "pila/headers/stack.h"
#include "listaDobleEnlazada/headers/doublelist.h"
#include "circularDobleEnlazada/headers/circularDoubleList.h"
#include "solicitudList/headers/solicitudList.h"
#include "matrix/matrix.h"

using namespace std;
using json = nlohmann::json;

// Credenciales de usuario
const string ADMIN_USER = "admin@gmail.com";
const string ADMIN_PASSWORD = "EDD2S2024";

// Función para cargar usuarios desde un archivo JSON
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
            usuario["fecha_de_nacimiento"],
            usuario["correo"],
            usuario["contraseña"]
        );
    }
    cout << "Usuarios cargados exitosamente." << endl;
}

// Función para cargar y mostrar las solicitudes desde un archivo JSON
void cargarSolicitudesDesdeJson(const string& filename, MyList& lista, Matrix& matrix) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << filename << endl;
        return;
    }

    json solicitudes;
    archivo >> solicitudes;

    for (const auto& solicitud : solicitudes) {
        string emisorCorreo = solicitud["emisor"];
        string receptorCorreo = solicitud["receptor"];
        string estado = solicitud["estado"];

        Node* emisor = lista.buscar(emisorCorreo);
        Node* receptor = lista.buscar(receptorCorreo);

        if (emisor != nullptr && receptor != nullptr) {
            if (estado == "ACEPTADA") {
                matrix.insertarRelacion(emisor, receptor);
                matrix.insertarRelacion(receptor, emisor);  // Relación bidireccional

            } else if (estado == "PENDIENTE") {
                receptor->solicitudes.push(emisorCorreo, receptorCorreo, estado);
            }
        } else {
            cout << "No se encontró uno de los usuarios: " << emisorCorreo << " o " << receptorCorreo << endl;
        }
    }

    cout << "Solicitudes cargadas exitosamente." << endl;
}


// Función para cargar publicaciones desde un archivo JSON
void cargarPublicacionesDesdeJson(const string& filename, DoubleList& listaDoble, CircularDoubleList& listaCircular) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << filename << endl;
        return;
    }

    json publicaciones;
    archivo >> publicaciones;

    for (const auto& publicacion : publicaciones) {
        listaDoble.insertAtEnd(
            publicacion["correo"],
            publicacion["contenido"],
            publicacion["fecha"],
            publicacion["hora"]
        );
        listaCircular.insertAtEnd(
            publicacion["correo"],
            publicacion["contenido"],
            publicacion["fecha"],
            publicacion["hora"]
        );
    }

    cout << "Publicaciones cargadas exitosamente." << endl;
}

string obtenerFechaHoraActual() {
    auto ahora = std::chrono::system_clock::now();
    auto tiempo = std::chrono::system_clock::to_time_t(ahora);
    std::tm* tm_local = std::localtime(&tiempo);

    std::ostringstream fechaHoraStream;
    fechaHoraStream << std::put_time(tm_local, "%d/%m/%Y %H:%M");

    return fechaHoraStream.str();
}


void enviarSolicitud(MyList& lista, const string& correoUsuario) {
    string correoDestino;
    cout << "Ingrese el correo del usuario al que desea enviar una solicitud: ";
    cin >> correoDestino;

    Node* destinatario = lista.buscar(correoDestino);
    if (destinatario != nullptr) {
        // Crear una nueva solicitud pendiente
        StackNode* nuevaSolicitud = new StackNode(correoUsuario, destinatario->correo, "PENDIENTE");
        nuevaSolicitud->emisor = correoUsuario;
        nuevaSolicitud->receptor = destinatario->correo;
        nuevaSolicitud->estado = "PENDIENTE";
        nuevaSolicitud->next = nullptr;

        // Insertar la solicitud en la pila del receptor
        destinatario->solicitudes.push(correoUsuario, destinatario->correo, "PENDIENTE");

        // Se agrega la solicitud a la lista simple del emisor
        lista.agregarSolicitudEnviada(correoUsuario, destinatario->correo);

        cout << "Solicitud enviada a " << destinatario->nombres << " " << destinatario->apellidos << " (" << destinatario->correo << ")" << endl;
    } else {
        cout << "El usuario con el correo " << correoDestino << " no se encontro." << endl;
    }
}

// Función para autenticar al usuario
bool autenticarUsuario(const string& correo, const string& contrasena, MyList& lista) {
    Node* usuario = lista.buscar(correo);
    if (usuario != nullptr && usuario->contrasena == contrasena) {
        return true;
    }
    return false;
}

int mostrarMenu() {
    int opcion;
    cout << "*************************************\n";
    cout << "    BIENVENIDO A SOCIAL STRUCTURE      \n";
    cout << "*************************************\n";
    cout << "1. Iniciar sesion \n";
    cout << "2. Registrarse \n";
    cout << "3. Informacion \n";
    cout << "4. Salir \n";
    cout << "Ingrese una opcion: ";
    cin >> opcion;
    return opcion;
}

void mostrarMenuReportes(MyList& lista, DoubleList& listaDoble, Matrix& matrix) {
    int opcion;
    do {
        cout << "********** MENU REPORTES **********\n";
        cout << "1. Reporte de usuarios \n";
        cout << "2. Reporte de relaciones \n";
        cout << "3. Reporte de publicaciones \n";
        cout << "4. Top 5 \n";
        cout << "5. Salir \n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "Generando reporte de usuarios...\n";
                lista.generateDotFile();
                break;
            }
            case 2: {
                cout <<"Generando reporte de relaciones de amistad...\ns";
                matrix.generateDotFile("matrizDispersa");
                break;
            }
            case 3: {
                cout << "Generando reporte de publicaciones...\n";
                listaDoble.generateDotFile();
                break;
            }
            case 4:{
                cout << "****************** Top 5 ******************\n";
                cout << "Usuarios con mas publicaciones \n";
                listaDoble.printTopUsersByPublications();
                cout << "****************** Top 5 ******************\n";
                cout << "Usuarios con menos amigos \n";
                matrix.top5MenosAmigos();
                break;
            }
            case 5: {
                cout << "Volviendo al menu anterior..." << endl;
                return;
            }
            default: {
                cout << "Opción no valida. Intentelo de nuevo.\n";
                break;
            }
        }
    } while (opcion != 4);
}

void mostrarMenuAdmin(MyList& lista, DoubleList& listaDoble, CircularDoubleList& listaCircular) {
    Matrix matrix; 
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
            case 2: {
                string filename;
                cout << "Ingrese el nombre del archivo JSON: ";
                cin >> filename;
                cargarSolicitudesDesdeJson(filename, lista, matrix);
                break;
            }
            case 3: {
                string filename;
                cout << "Ingrese el nombre del archivo JSON: ";
                cin >> filename;
                cargarPublicacionesDesdeJson(filename, listaDoble, listaCircular);
                break;
            }
            case 4: {
                cout << "Ingrese el correo del usuario a eliminar: ";
                string correo;
                cin >> correo;
                if (lista.eliminar(correo)) {
                    cout << "Usuario eliminado correctamente.\n";
                } else {
                    cout << "Usuario no encontrado.\n";
                }
                break;
            }
            case 5: {
                mostrarMenuReportes(lista, listaDoble, matrix);
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


void mostrarMenuPublicaciones(DoubleList& listaDoble, CircularDoubleList& listaCircular, const string& correoUsuario) {
    int opcion;
    do {
        cout << "********** MENU PUBLICACIONES **********\n";
        cout << "1. Ver todas las publicaciones \n";
        cout << "2. Crear una nueva publicacion \n";
        cout << "3. Eliminar una publicacion\n";
        cout << "4. Volver al menu anterior \n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                listaCircular.showPostsWithNavigation();
                break;
            }
            case 2: {
                string textoPublicacion;
                cout << "Escriba aqui: \n";
                cin.ignore();  // Limpiar el buffer
                getline(cin, textoPublicacion);  // Obtener la publicación como una línea completa de texto

                // Obtener la fecha y hora actuales
                string fechaHoraActual = obtenerFechaHoraActual();
                size_t pos = fechaHoraActual.find(' ');
                string fecha = fechaHoraActual.substr(0, pos);
                string hora = fechaHoraActual.substr(pos + 1);

                // Agregar la publicación a la lista doble
                listaDoble.insertAtEnd(correoUsuario, textoPublicacion, fecha, hora);

                // Agregar la publicación a la lista circular
                listaCircular.insertAtEnd(correoUsuario, textoPublicacion, fecha, hora);

                cout << "Publicacion creada" << endl;
                break;
            }
            case 3: {
                // Mostrar las publicaciones del usuario
                listaDoble.printByUser(correoUsuario);

                // Solicitar el ID de la publicación a eliminar
                int index;
                cout << "Ingrese el ID de la publicacion que desea eliminar: ";
                cin >> index;

                // Eliminar la publicación de la lista circular
                if (listaCircular.deleteByPosition(index)) {
                    cout << "Publicacion eliminada exitosamente" << endl;

                    // También eliminamos de la lista doble
                    if (!listaDoble.deleteByUser(index, correoUsuario)) {
                        cout << "Error al eliminar la publicacion" << endl;
                    }
                } else {
                    cout << "ID ingresado no valido" << endl;
                }

                break;
            }
            case 4: {
                cout << "Volviendo al menu..." << endl;
                break;
            }
            default: {
                cout << "Opcion no valida. Intentelo de nuevo.\n";
                break;
            }
        }
    } while (opcion != 4);
}

void mostrarMenuUsuario(MyList& lista, DoubleList& listaDoble, CircularDoubleList& listaCircular, const std::string& correoUsuario, SolicitudList& solicitudList);


void mostrarMenuReportesUsuario(MyList& lista, DoubleList& listaDoble, const string& correoUsuario, CircularDoubleList& listaCircular, SolicitudList& solicitudList) {
    int opcion;
    do {
        cout << "********** MENU REPORTES USUARIO **********\n";
        cout << "1. Reporte de solicitudes \n";
        cout << "2. Publicaciones\n";
        cout << "3. Amigos \n";
        cout << "4. Volver al menu anterior \n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                Node* usuario = lista.buscar(correoUsuario);
                if (usuario != nullptr) {
                    usuario->solicitudes.generateDotFile("reporteUsuarios", usuario->correo);
                    cout << "Generando reportes...\n";
                }
                lista.generateSolicitudDotFile(usuario);
                break;
            }
            case 2: {
                cout << "Generando reporte de publicaciones...\n";
                listaCircular.generateDotFile("reportePublicaciones.dot", correoUsuario);
                break;
            }
            case 3: {
                cout << "Generando reporte de amigos...\n";
                lista.matrix.generateDotFile("reporteAmigos");
                break;
            }
            case 4: {
                cout << "Volviendo al menu anterior...\n";
                mostrarMenuUsuario(lista, listaDoble, listaCircular, correoUsuario, solicitudList);
                break;
            }
            default: {
                cout << "Opcion no valida. Intentelo de nuevo.\n";
                break;
            }
        }
    } while (opcion != 4);
}

void mostrarMenuUsuario(MyList& lista, DoubleList& listaDoble, CircularDoubleList& listaCircular, const string& correoUsuario, SolicitudList& solicitudList) {
    int opcion;
    do {
        cout << "********** MENU USUARIO **********\n";
        cout << "1. Ver perfil \n";
        cout << "2. Eliminar perfil \n";
        cout << "3. Ver solicitudes \n";
        cout << "4. Enviar solicitud \n";
        cout << "5. Publicaciones \n";
        cout << "6. Reportes \n";
        cout << "7. Salir \n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                Node* usuario = lista.buscar(correoUsuario);
                if (usuario) {
                    usuario->print();
                } else {
                    cout << "Usuario no encontrado.\n";
                }
                break;
            }
            case 2: {
                cout << "¿Esta seguro de que desea eliminar su perfil? (s/n): ";
                char confirmacion;
                cin >> confirmacion;
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (lista.eliminar(correoUsuario)) {
                        cout << "Perfil eliminado correctamente.\n";
                        return;
                    } else {
                        cout << "Error al eliminar el perfil.\n";
                    }
                }
                break;
            }
            case 3: {
                Node* usuario = lista.buscar(correoUsuario);
                if (usuario != nullptr) {
                    lista.manejarSolicitudes(usuario);
                } else {
                    cout << "Usuario no encontrado.\n";
                }
                break;
            }
            case 4: {
                enviarSolicitud(lista, correoUsuario);
                break;
            }
            case 5: {
                mostrarMenuPublicaciones(listaDoble, listaCircular, correoUsuario);
                break;
            }
            case 6:{
                mostrarMenuReportesUsuario(lista, listaDoble, correoUsuario, listaCircular, solicitudList);
                break;
            }
            case 7: {
                cout << "Saliendo del menu...\n";
                return;
            }
            default: {
                cout << "Opcion no valida. Intentelo de nuevo.\n";
                break;
            }
        }
    } while (opcion != 6);
}

int main() {
    MyList lista;
    DoubleList listaDoble;
    CircularDoubleList listaCircular;
    SolicitudList solicitudList;
    
    int opcion;
    do {
        opcion = mostrarMenu();
        switch (opcion) {
            case 1: {
                string usuario, password;
                cout << "Ingrese su usuario: ";
                cin >> usuario;
                cout << "Ingrese su contrasenia: ";
                cin >> password;

                // Validar credenciales
                if (usuario == ADMIN_USER && password == ADMIN_PASSWORD) {
                    mostrarMenuAdmin(lista, listaDoble, listaCircular);
                } else if (autenticarUsuario(usuario, password, lista)) {
                    string correoUsuario = usuario;
                    mostrarMenuUsuario(lista, listaDoble, listaCircular, correoUsuario, solicitudList);
                } else {
                    cout << "Credenciales incorrectas. Intentelo de nuevo.\n";
                }
                break;
            }
            case 2: {
                string nombres, apellidos, fechaNacimiento, correo, contrasena;
                cout << " --------------- Registro de Usuario ---------------\n";
                cout << "Ingrese sus nombres: ";
                cin >> nombres;
                cout << "Ingrese sus apellidos: ";
                cin >> apellidos;
                cout << "Ingrese su fecha de nacimiento: ";
                cin >> fechaNacimiento;
                cout << "Ingrese su correo: ";
                cin >> correo;
                cout << "Ingrese su contraseña: ";
                cin >> contrasena;

                lista.insert(nombres, apellidos, fechaNacimiento, correo, contrasena);
                cout << "Usuario registrado correctamente.\n";
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
            default: {
                cout << "Opcion invalida. Intentelo de nuevo.\n";
                break;
            }
        }
    } while (opcion != 4);
    return 0;
}