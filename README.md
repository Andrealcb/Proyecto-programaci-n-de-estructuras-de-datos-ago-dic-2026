# Proyecto-programación-de-estructuras-de-datos-ago-dic-2026
## Avance 1 de proyecto

En este avance, presentare un tipo de gestor de equipos para Genshin Impact, puede hacer lo siguiente:

* Decirte que equipos son los mejores con respecto a que cantidad de personajes pongas 1,2,3.
* En las primeras 3 opciones completa el equipo con los personajes que le conviene al equipo según, la base de datos 
* En la cuarta es meramente para obtener la rotación.

---

## ¿Cómo se usa el programa?

### 1. Compilar

En consola:

```cmd
poner la direccion de la carpeta con los archivos y poner cd "Direccion"

y luego:
 
g++ main.cpp -o nombre

```

### **2. Ejecutar**


./nombre o solo nombre.

Al entrar te aparecerá el menú donde puedes escoger cualquiera de las opciones dependiendo de que personajes quieras poner.

---

## SICT0302: Toma decisiones

### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.

Bueno, yo utilice el algoritmo de ordenamiento Inserción, debido a que es mas eficiente en este caso en donde solo se realizan ciertas cantidades de equipos, me parece mas rápido y limpio, además que mantiene el orden original en caso de resultar equipos con el mismo daño. 


## SICT0302: Toma decisiones

### Selecciona una estructura de datos adecuada al problema y la usa correctamente.

Aquí utilice arreglos estáticos t dinámicos para poder poner la información de los personajes y sus respectivos equipos de una manera mas limpia y organizada, el usar un arreglo estático se justifica ya que siempre serán 4 personajes en el equipo. 

## SICT0303: Implementa acciones científicas

### Implementa mecanismos para consultar información de las estructras correctos.

Con consultarPorPersonajes() se pueden realizar búsquedas fácilmente para los personajes que se quiere, buscando a los personajes que se pusieron al inicio después de seleccionar la cantidad. 
 
### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.

Se implemento la función cargarEquipos() y cargarPersonajesInfo(), para procesar la info de los archivos .csv, aqui se utilizan para almacenar las variables en la memoria para poder seguir agregando personajes de manera sencilla desde el .cvs.
