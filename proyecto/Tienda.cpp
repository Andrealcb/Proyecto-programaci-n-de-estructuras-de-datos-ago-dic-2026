#include "Tienda.h"
#include "Admin.h"
#include "Gerente.h"
#include "Empleado.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <cctype>


using namespace std;

/* Constructor */
Tienda::Tienda() : nextProductoId(1), nextUsuarioId(1), nextVentaId(1) {}

/* Devuelve fecha y hora actual en formato "YYYY-MM-DD HH:MM:SS" */
string Tienda::nowString() const {
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    tm local_tm;
#ifdef _WIN32
    localtime_s(&local_tm, &t);
#else
    localtime_r(&t, &local_tm);
#endif
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local_tm);
    return string(buf);
}

/* Lectura de línea con prompt */
string Tienda::readLine(const string& prompt) const {
    if (!prompt.empty()) cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

/* Parse helpers */
double Tienda::parseDouble(const string& s) const {
    try { return stod(s); } catch(...) { return 0.0; }
}
int Tienda::parseInt(const string& s) const {
    try { return stoi(s); } catch(...) { return 0; }
}

/* Busca índice de producto por código */
int Tienda::indexProductoPorCodigo(const string& codigo) const {
    for (size_t i = 0; i < productos.size(); ++i)
        if (productos[i].getCodigo() == codigo) return (int)i;
    return -1;
}

/* Indica si existe el código */
bool Tienda::codigoExiste(const string& codigo) const {
    return indexProductoPorCodigo(codigo) != -1;
}

/* Verifica si existe un usuario con ese nombre en cualquier colección */
bool Tienda::usuarioExisteEnColeccion(const string& nombre) const {
    for (const auto& a : administradores) if (a.getUsuario() == nombre) return true;
    for (const auto& g : gerentes) if (g.getUsuario() == nombre) return true;
    for (const auto& e : empleados) if (e.getUsuario() == nombre) return true;
    return false;
}

/* Crear tablas (simulado) */
void Tienda::crearTablas() {
    cout << "Tablas listas." << endl;
}

/* productos */
void Tienda::agregarProducto() {
    cout << "\n--- Agregar Producto ---\n";
    string nombre = readLine("Ingrese el nombre del producto: ");
    string codigo = readLine("Ingrese el código del producto: ");
    if (codigo.empty()) { cout << "Codigo no puede ser vacío.\n"; return; }
    if (codigoExiste(codigo)) {
        cout << "El codigo ingresado ya existe. Intente con uno unico.\n";
        return;
    }
    string sPrecio = readLine("Ingrese el precio unitario del producto: ");
    double precio = parseDouble(sPrecio);
    string sCant = readLine("Ingrese la cantidad en stock del producto: ");
    int cantidad = parseInt(sCant);

    Producto p(nextProductoId++, nombre, codigo, precio, cantidad);
    productos.push_back(p);
    cout << "Producto agregado exitosamente.\n";
}

void Tienda::buscarProductoPorCodigo() const {
    cout << "\n--- Buscar Producto ---\n";
    string codigo = readLine("Ingrese el codigo del producto: ");
    int idx = -1;
    for (size_t i = 0; i < productos.size(); ++i) {
        if (productos[i].getCodigo() == codigo) { idx = (int)i; break; }
    }
    if (idx == -1) {
        cout << "Producto no encontrado.\n";
        return;
    }
    const Producto& p = productos[idx];
    cout << "Producto encontrado: Nombre: " << p.getNombre()
         << ", Código: " << p.getCodigo()
         << ", Precio Unitario: " << fixed << setprecision(2) << p.getPrecio()
         << ", Cantidad en stock: " << p.getCantidad()
         << "\n";
}

void Tienda::modificarProducto() {
    cout << "\n--- Modificar Producto ---\n";
    string codigo = readLine("Ingrese el codigo del producto a modificar: ");
    int idx = indexProductoPorCodigo(codigo);
    if (idx == -1) { cout << "Producto no encontrado.\n"; return; }
    Producto &p = productos[idx];
    cout << "Producto encontrado: Nombre: " << p.getNombre() << ", Codigo: " << p.getCodigo()
         << ", Precio: " << p.getPrecio() << ", Stock: " << p.getCantidad() << "\n";
    string nombre = readLine("Nuevo nombre (enter para dejar): ");
    string precio = readLine("Nuevo precio (enter para dejar): ");
    string cantidad = readLine("Nueva cantidad (enter para dejar): ");

    if (!nombre.empty()) p.setNombre(nombre);
    if (!precio.empty()) p.setPrecio(parseDouble(precio));
    if (!cantidad.empty()) p.setCantidad(parseInt(cantidad));
    cout << "Producto modificado correctamente.\n";
}

void Tienda::eliminarProducto() {
    cout << "\n--- Eliminar Producto ---\n";
    string codigo = readLine("Ingrese el código del producto a eliminar: ");
    int idx = indexProductoPorCodigo(codigo);
    if (idx == -1) { cout << "No se encontró ningún producto con ese codigo.\n"; return; }
    productos.erase(productos.begin() + idx);
    cout << "Producto eliminado correctamente.\n";
}

void Tienda::mostrarProductos() const {
    cout << "\n--- Productos ---\n";
    if (productos.empty()) { cout << "No hay productos registrados.\n"; return; }
    for (const auto& p : productos) p.mostrar();
}

/* usuarios */
void Tienda::agregarGerente() {
    cout << "\n--- Agregar Gerente ---\n";
    string nombre = readLine("Ingrese el nombre de usuario(gerente): ");
    if (nombre.empty()) { cout << "Usuario no puede ser vacio.\n"; return; }
    if (usuarioExisteEnColeccion(nombre)) { cout << "Usuario ya existe.\n"; return; }
    string pass = readLine("Ingrese contraseña: ");
    Gerente g(nextUsuarioId++, nombre, pass);
    gerentes.push_back(g);
    cout << "Gerente agregado.\n";
}

void Tienda::agregarEmpleado() {
    cout << "\n--- Agregar Empleado ---\n";
    string nombre = readLine("Ingrese el nombre de usuario(empleado): ");
    if (nombre.empty()) { cout << "Usuario no puede ser vacio.\n"; return; }
    if (usuarioExisteEnColeccion(nombre)) { cout << "Usuario ya existe.\n"; return; }
    string pass = readLine("Ingrese contraseña: ");
    Empleado e(nextUsuarioId++, nombre, pass);
    empleados.push_back(e);
    cout << "Empleado agregado.\n";
}

void Tienda::modificarGerente() {
    cout << "\n--- Modificar Gerente ---\n";
    string user = readLine("Ingrese el Usuario que desea modificar: ");
    for (auto &g : gerentes) {
        if (g.getUsuario() == user) {
            cout << "Usuario encontrado: " << g.getUsuario() << "\n";
            string nuevo = readLine("Nuevo nombre (enter para dejar): ");
            string pass = readLine("Nueva contraseña (enter para dejar): ");
            if (!nuevo.empty()) g.setUsuario(nuevo);
            if (!pass.empty()) g.setContrasena(pass);
            cout << "Gerente modificado.\n";
            return;
        }
    }
    cout << "Usuario no encontrado.\n";
}

void Tienda::modificarEmpleado() {
    cout << "\n--- Modificar Empleado ---\n";
    string user = readLine("Ingrese el Usuario que desea modificar: ");
    for (auto &e : empleados) {
        if (e.getUsuario() == user) {
            cout << "Usuario encontrado: " << e.getUsuario() << "\n";
            string nuevo = readLine("Nuevo nombre (enter para dejar): ");
            string pass = readLine("Nueva contraseña (enter para dejar): ");
            if (!nuevo.empty()) e.setUsuario(nuevo);
            if (!pass.empty()) e.setContrasena(pass);
            cout << "Empleado modificado.\n";
            return;
        }
    }
    cout << "Usuario no encontrado.\n";
}

void Tienda::eliminarGerente() {
    cout << "\n--- Eliminar Gerente ---\n";
    string user = readLine("Ingrese el Usuario que desea eliminar: ");
    auto it = remove_if(gerentes.begin(), gerentes.end(), [&](const Gerente& u){ return u.getUsuario() == user; });
    if (it != gerentes.end()) { gerentes.erase(it, gerentes.end()); cout << "Usuario eliminado.\n"; }
    else cout << "Usuario no encontrado.\n";
}

void Tienda::eliminarEmpleado() {
    cout << "\n--- Eliminar Empleado ---\n";
    string user = readLine("Ingrese el Usuario que desea eliminar: ");
    auto it = remove_if(empleados.begin(), empleados.end(), [&](const Empleado& u){ return u.getUsuario() == user; });
    if (it != empleados.end()) { empleados.erase(it, empleados.end()); cout << "Usuario eliminado.\n"; }
    else cout << "Usuario no encontrado.\n";
}

void Tienda::mostrarUsuarios() const {
    cout << "\n--- Empleados ---\n";
    if (empleados.empty()) cout << "No hay empleados.\n";
    for (const auto& e : empleados) cout << "Usuario: " << e.getUsuario() << " | Pass: " << e.getContrasena() << "\n";
}

void Tienda::mostrarUsuariosCombinados() const {
    cout << "\n--- Gerentes ---\n";
    for (const auto& g : gerentes) cout << "Gerente: " << g.getUsuario() << " | Pass: " << g.getContrasena() << "\n";
    cout << "\n--- Empleados ---\n";
    for (const auto& e : empleados) cout << "Empleado: " << e.getUsuario() << " | Pass: " << e.getContrasena() << "\n";
}

/* ventas */
void Tienda::venderProducto(const string& nombre_usuario, const string& rango) {
    cout << "\n--- Vender Producto ---\n";
    Carrito carrito;
    while (true) {
        string codigo = readLine("Ingrese el código del producto que desea vender (o 'fin' para terminar): ");
        string low = codigo; for (auto &c : low) c = tolower(c);
        if (low == "fin") break;
        int idx = indexProductoPorCodigo(codigo);
        if (idx == -1) { cout << "Producto no encontrado.\n"; continue; }
        const Producto &p = productos[idx];
        cout << "Producto encontrado: Nombre: " << p.getNombre()
             << ", Código: " << p.getCodigo()
             << ", Precio Unitario: " << fixed << setprecision(2) << p.getPrecio()
             << ", Cantidad en stock: " << p.getCantidad() << "\n";
        string sCant = readLine("Ingrese la cantidad a vender: ");
        int cantidad_v = parseInt(sCant);
        if (cantidad_v <= 0) { cout << "Cantidad inválida.\n"; continue; }
        if (p.getCantidad() < cantidad_v) { cout << "No hay suficiente stock.\n"; continue; }
        vector<string> fila = { to_string(p.getId()), p.getNombre(), p.getCodigo(), to_string(p.getPrecio()), to_string(p.getCantidad()) };

    }

    if (carrito.estaVacio()) { cout << "No se realizo ninguna venta.\n"; return; }

    double total_venta = carrito.total();
    cout << fixed << setprecision(2);
    cout << "Total a pagar: $" << total_venta << "\n";
    double pago = 0.0;
    while (true) {
        string sPago = readLine("Ingrese el monto con el que paga: $");
        pago = parseDouble(sPago);
        if (pago >= total_venta) break;
        cout << "Monto insuficiente. Intente de nuevo.\n";
    }
    double cambio = pago - total_venta;

    // actualizar stock
    for (const auto &it : carrito.getItems()) {
        string codigo = "";
        if (it.productoRow.size() >= 3) codigo = it.productoRow[2];
        int cantV = it.cantidad;
        int idx = indexProductoPorCodigo(codigo);
        if (idx != -1) {
            int nueva = productos[idx].getCantidad() - cantV;
            productos[idx].setCantidad(nueva);
        }
    }

    // imprimir ticket
    cout << "\n--- Ticket de Compra ---\n";
    cout << "Nombre de la Tienda\n";
    cout << "Direccion ejemplo\n";
    cout << "Tel: 9123456\n";
    cout << "------------------------\n";
    for (const auto &it : carrito.getItems()) {
        cout << "Producto: " << it.productoRow[1] << "\n";
        cout << "Codigo: " << it.productoRow[2] << "\n";
        cout << "Cantidad vendida: " << it.cantidad << "\n";
        double precio = 0.0;
        try { precio = stod(it.productoRow[3]); } catch(...) { precio = 0.0; }
        cout << "Precio unitario: $" << precio << "\n";
        cout << "------------------------\n";
    }
    cout << "Total de la venta: $" << total_venta << "\n";
    cout << "Pago recibido: $" << pago << "\n";
    cout << "Cambio: $" << cambio << "\n";
    cout << "------------------------\n";
    cout << "Gracias por su compra.\n";

    vector<pair<vector<string>,int>> lista;
    for (const auto &it : carrito.getItems()) lista.push_back({ it.productoRow, it.cantidad });

    registrarVenta(lista, total_venta, nombre_usuario.empty() ? "Desconocido" : nombre_usuario, rango.empty() ? "Desconocido" : rango);
    carrito.limpiar();
}

void Tienda::registrarVenta(const vector<pair<vector<string>,int>>& productos_a_vender, double total_venta, const string& usuario, const string& rango) {
    string fecha = nowString();
    for (const auto &pr : productos_a_vender) {
        Venta v;
        v.id = nextVentaId++;
        v.producto = pr.first[1];
        v.cantidad = pr.second;
        try { v.precio_unitario = stod(pr.first[3]); } catch(...) { v.precio_unitario = 0.0; }
        v.total = v.precio_unitario * v.cantidad;
        v.vendedor = usuario;
        v.rango = rango;
        v.fecha_hora = fecha;
        ventas_registradas.push_back(v);

        vector<string> fila = { v.producto, to_string(v.cantidad), to_string(v.precio_unitario), to_string(v.total), v.vendedor, v.rango, v.fecha_hora };
        reporte_ventas.push_back(fila);
    }
}

/* reportes */
void Tienda::mostrarReporteVentas() const {
    cout << "\n--- REPORTE DE VENTAS ---\n";
    string desde;
    cout << "Ingrese fecha de inicio (YYYY-MM-DD): ";
    getline(cin, desde);
    string hasta;
    cout << "Ingrese fecha final (YYYY-MM-DD): ";
    getline(cin, hasta);
    string desde_ts = desde + " 00:00:00";
    string hasta_ts = hasta + " 23:59:59";

    // Crear vector con las ventas del periodo seleccionado
    vector<Venta> ventas_filtradas;

    for (const auto &v : ventas_registradas) {
        if (v.fecha_hora >= desde_ts && v.fecha_hora <= hasta_ts) {
            ventas_filtradas.push_back(v);
        }
    }

    // Preguntar si desea ordenar
    string ordenventas;
    cout << "\n¿Desea ordenar el reporte de ventas?\n 1.- Si\n 2.- No\n";
    cout << "Opción: ";
    getline(cin, ordenventas);

    if (ordenventas == "1") {

        cout << "\n¿En qué orden?\n 1.- Cantidad de ventas ascendente\n 2.- Cantidad de ventas descendente\n";
        string opt = readLine("Opción: ");
        int largo = ventas_filtradas.size();
        if (opt == "1") {
            std::sort(ventas_filtradas.begin(), ventas_filtradas.end(),
             [](const Venta& a, const Venta& b) {
              return a.cantidad < b.cantidad;
            }
            );
        }
        else if (opt == "2") {
            std::sort(ventas_filtradas.begin(), ventas_filtradas.end(),
           [](const Venta& a, const Venta& b) {
            return a.cantidad > b.cantidad;
            }
            );
        }
    }

    // Mostrar reporte
    cout << "\n";
    cout << left
         << setw(20) << "Fecha/Hora" << " "
         << setw(15) << "Producto" << " "
         << setw(6) << "Cant" << " "
         << setw(8) << "P.Unit" << " "
         << setw(8) << "Total" << " "
         << setw(15) << "Vendedor" << " "
         << setw(10) << "Rango"
         << "\n";

    cout << string(100, '=') << "\n";

    for (const auto &v : ventas_filtradas) {

        cout << left
             << setw(20) << v.fecha_hora << " "
             << setw(15) << v.producto << " "
             << setw(6) << v.cantidad << " "
             << setw(8) << v.precio_unitario << " "
             << setw(8) << v.total << " "
             << setw(15) << v.vendedor << " "
             << setw(10) << v.rango
             << "\n";
    }
}

/* login */
vector<string> Tienda::siAdministrador() const {
    vector<string> res;
    cout << "\nIngrese usuario y contraseña:\n";
    string u, p;
    cout << "Usuario: "; getline(cin, u);
    cout << "Contraseña: "; getline(cin, p);
    for (const auto &a : administradores) {
        if (a.getUsuario() == u && a.getContrasena() == p) {
            res = { to_string(a.getId()), a.getUsuario(), a.getContrasena() };
            return res;
        }
    }
    return res;
}

vector<string> Tienda::siGerente() const {
    vector<string> res;
    cout << "\nIngrese usuario y contraseña:\n";
    string u, p;
    cout << "Usuario: "; getline(cin, u);
    cout << "Contraseña: "; getline(cin, p);
    for (const auto &g : gerentes) {
        if (g.getUsuario() == u && g.getContrasena() == p) {
            res = { to_string(g.getId()), g.getUsuario(), g.getContrasena() };
            return res;
        }
    }
    return res;
}

vector<string> Tienda::siEmpleado() const {
    vector<string> res;
    cout << "\nIngrese usuario y contraseña:\n";
    string u, p;
    cout << "Usuario: "; getline(cin, u);
    cout << "Contraseña: "; getline(cin, p);
    for (const auto &e : empleados) {
        if (e.getUsuario() == u && e.getContrasena() == p) {
            res = { to_string(e.getId()), e.getUsuario(), e.getContrasena() };
            return res;
        }
    }
    return res;
}

void Tienda::administradorNo() {
    cout << "\nCree un usuario y contraseña para administrador:\n";
    string u = readLine("Usuario: ");
    string p = readLine("Contraseña: ");
    Administrador a(nextUsuarioId++, u, p);
    administradores.push_back(a);
    cout << "Administrador creado.\n";
}

/* ---------- run / menus ---------- */
void Tienda::run() {
    crearTablas();
    if (administradores.empty()) {
        administradorNo();
    }

    while (true) {
        cout << "\nSeleccione su tipo de usuario:\n1. Administrador\n2. Gerente\n3. Empleado\n4. Salir\n";
        string tipo = readLine("Opción: ");
        if (tipo == "4") break;

        if (tipo == "1") {
            auto usuario = siAdministrador();
            if (!usuario.empty()) {
                string nombre_usuario = usuario.size() > 1 ? usuario[1] : "";
                string rango = "Administrador";
                while (true) {
                    cout << "\n--- MENU ADMINISTRADOR ---\n";
                    cout << "1. Agregar producto\n2. Buscar producto por codigo\n3. Modificar producto\n4. Eliminar producto\n5. Vender producto\n6. Mostrar productos\n7. Mostrar todos los usuarios (gerentes y empleados)\n8. Reporte de ventas\n9. Agregar gerentes o empleados\n10. Modificar gerentes o empleados\n11. Eliminar empleados o gerentes\n12. Salir\n";
                    string opt = readLine("Opción: ");
                    if (opt == "1") agregarProducto();
                    else if (opt == "2") buscarProductoPorCodigo();
                    else if (opt == "3") modificarProducto();
                    else if (opt == "4") eliminarProducto();
                    else if (opt == "5") venderProducto(nombre_usuario, rango);
                    else if (opt == "6") mostrarProductos();
                    else if (opt == "7") mostrarUsuariosCombinados();
                    else if (opt == "8") mostrarReporteVentas();
                    else if (opt == "9") {
                        string a = readLine("1. Gerente\n2. Empleado\n¿De que cargo desea agregar? ");
                        if (a == "1") agregarGerente();
                        else if (a == "2") agregarEmpleado();
                    }
                    else if (opt == "10") {
                        string a = readLine("1. Gerente\n2. Empleado\n¿De que cargo desea modificar? ");
                        if (a == "1") modificarGerente();
                        else if (a == "2") modificarEmpleado();
                    }
                    else if (opt == "11") {
                        string a = readLine("1. Gerente\n2. Empleado\n¿De que cargo desea eliminar? ");
                        if (a == "1") eliminarGerente();
                        else if (a == "2") eliminarEmpleado();
                    }
                    else if (opt == "12") break;
                    else cout << "Opción no válida\n";
                }
            } else {
                cout << "Usuario o contraseña incorrectos.\n";
            }
        }
        else if (tipo == "2") {
            auto g = siGerente();
            if (!g.empty()) {
                string nombre_usuario = g.size() > 1 ? g[1] : "";
                string rango = "Gerente";
                while (true) {
                    cout << "\n--- MENU GERENTE ---\n";
                    cout << "1. Agregar producto\n2. Buscar producto por codigo\n3. Modificar producto\n4. Eliminar producto\n5. Vender producto\n6. Mostrar productos\n7. Mostrar todos los empleados\n8. Reporte de ventas\n9. Agregar empleados\n10. Modificar empleados\n11. Eliminar empleados\n12. Salir\n";
                    string opt = readLine("Opción: ");
                    if (opt == "1") agregarProducto();
                    else if (opt == "2") buscarProductoPorCodigo();
                    else if (opt == "3") modificarProducto();
                    else if (opt == "4") eliminarProducto();
                    else if (opt == "5") venderProducto(nombre_usuario, rango);
                    else if (opt == "6") mostrarProductos();
                    else if (opt == "7") mostrarUsuarios();
                    else if (opt == "8") mostrarReporteVentas();
                    else if (opt == "9") agregarEmpleado();
                    else if (opt == "10") modificarEmpleado();
                    else if (opt == "11") eliminarEmpleado();
                    else if (opt == "12") break;
                    else cout << "Opcion no valida\n";
                }
            } else cout << "Usuario o contraseña incorrectos.\n";
        }
        else if (tipo == "3") {
            auto e = siEmpleado();
            if (!e.empty()) {
                string nombre_usuario = e.size() > 1 ? e[1] : "";
                string rango = "Empleado";
                while (true) {
                    cout << "\n--- MENU EMPLEADO ---\n";
                    cout << "1. Buscar producto por código\n2. Vender producto\n3. Mostrar productos\n4. Salir\n";
                    string opt = readLine("Opción: ");
                    if (opt == "1") buscarProductoPorCodigo();
                    else if (opt == "2") venderProducto(nombre_usuario, rango);
                    else if (opt == "3") mostrarProductos();
                    else if (opt == "4") break;
                    else cout << "Opción no válida\n";
                }
            } else cout << "Usuario o contraseña incorrectos.\n";
        }
        else cout << "Opcion no valida.\n";
    }

    cout << "Programa finalizado.\n";
}
