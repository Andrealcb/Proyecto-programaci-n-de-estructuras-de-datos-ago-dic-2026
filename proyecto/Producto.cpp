#include "Producto.h"
#include <iostream>

Producto::Producto() : id(0), nombre(""), codigo(""), precio(0), cantidad(0) {}

Producto::Producto(int id, string nombre, string codigo, double precio, int cantidad)
    : id(id), nombre(nombre), codigo(codigo), precio(precio), cantidad(cantidad) {}

int Producto::getId() const { return id; }
string Producto::getNombre() const { return nombre; }
string Producto::getCodigo() const { return codigo; }
double Producto::getPrecio() const { return precio; }
int Producto::getCantidad() const { return cantidad; }

void Producto::setNombre(string nombre) { this->nombre = nombre; }
void Producto::setCodigo(string codigo) { this->codigo = codigo; }
void Producto::setPrecio(double precio) { this->precio = precio; }
void Producto::setCantidad(int cantidad) { this->cantidad = cantidad; }

void Producto::mostrar() const {
    cout << "ID: " << id << " | " << nombre << " | Cod: " << codigo
         << " | $" << precio << " | Stock: " << cantidad << endl;
}

bool Producto::vender(int cant) {
    if (cant <= cantidad) {
        cantidad -= cant;
        return true;
    }
    return false;
}

