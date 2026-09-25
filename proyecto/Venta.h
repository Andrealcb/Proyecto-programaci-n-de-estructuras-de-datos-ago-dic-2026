#ifndef VENTA_H
#define VENTA_H

#include <string>

/*
 * Estructura Venta: guarda los datos de una venta registrada
 */
struct Venta {
    int id;
    std::string producto;
    int cantidad;
    double precio_unitario;
    double total;
    std::string vendedor;
    std::string rango;
    std::string fecha_hora; // "YYYY-MM-DD HH:MM:SS"
    
};



#endif
