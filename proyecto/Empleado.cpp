#include "Empleado.h"

Empleado::Empleado() : Usuario() {}

Empleado::Empleado(int id, const std::string& usuario, const std::string& contrasena)
    : Usuario(id, usuario, contrasena) {}

std::string Empleado::getTipo() const {
    return "Empleado";
}

