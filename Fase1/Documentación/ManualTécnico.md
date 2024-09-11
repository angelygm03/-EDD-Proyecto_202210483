# Manual Técnico Social Structure
## Estructuras de Datos
### Segundo Semestre 2024
```js
Universidad San Carlos de Guatemala
Facultad de Ingeniería
Nombre: Angely Lucrecia García Martínez
Carne: 202210483
```
---
## Descripción del Proyecto
El proyecto "Social Structure" es un sistema de gestión de redes sociales que permite la administración y visualización de usuarios, solicitudes de amistad, y publicaciones. Está desarrollado en C++ y hace uso de varias estructuras de datos, como listas enlazadas simples, listas enlazadas dobles, listas circulares dobles, y pilas, para organizar y gestionar la información de manera eficiente.

## Objetivo
El manual técnico proporciona una guía detallada para desarrolladores, administradores de sistemas y otros usuarios técnicos sobre cómo instalar, configurar y utilizar Social Structure. Contiene información sobre la estructura del código, las dependencias del proyecto, las instrucciones de implementación, y la explicación de los diferentes componentes y su funcionamiento.

El manual técnico está diseñado para ofrecer una referencia completa para aquellos que deseen comprender el funcionamiento interno del sistema, realizar personalizaciones o contribuir al desarrollo continuo del proyecto.

## Características Principales
* Gestión de Usuarios: Los usuarios pueden registrarse, iniciar sesión, y ver su perfil. Los administradores tienen la capacidad de cargar usuarios desde archivos JSON, así como eliminar usuarios existentes.

* Solicitudes de Amistad: Los usuarios pueden enviar y recibir solicitudes de amistad. Las solicitudes recibidas se almacenan en pilas asociadas a cada usuario receptor y se pueden gestionar desde su perfil. Asimismo las solicitudes enviadas se almacenan en listas simples.

* Publicaciones: Los usuarios pueden crear, visualizar, y eliminar publicaciones. Las publicaciones se gestionan utilizando listas enlazadas dobles y listas circulares dobles, lo que permite una organización eficiente y la posibilidad de reportes.

* Reportes: El sistema permite generar reportes en formato .png para visualizar la estructura de datos de los usuarios, sus relaciones, y publicaciones. Además, los administradores pueden ver un Top 5 de los usuarios con más publicaciones.

* Menú Administrativo: Los administradores tienen acceso a un menú exclusivo donde pueden gestionar usuarios, relaciones, y publicaciones a través de cargas masivas desde archivos JSON.

* Autenticación: El sistema incluye un mecanismo de autenticación para garantizar que solo los usuarios registrados y el administrador tengan acceso a sus respectivas funciones.

## Tecnologías utilizadas
* C++: El proyecto está desarrollado principalmente en lenguaje C++, aprovechando las bibliotecas nativas para implementar la funcionalidad requerida.

* Graphviz: Se utiliza la biblioteca Graphviz para generar gráficos visuales que representan las mascotas y su estado.

* Nlohmann /Json: Se utiliza la biblioteca del desarrollador Nlohmann la cual es necesaria para parsear los archivos JSON que se cargan al sistema.

## Requisitos del sistema
* Compilador C++
    * GCC 
    * MinGW
    * Clang

* Sistema operativo compatible con C++.
* Bibliotecas
    * nlohmann/json: Para manejar archivos JSON.
    * C++ Standard Library: Para uso de `<iostream>`, `<string>`, `<fstream>` y `<chrono>`.
    * Graphviz: Para la generación y visualización de reportes en formato .dot.

