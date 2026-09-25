#include "Carrito.h"

/*
 * Agrega un producto al carrito. Si ya existe (mismo código en índice 2) suma cantidades.
 */
void Carrito::agregar(const std::vector<std::string>& productoRow, int cantidad) {
    for (auto &it : items) {
        if (!it.productoRow.empty() && !productoRow.empty() && it.productoRow[2] == productoRow[2]) {
            it.cantidad += cantidad;
            return;
        }
    }
    ItemCarrito nuevo;
    nuevo.productoRow = productoRow;
    nuevo.cantidad = cantidad;
    items.push_back(nuevo);
}

/* Retorna si el carrito está vacío */
bool Carrito::estaVacio() const {
    return items.empty();
}

/* Limpia el carrito */
void Carrito::limpiar() {
    items.clear();
}

/* Calcula el total (lee el precio en productoRow[3]) */
double Carrito::total() const {
    double suma = 0.0;
    for (const auto &it : items) {
        double precio = 0.0;
        if (it.productoRow.size() >= 4) {
            try { precio = std::stod(it.productoRow[3]); } catch(...) { precio = 0.0; }
        }
        suma += precio * it.cantidad;
    }
    return suma;
}

/* Devuelve referencia a los items */
const std::vector<ItemCarrito>& Carrito::getItems() const {
    return items;
}
