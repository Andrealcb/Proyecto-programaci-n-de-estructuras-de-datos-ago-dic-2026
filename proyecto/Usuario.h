#ifndef USUARIO_H
#define USUARIO_H

#include <string>

/*
 * Representa un usuario del sistema
 */
class Usuario {
protected:
    int id;
    std::string usuario;
    std::string contrasena;

public:
    Usuario();
    Usuario(int id, const std::string& usuario, const std::string& contrasena);
    virtual ~Usuario() {}

    int getId() const;
    std::string getUsuario() const;
    std::string getContrasena() const;

    void setUsuario(const std::string& u);
    void setContrasena(const std::string& p);

    // Método virtual 
    virtual std::string getTipo() const = 0;
};

#endif