## Instalación
Debido a que es una aplicación que se ejecuta en consola, se debe clonar o descargar el repositorio del proyecto desde [Github](https://github.com/angelygm03/-EDD-Proyecto_202210483.git) para luego abrir el proyecto en el IDE de su preferencia (se recomienda Visual Studio Code) y correr la aplicación.

## Estructura del Proyecto
El proyecto sigue una estructura de directorios típica de C++
* Fase 1
    * main.cpp: Script principal para ejecutar la aplicación.
        * listaEnlazada: Contiene los headers y scripts que almacenan la información de los usuarios en el sistema
        * listaDobleEnlzada: Es una lista doblemente enlazada que almacenan globalmente las publicaciones de todos los usuarios en la aplicación.
        * pila: En esta estructura se almacenan las solicitudes que cada usuario recibe, por lo tanto, cuando el usuario se registra en el sistema automáticamente se le asigna una pila
        * solicitudList: Es una lista simplemente enlazada que también almacena solicitudes, pero en este caso son solicitudes como emisor.
        * circularDobleEnlazada: En esta estructura se almacenan las publicaciones pero de forma personal, cada usuario tiene una lista circular para que pueda observar únicamente sus publicaciones.

## Bibliotecas utilizadas
* iostream: Proporciona las funcionalidades para la entrada y salida estándar en C++.

* string: Ofrece soporte para trabajar con cadenas de caracteres (strings) en C++. 

* fstream: Facilita el manejo de archivos en C++ (entrada/salida de archivos).

* chrono: Proporciona herramientas para trabajar con tiempo y duraciones.

* iomanip: Ofrece manipuladores para la configuración de la entrada y salida de datos.

* nlohmann/json.hpp: Es parte de la biblioteca externa nlohmann/json que facilita el manejo de datos en formato JSON. 

![INVCLASS](https://i.ibb.co/tsm0V9g/image.png)


## Uso del código
El archivo main.py contiene el script principal que debe ejecutarse para iniciar la aplicación. El sistema pide que se ingresen distintas opciones para que el usario elija la que desea por medio de inputs proporcionados por el script. Los detalles sobre cómo utilizar cada comando están documentados dentro del manual de usuario.
![INVCLASS](https://i.ibb.co/hVWQRqT/image.png)

## Estructuras Utilizadas
### Listas Enlazadas
La aplicación emplea 2 listas simplemente enlazadas MyList y SolicitudList, la primera maneja las solicitudes que el emisor envía a otros usuarios y la segunda que almacena los usuarios en el sistema así como sus datos personales.

![INVCLASS](https://i.ibb.co/YXHmLv5/image.png)

### Lista doblemente enlazada
Como se mencionó anteriormente, esta estructura almacena las publicaciones de formar global en todo el sistema, solamente el usuario administrador puede acceder a ella.

![INVCLASS](https://i.ibb.co/4W9Y6S9/image.png)

### Pila
La pila fue una buena elección para poder mostrarle las solicitudes pendientes al usuario, de esta manera cuando el usuario quiera ver y aprobar las solicitudes se le muestran primero las útlimas solicitudes entrantes.

![INVCLASS](https://i.ibb.co/MkMwJTV/image.png)

### Lista Circular Doblemente Enlazada
Se hace uso de este tipo de estructura para almacenar las publicaciones que un usuario en específico ha publicado, omitiendo las del resto de usuarios. Es muy funcional al momento de que el usuario quiera retroceder o avanzar hacia una publicación.

![INVCLASS](https://i.ibb.co/dtZZkPs/image.png)


## Manejo de Errores
### Instalación de Bibliotecas y Compiladores
La correcta instalación de las bibliotecas y del compilador requerido es crucial para el funcionamiento adecuado de Social Structure. A continuación, se detalla cómo manejar posibles errores relacionados con la instalación y la importación de estas bibliotecas:

#### Error de Importación de Graphviz
Si al ejecutar Social Structure se encuentra con un error relacionado con la importación de la biblioteca graphviz, es probable que esta biblioteca no esté instalada en su entorno. Esto puede suceder si la biblioteca no se ha instalado previamente utilizando en el Path (variables de entorno).


#### Manejo de Excepciones
Social Structure está diseñado para manejar posibles errores de importación de bibliotecas de manera que el programa continúe ejecutándose sin interrupciones graves. Si no se puede importar graphviz, algunas funcionalidades que dependen de esta biblioteca pueden estar deshabilitadas, pero el resto del programa seguirá funcionando normalmente.




