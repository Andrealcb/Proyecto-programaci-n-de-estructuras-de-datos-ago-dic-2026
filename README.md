# Proyecto-programación-de-estructuras-de-datos-ago-dic-2026
## Avance 2 de proyecto

En este avance, presentare un tipo de gestor de equipos para Genshin Impact, puede hacer lo siguiente:

* Decirte que equipos son los mejores con respecto a que cantidad de personajes pongas 1,2,3.
* En las primeras 3 opciones completa el equipo con los personajes que le conviene al equipo según, la base de datos 
* En la cuarta es meramente para obtener la rotación.

  
* Solución de errores...

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

Esta vez seleccione el algoritmo Merge Sort, ya que tiene una complejidad de 0(n log n) tanto en el mejor y el peor caso, lo que quiere decir que casi siempre mantiene el mismo rendimiento, también hace que al encontrar dos equipo con el mismo daño los ponga de acuerdo a su orden original, no modifica el orden de los equipo en el archivo original algo que realmente no es necesario tomando en cuenta que no siempre se buscaran los mismos personajes y debido como anteriormente se menciono al tener una complejidad 0(n log n) tanto en el mejor y el peor de los casos se asegura la estabilidad en caso de tener muchos datos, lo cual si seria posible al haber más de 150 personajes que van en aumento.

## SICT0302: Toma decisiones

### Selecciona una estructura de datos adecuada al problema y la usa correctamente.

Se utiliza un vectores dinámicos y arreglos estáticos, ya que permiten almacenar y recorrer catálogos sin importar el tamaño, con acceso directo sin importar que se aumenten datos recientemente, aquí se tiene una complejidad 0(n) por la cantidad de personajes buscados y los integrantes de cada equipo (que solo son 4).

## SICT0303: Implementa acciones científicas

### Implementa mecanismos para consultar información de las estructuras correctos.
Aquí se implementan mecanismos de consulta para filtrar y visualizar toda la info de los personajes y equipos. Esto sirve en el programa  para acceder a los datos almacenados y consultarlos a la hora de que el usuario seleccione los filtros.

