#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
using namespace std;

class Producto {
private:
    int id;
    string nombre;
    string codigo;
    double precio;
    int cantidad;

public:
    Producto();
    Producto(int id, string nombre, string codigo, double precio, int cantidad);

    // Getters
    int getId() const;
    string getNombre() const;
    string getCodigo() const;
    double getPrecio() const;
    int getCantidad() const;

    // Setters
    void setNombre(string nombre);
    void setCodigo(string codigo);
    void setPrecio(double precio);
    void setCantidad(int cantidad);

    void mostrar() const;
    bool vender(int cant);
};

#endif
