#ifndef GERENTE_H
#define GERENTE_H

#include "Usuario.h"

class Gerente : public Usuario {
public:
    Gerente();
    Gerente(int id, const std::string& usuario, const std::string& contrasena);

    std::string getTipo() const override;
};

#endif
