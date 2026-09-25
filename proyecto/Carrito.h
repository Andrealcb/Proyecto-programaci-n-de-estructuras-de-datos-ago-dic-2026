#ifndef CARRITO_H
#define CARRITO_H

#include <vector>
#include <string>

struct ItemCarrito {
    std::vector<std::string> productoRow;
    int cantidad;
};

/*
 * Carrito: administra una lista de ItemCarrito para la venta actual.
 */
class Carrito {
private:
    std::vector<ItemCarrito> items;
    int cantidad = 0; 
public:
    void agregar(const std::vector<std::string>& productoRow, int cantidad);
    bool estaVacio() const;
    void limpiar();
    double total() const;
    const std::vector<ItemCarrito>& getItems() const;
};

#endif
