# Manual de Usuario Social Structure
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

## Objetivos
* Objetivo General
    * Proporcionar a los usuarios una guía detallada y comprensible sobre cómo utilizar todas las funciones y características de la aplicación. El manual está diseñado para facilitar el aprendizaje y la utilización eficiente de Social Structure, permitiendo a los usuarios gestionar sus relaciones de amistad y publicaciones.

* Objetivos Específicos
    * Proporcionar instrucciones paso a paso sobre cómo utilizar cada función de la aplicación, desde el inicio de sesión hasta la generación de reportes.
    * Detallar el propósito de cada función implementada en PetWorld Manager, incluyendo ejemplos prácticos para una comprensión clara.

## Desarrollo del Manual de Usuario
### Menú Principal
En este menú, se mostrarán varias opciones. La primera opción "Iniciar sesión" pedirá al usuario ingresar sus credenciales para acceder al sistema. La opción "Registrase" solicita al usuario sus datos para poder almacenarlos en el sistema y darle acceso y la última opción es "Salir" la cual finalizará la ejecución de la aplicación.

![INVCLASS](https://i.ibb.co/C5Y8Rfk/image.png)

### Registro
En esta sección el usuario debe ingresar sus datos así como su correo electrónico y una contraseña con los cuales ingresará al sistema posteriormente.

![INVCLASS](https://i.ibb.co/Smvstsm/image.png)

## Administrador
El administrador tiene sus credenciales preestablecidas en el programa, por lo tanto, no necesita registrarse.

### Menú Administrador
En este menú, el administrador puede seleccionar varias opciones entre la carga masiva de datos como la gestión de usuarios y los reportes.

![INVCLASS](https://i.ibb.co/gtQLB0S/image.png)

## Carga Masiva
Tanto los usuarios como las relaciones de amistad y las publicaciones tendrán que venir en un formato JSON para que el sistema pueda detectar su contenido. A continuación se ejemplifica el formato:

### JSON de Usuarios
![INVCLASS](https://i.ibb.co/G79L8Q1/image.png)

### JSON de Relaciones de Amistad
![INVCLASS](https://i.ibb.co/G79L8Q1/image.png)


### JSON de Publicaciones
![INVCLASS](https://i.ibb.co/G79L8Q1/image.png)

Por lo tanto, al realizar la carga masiva se deberá de escribir el nombre del archivo junto a la extensión .json

![INVCLASS](https://i.ibb.co/SxtpLZR/image.png)

## Gestión de Usuarios
El administrador tiene el control de poder eliminar usuarios de la aplicación ingresando el correo electrónico de dicho usuario.

![INVCLASS](https://i.ibb.co/94TFCgW/image.png)

## Reportes
Se redirige al usuario a un nuevo menú con más opciones:
![INVCLASS](https://i.ibb.co/TYjJ5Ry/image.png)

### Reporte de usuarios
El sistema muestra una estructura simulando una lista enlazada que contiene la información de los usuarios registrados.

![INVCLASS](https://i.ibb.co/r39FmFT/reporte-Usuarios.png)

### Reporte de publicaciones
El sistema muestra una estructura simulando una lista doblemente enlazada con las publicaciones que todos los usuarios han realizado en la aplicación.

![INVCLASS](https://i.ibb.co/pWvhtJk/reporte-Publicaciones.png)

### Top 5
En este apartado, se despliega un listado con las 5 personas que más publicaciones han realizado en la aplicación junto con su correo y la cantidad de publicaciones

![INVCLASS](https://i.ibb.co/xGdbfR0/image.png)


## Usuario
### Ver perfil
En esta sección se muestra la información personal del usuario junto a las publicaciones que ha realizado.

![INVCLASS](https://i.ibb.co/vqWL1Bz/image.png)


### Eliminar perfil
El usuario es capaz de eliminar su perfil si así lo desea, únicamente se le pide confirmar antes de realizar la operación.

![INVCLASS]()


### Ver solicitudes
El sistema le muestra al usuario cada una de las solicitudes que tiene pendientes de responder, será el usuario quien decida si la acepta o rechaza.

![INVCLASS](https://i.ibb.co/Yb8rJfX/image.png)

### Enviar solicitud
Si un usuario quiere enviarle una solicitud de amistad a otro usuario debe ingresar su correo para poder enviarla y estar a la espera de que el receptor la acepte o rechace.

![INVCLASS](https://i.ibb.co/T4Wnq8b/image.png)

### Publicaciones
Se despliega un nuevo menú con las siguientes opciones

![INVCLASS](https://i.ibb.co/pPF65Zx/image.png)

* Ver publicaciones: Se muestran las publicaciones que el usuario ha realizado con la capacidad de ver cada una de ellas pudiendo retroceder o avanzar si así lo desea.

![INVCLASS](https://i.ibb.co/Tv89dzD/image.png)

* Crear una nueva publicación: Por ser una aplicación de consola, el usuario solamente puede ingresar texto a su comentario tomando en cuenta que se almacenan automáticamente la fecha y hora que lo realizó.

![INVCLASS](https://i.ibb.co/0n6M73Z/image.png)

* Eliminar una publicación: En algunas ocasiones los usuarios pueden decidir eliminar sus publicaciones por diferentes motivos por lo que se implementó esta funcionalidad donde únicamente debe ingresar el ID de la publicación a eliminar.

![INVCLASS](https://i.ibb.co/pZvLDdN/image.png)

### Reportes
Este menú tiene varias opciones a elegir
* Reporte de solicitudes: Se muestran dos gráficas a la vez, una representa una lista de solicitudes que el usuario a emitido a otros usuarios y una pila con las solicitudes que ha recibido y tiene pendiente respoder.

Pila de solicitudes recibidas

![INVCLASS](https://i.ibb.co/VpPv374/reporte-Usuarios.png)

Lista de solicitudes enviadas

![INVCLASS](https://i.ibb.co/m0Mgvz3/reporte-Solicitudes.png)

* Publicaciones: El usuario puede visualizar gráficamente una lista con todas las publicaciones que ha realizado dentro de la aplicación. A diferencia del administrador, el usuario únicamente puede visualizar sus publicaciones y no las del resto.

![INVCLASS](https://i.ibb.co/6Wt4Xs0/reporte-Publicaciones.png)

### Salir del programa
Para terminar de ejecutar el programa únicamente se debe ingresar la opción 4 al haber cerrado sesión y devolverse al menú principal.

![INVCLASS](https://i.ibb.co/ZBSmyHF/image.png)