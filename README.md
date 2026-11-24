# Evidencia problemas de programación

En este apartado se encuentran los tres problemas seleccionados y resueltos para la actividad, junto con sus respectivos videos de explicación.

## 1. Algoritmos de ordenamiento

**Problema:** [2164. Sort Even and Odd Indices Independently](https://leetcode.com/problems/sort-even-and-odd-indices-independently/)

**Dificultad:** Fácil

**Video de explicación:** [Ver video](https://youtu.be/clb2FBrB5gk)

## 2. Estructuras de datos lineales

**Problema:** [225. Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)

**Dificultad:** Fácil

**Video de explicación:** [Ver video](https://youtu.be/wdgxKQT1z5Y)

## 3. Estructuras de datos no lineales

**Problema:** [200. Number of Islands](https://leetcode.com/problems/number-of-islands/)

**Dificultad:** Media

**Video de explicación:** [Ver video](https://youtu.be/e1bdmnm8_LQ)



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

Se utilizan vectores dinámicos para almacenar los equipos, personajes y los resultados de las consultas hechas por el usuario, ya que la cantidad de elementos puede aumentar al ser un juego que lanza nuevos personajes cada cierto tiempo y con los arreglos también estamos seguros para los equipos, debido a que el numero de personajes que puede tener un equipo no va a cambiar (lo más seguro). 
Su complejidad, en los dinámicos cuando accede a un elemento se tiene O(1) en todos los casos, ya que se accede por el índice y esto es directo, cuando recorre los elementos es de O(n) y cuando lo busca sin que este ordenado previamente es de O(n).
Y en los estáticos que se usan para guardar los 4 personajes de los equipos, como se ingresa por índice es de O(1), en los recorridos de los 4 personajes de O(1) ya que siempre será la misma cantidad.


## SICT0303: Implementa acciones científicas

### Implementa mecanismos para consultar información de las estructuras correctos.

Aquí se implementan mecanismos para filtrar y visualizar info de los personajes y equipos. Que son los de búsqueda de personajes seleccionados, comparación de nombres para evitar repetidos, para las mayúsculas y minúsculas (en la entrega anterior no lo tenía) y la distinción de personajes de 4 y 5 estrellas, se hace con ifstream y stringstream.
En los de lectura, se utilizan 2 archivos CSV para almacenar la info necesaria para el programa. En equipos.csv están los equipos y toda la info de estos, en personajes.csv esta el nombre del personaje y si es de 4 ó 5 estrellas.
Para guardar, se usa ofstream para guardar los cambio hechos por el usuario al usar el programa, para guardar un nuevo equipo de usa ios::app.  



