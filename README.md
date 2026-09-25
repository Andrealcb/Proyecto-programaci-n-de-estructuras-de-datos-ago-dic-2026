# Proyecto-programación-de-estructuras-de-datos-ago-dic-2026
## Avance 1 de proyecto

En este avance, utilice un proyecto pasado sobre un punto de venta para una tienda, puede hacer lo siguiente:

* Crear productos con nombre, código, precio y cantidad.
* Registrar usuarios mediante herencia (Administrador, Gerente, Empleado).
* Agregar productos al carrito.
* Realizar ventas y actualizar el inventario.
* Mostrar el inventario existente.
* Generar tickets de compra.

---

## ¿Cómo se usa el programa?

### 1. Compilar

En consola:

```cmd
poner la direccion de la carpeta con los archivos y poner cd "Direccion"

y luego:
 
g++ main.cpp Tienda.cpp Producto.cpp Usuario.cpp Admin.cpp Gerente.cpp Empleado.cpp Carrito.cpp -o tienda
```

### **2. Ejecutar**


./tienda o solo tienda.

Cuando entres al comienzo, te preguntara que tipo de usuario eres, ingrese como administrador, el usuario es: Admin y contraseña: 1234.

Y asi ya podras interactuar con el menú y todo lo demás del programa.

El menú muestra opciones como:

* Ver productos
* Agregar productos (solo Admin)
* Agrgar gerentes o empleados (depende el rango)
* Comprar
* Ver carrito
* Salir
* Y más...

Las opciones del menú dependeran de que rango eres, entre más alto el rango mas opciones tendrás.

---

## Sub-competencias

Coloque la librería de algorithm, para poner el algoritmo de ordenamiento, en el código esta implementado para la sección de reporte de ventas, para ordenar el numero de ventas de los productos, yo creo que puede funcionar para que el gerente o administrador pueda ver que cosas se venden mas y cuales menos y asi tener mas stock disponible para eso o eliminar productos que no se venden.
