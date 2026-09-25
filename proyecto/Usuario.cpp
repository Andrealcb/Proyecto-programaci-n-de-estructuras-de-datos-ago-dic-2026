#include "Usuario.h"

Usuario::Usuario() : id(-1), usuario(""), contrasena("") {}

Usuario::Usuario(int id, const std::string& usuario, const std::string& contrasena)
    : id(id), usuario(usuario), contrasena(contrasena) {}

int Usuario::getId() const { return id; }
std::string Usuario::getUsuario() const { return usuario; }
std::string Usuario::getContrasena() const { return contrasena; }

void Usuario::setUsuario(const std::string& u) { usuario = u; }
void Usuario::setContrasena(const std::string& p) { contrasena = p; }
