#ifndef ADMIN_H
#define ADMIN_H

#include "Usuario.h"

class Administrador : public Usuario {
public:
    Administrador();
    Administrador(int id, const std::string& usuario, const std::string& contrasena);

    std::string getTipo() const override;
};

#endif
