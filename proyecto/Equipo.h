#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include <vector>

struct Equipo {
    std::string nombreEquipo;
    std::string reaccion;
    long long danoTotal;
    std::string miembros[4];
};

struct PersonajeInfo {
    std::string nombre;
    int estrellas;
};

bool cargarEquipos(const std::string& nombreArchivo, std::vector<Equipo>& lista);
bool cargarPersonajesInfo(const std::string& nombreArchivo, std::vector<PersonajeInfo>& lista);
std::vector<Equipo> consultarPorPersonajes(const std::vector<Equipo>& lista, const std::vector<std::string>& personajesBuscados);
void ordenarPorDanoInsercion(std::vector<Equipo>& lista);

#endif