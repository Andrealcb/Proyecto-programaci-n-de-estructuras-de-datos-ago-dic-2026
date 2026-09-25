#include "Admin.h"

Administrador::Administrador() : Usuario() {}

Administrador::Administrador(int id, const std::string& usuario, const std::string& contrasena)
    : Usuario(id, usuario, contrasena) {}

std::string Administrador::getTipo() const {
    return "Administrador";
}
