#ifndef EMPLEADO_H
#define EMPLEADO_H

#include "Usuario.h"

class Empleado : public Usuario {
public:
    Empleado();
    Empleado(int id, const std::string& usuario, const std::string& contrasena);

    std::string getTipo() const override;
};

#endif
