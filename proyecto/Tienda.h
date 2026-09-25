#ifndef TIENDA_H
#define TIENDA_H

#include "Admin.h"
#include "Gerente.h"
#include "Empleado.h"
#include <vector>
#include <string>
#include "Producto.h"
#include "Usuario.h"
#include "Venta.h"
#include "Carrito.h"


class Tienda {
private:
	
    std::vector<Venta> ventas_registradas = {
        {1, "Coca Cola", 2, 20.0, 40.0,
         "Andrea", "Gerente", "2026-09-20 10:30:00"},
         
        {2, "Sabritas", 7, 18.0, 126.0,
         "Carlos", "Empleado", "2026-09-20 11:15:00"},

        {3, "Galletas", 3, 15.0, 45.0,
         "Andrea", "Gerente", "2026-09-20 12:00:00"}
    };
   
    std::vector<Producto> productos = {
    {1, "Coca Cola", "001", 20.0, 50},
    
    {2, "Sabritas", "002", 18.0, 30},
    
    {3, "Galletas", "003", 15.0, 40}
    };
    
    std::vector<Empleado> empleados = {
    {1, "Carlos", "5678"}
    };
    
    std::vector<Gerente> gerentes = {
    {1, "Andrea", "2308"}
    };
    
    std::vector<Administrador> administradores = {
    {1, "Admin","1234"}
    };

    std::vector<std::vector<std::string>> reporte_ventas;

    // IDs automáticos
    int nextProductoId;
    int nextUsuarioId;
    int nextVentaId;

    // Helpers
    std::string nowString() const;
    std::string readLine(const std::string& prompt = "") const;
    double parseDouble(const std::string& s) const;
    int parseInt(const std::string& s) const;

    int indexProductoPorCodigo(const std::string& codigo) const;
    bool codigoExiste(const std::string& codigo) const;
    bool usuarioExisteEnColeccion(const std::string& nombre) const;

public:
    Tienda();

    // Inicialización
    void crearTablas();

    // Productos
    void agregarProducto();
    void buscarProductoPorCodigo() const;
    void modificarProducto();
    void eliminarProducto();
    void mostrarProductos() const;

    // Usuarios
    void agregarGerente();
    void agregarEmpleado();
    void modificarGerente();
    void modificarEmpleado();
    void eliminarGerente();
    void eliminarEmpleado();
    void mostrarUsuarios() const;
    void mostrarUsuariosCombinados() const;

    // Ventas / Carrito
    void venderProducto(const std::string& nombre_usuario = "Desconocido",
                        const std::string& rango = "Desconocido");

    void registrarVenta(
        const std::vector<std::pair<std::vector<std::string>,int>>& productos_a_vender,
        double total_venta,
        const std::string& usuario,
        const std::string& rango
    );

    // Reportes
    void mostrarReporteVentas() const;

    // Login
    std::vector<std::string> siAdministrador() const;
    std::vector<std::string> siGerente() const;
    std::vector<std::string> siEmpleado() const;
    void administradorNo();

    // Run / Menú
    void run();
};

#endif