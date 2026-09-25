#include "Gerente.h"

Gerente::Gerente() : Usuario() {}

Gerente::Gerente(int id, const std::string& usuario, const std::string& contrasena)
    : Usuario(id, usuario, contrasena) {}

std::string Gerente::getTipo() const {
    return "Gerente";
}
