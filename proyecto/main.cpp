#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <stdexcept>

using namespace std;

string limpiarEspacios(const string& str) {
    size_t inicio = str.find_first_not_of(" \t\r\n");
    if (inicio == string::npos) return "";
    size_t fin = str.find_last_not_of(" \t\r\n");
    return str.substr(inicio, fin - inicio + 1);
}

string aMinusculas(const string& str) {
    string resultado = str;
    for (size_t i = 0; i < resultado.length(); i++) {
        resultado[i] = static_cast<char>(tolower(static_cast<unsigned char>(resultado[i])));
    }
    return resultado;
}

bool esEnteroValido(const string& str) {
    string limpio = limpiarEspacios(str);
    if (limpio.empty()) return false;
    for (size_t i = 0; i < limpio.length(); i++) {
        if (!isdigit(static_cast<unsigned char>(limpio[i]))) return false;
    }
    return true;
}

bool contieneComa(const string& str) {
    return str.find(',') != string::npos;
}


template <class T>
class Sorts {
private:
    void mergeSort(vector<T>& arr, int derecha, int izquierda);
    void merge(vector<T>& arr, int derecha, int mid, int izquierda);
public:
    vector<T> ordenaMerge(const vector<T>& source);
};

template <class T>
void Sorts<T>::merge(vector<T>& arr, int derecha, int mid, int izquierda) {
    int n1 = mid - derecha + 1;
    int n2 = izquierda - mid;

    vector<T> d(n1), z(n2);

    for (int i = 0; i < n1; i++) d[i] = arr[derecha + i];
    for (int j = 0; j < n2; j++) z[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = derecha;

    while (i < n1 && j < n2) {
        if (d[i] >= z[j]) {
            arr[k] = d[i];
            i++;
        } else {
            arr[k] = z[j];
            j++;
        }
        k++;
    }

    while (i < n1) { arr[k] = d[i]; i++; k++; }
    while (j < n2) { arr[k] = z[j]; j++; k++; }
}

template <class T>
void Sorts<T>::mergeSort(vector<T>& arr, int derecha, int izquierda) {
    if (derecha >= izquierda) return;
    int mid = derecha + (izquierda - derecha) / 2;
    mergeSort(arr, derecha, mid);
    mergeSort(arr, mid + 1, izquierda);
    merge(arr, derecha, mid, izquierda);
}

template <class T>
vector<T> Sorts<T>::ordenaMerge(const vector<T>& source) {
    vector<T> arr(source);
    int n = static_cast<int>(arr.size());
    if (n > 0) {
        mergeSort(arr, 0, n - 1);
    }
    return arr;
}


struct Equipo {
    string nombreEquipo;
    string reaccion;
    long long danoTotal;
    string miembros[4];

    bool operator>=(const Equipo& otro) const {
        return danoTotal >= otro.danoTotal;
    }
};

struct PersonajeInfo {
    string nombre;
    int estrellas;
};

bool cargarEquipos(const string& nombreArchivo, vector<Equipo>& lista) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return false;

    string linea;
    while (getline(archivo, linea)) {
        if (limpiarEspacios(linea).empty()) continue;

        stringstream ss(linea);
        string nombreEquipo, reaccion, danoStr, p1, p2, p3, p4, extra;

        if (!getline(ss, nombreEquipo, ',') ||
            !getline(ss, reaccion, ',') ||
            !getline(ss, danoStr, ',') ||
            !getline(ss, p1, ',') ||
            !getline(ss, p2, ',') ||
            !getline(ss, p3, ',') ||
            !getline(ss, p4)) {
            continue;
        }

        if (getline(ss, extra, ',')) continue;

        nombreEquipo = limpiarEspacios(nombreEquipo);
        reaccion = limpiarEspacios(reaccion);
        danoStr = limpiarEspacios(danoStr);
        p1 = limpiarEspacios(p1);
        p2 = limpiarEspacios(p2);
        p3 = limpiarEspacios(p3);
        p4 = limpiarEspacios(p4);

        if (nombreEquipo.empty() || reaccion.empty() ||
            p1.empty() || p2.empty() || p3.empty() || p4.empty()) {
            continue;
        }

        if (!esEnteroValido(danoStr)) continue;

        try {
            long long dano = stoll(danoStr);
            if (dano < 0) continue;
            Equipo eq = {nombreEquipo, reaccion, dano, {p1, p2, p3, p4}};
            lista.push_back(eq);
        } catch (const invalid_argument&) {
            continue;
        } catch (const out_of_range&) {
            continue;
        }
    }
    archivo.close();
    return true;
}

bool cargarPersonajesInfo(const string& nombreArchivo, vector<PersonajeInfo>& lista) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return false;

    string linea;
    while (getline(archivo, linea)) {
        if (limpiarEspacios(linea).empty()) continue;

        stringstream ss(linea);
        string nombre, estrellasStr, extra;

        if (!getline(ss, nombre, ',') || !getline(ss, estrellasStr)) {
            continue;
        }
        if (getline(ss, extra, ',')) continue;

        nombre = limpiarEspacios(nombre);
        estrellasStr = limpiarEspacios(estrellasStr);

        if (nombre.empty() || !esEnteroValido(estrellasStr)) continue;

        try {
            int estrellas = stoi(estrellasStr);
            if (estrellas != 4 && estrellas != 5) continue;
            PersonajeInfo p = {nombre, estrellas};
            lista.push_back(p);
        } catch (const invalid_argument&) {
            continue;
        } catch (const out_of_range&) {
            continue;
        }
    }
    archivo.close();
    return true;
}

bool guardarNuevoEquipoArchivo(const string& nombreArchivo, const Equipo& eq) {
    ofstream archivo(nombreArchivo, ios::app);
    if (!archivo.is_open()) return false;

    archivo << eq.nombreEquipo << "," << eq.reaccion << "," << eq.danoTotal << ","
            << eq.miembros[0] << "," << eq.miembros[1] << ","
            << eq.miembros[2] << "," << eq.miembros[3] << "\n";

    bool exito = archivo.good();
    archivo.close();
    return exito;
}

bool exportarResultadosArchivo(const string& nombreArchivo, const vector<Equipo>& resultados) {
    ofstream archivo(nombreArchivo, ios::trunc);
    if (!archivo.is_open()) return false;

    archivo << "Equipo,Reaccion,DanoTotal,Miembro1,Miembro2,Miembro3,Miembro4\n";
    for (const auto& eq : resultados) {
        archivo << eq.nombreEquipo << "," << eq.reaccion << "," << eq.danoTotal << ","
                << eq.miembros[0] << "," << eq.miembros[1] << ","
                << eq.miembros[2] << "," << eq.miembros[3] << "\n";
    }

    bool exito = archivo.good();
    archivo.close();
    return exito;
}

void mostrarPersonajesClasificados(const vector<PersonajeInfo>& personajesInfo) {
    vector<string> cincoEstrellas, cuatroEstrellas;

    for (const auto& p : personajesInfo) {
        if (p.estrellas == 5) cincoEstrellas.push_back(p.nombre);
        else if (p.estrellas == 4) cuatroEstrellas.push_back(p.nombre);
    }

    cout << "\n====================================================================" << endl;
    cout << "                 CATÁLOGO DE PERSONAJES DISPONIBLES                 " << endl;
    cout << "====================================================================" << endl;

    cout << "\n--- Personajes 5 Estrellas ---" << endl;
    for (size_t i = 0; i < cincoEstrellas.size(); i++) {
        cout << " • " << left << setw(22) << cincoEstrellas[i];
        if ((i + 1) % 3 == 0) cout << endl;
    }
    if (cincoEstrellas.size() % 3 != 0) cout << endl;

    cout << "\n--- Personajes 4 Estrellas ---" << endl;
    for (size_t i = 0; i < cuatroEstrellas.size(); i++) {
        cout << " • " << left << setw(22) << cuatroEstrellas[i];
        if ((i + 1) % 3 == 0) cout << endl;
    }
    if (cuatroEstrellas.size() % 3 != 0) cout << endl;
    cout << "--------------------------------------------------------------------\n" << endl;
}

vector<Equipo> consultarPorPersonajes(const vector<Equipo>& lista, const vector<string>& personajesBuscados) {
    vector<Equipo> resultados;

    vector<string> buscadosNormalizados;
    for (const auto& p : personajesBuscados) {
        string limpio = aMinusculas(limpiarEspacios(p));
        if (!limpio.empty()) {
            buscadosNormalizados.push_back(limpio);
        }
    }

    if (buscadosNormalizados.empty()) return resultados;

    sort(buscadosNormalizados.begin(), buscadosNormalizados.end());
    buscadosNormalizados.erase(
        unique(buscadosNormalizados.begin(), buscadosNormalizados.end()),
        buscadosNormalizados.end()
    );

    for (const auto& eq : lista) {
        bool todosEncontrados = true;
        bool miembroUsado[4] = {false, false, false, false};

        for (const auto& buscadoLower : buscadosNormalizados) {
            bool encontradoActual = false;

            for (int i = 0; i < 4; i++) {
                if (!miembroUsado[i] && aMinusculas(eq.miembros[i]) == buscadoLower) {
                    miembroUsado[i] = true;
                    encontradoActual = true;
                    break;
                }
            }
            if (!encontradoActual) {
                todosEncontrados = false;
                break;
            }
        }
        if (todosEncontrados) resultados.push_back(eq);
    }
    return resultados;
}

string leerCampoSinComas(const string& etiqueta) {
    string entrada;
    while (true) {
        cout << etiqueta;
        getline(cin, entrada);
        entrada = limpiarEspacios(entrada);
        if (entrada.empty()) {
            cout << "No puede estar vacío.\n";
        } else if (contieneComa(entrada)) {
            cout << "No se puede poner comas.\n";
        } else {
            return entrada;
        }
    }
}

int main() {
    #if defined(_WIN32) || defined(_WIN64)
        system("chcp 65001 > nul");
    #endif

    vector<Equipo> catalogoEquipos;
    vector<PersonajeInfo> catalogoPersonajes;

    if (!cargarEquipos("equipos.csv", catalogoEquipos) || !cargarPersonajesInfo("personajes.csv", catalogoPersonajes)) {
        cout << "Error: No se pudieron abrir 'equipos.csv' o 'personajes.csv'." << endl;
        return 1;
    }

    int opcion = 0;
    do {cout << "Según cuantos personajes tengas pensado para el equipo selecciona una opción, asi te dira cuales otros necesitas poner para hacer un buen equipo." << endl;
        cout << "\n========================================" << endl;
        cout << "  Gestor de Equipos  -  Genshin Impact  " << endl;
        cout << "========================================" << endl;
        cout << "1. Consultar equipos con 1 personaje" << endl;
        cout << "2. Consultar equipos con 2 personajes" << endl;
        cout << "3. Consultar equipos con 3 personajes" << endl;
        cout << "4. Consultar equipos con 4 personajes (Rotación)" << endl;
        cout << "5. Ver catálogo de personajes" << endl;
        cout << "6. Registrar y guardar un nuevo equipo" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            cout << "Esa opcion no existe, ponga un numero del 1 al 7.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');

        if (opcion >= 1 && opcion <= 4) {
            mostrarPersonajesClasificados(catalogoPersonajes);

            vector<string> personajesBuscados;
            cout << ">>> Ingrese " << opcion << "Ingrese sus personajes:\n";
            for (int i = 0; i < opcion; i++) {
                while (true) {
                    string p;
                    cout << "Ingrese el personaje " << (i + 1) << ": ";
                    getline(cin, p);
                    p = limpiarEspacios(p);

                    if (p.empty()) {
                        cout << "El nombre no puede estar vacío.\n";
                        continue;
                    }

                    bool repetido = false;
                    for (const auto& previo : personajesBuscados) {
                        if (aMinusculas(previo) == aMinusculas(p)) {
                            repetido = true;
                            break;
                        }
                    }

                    if (repetido) {
                        cout << "Ya ingresaste a '" << p << "'. Ingresa un personaje distinto.\n";
                    } else {
                        personajesBuscados.push_back(p);
                        break;
                    }
                }
            }

            vector<Equipo> resultados = consultarPorPersonajes(catalogoEquipos, personajesBuscados);

            cout << "\n--- Resultados ---" << endl;
            if (resultados.empty()) {
                cout << "No hay equipos registrados con esa combinación exacta.\n";
            } else {
                Sorts<Equipo> motorOrdenamiento;
                resultados = motorOrdenamiento.ordenaMerge(resultados);

                for (const auto& eq : resultados) {
                    cout << " • Equipo: " << eq.nombreEquipo << " (" << eq.reaccion << ") | Daño total: " << eq.danoTotal << endl;
                    cout << "   Rotación: " << eq.miembros[0] << ", " << eq.miembros[1] << ", "
                         << eq.miembros[2] << ", " << eq.miembros[3] << "\n" << endl;
                }
            }
        } else if (opcion == 5) {
            mostrarPersonajesClasificados(catalogoPersonajes);
        } else if (opcion == 6) {
            Equipo nuevoEq;
            cout << "\n--- Registro de Nuevo Equipo ---" << endl;
            nuevoEq.nombreEquipo = leerCampoSinComas("Ingrese el nombre del equipo: ");
            nuevoEq.reaccion = leerCampoSinComas("Ingrese la reacción elemental principal: ");

            string danoInput;
            while (true) {
                cout << "Ingrese el daño total aproximado: ";
                getline(cin, danoInput);
                if (esEnteroValido(danoInput)) {
                    try {
                        nuevoEq.danoTotal = stoll(limpiarEspacios(danoInput));
                        break;
                    } catch (const out_of_range&) {
                        cout << "Número demasiado grande.\n";
                    }
                } else {
                    cout << "Ingrese solo numeros.\n";
                }
            }

            cout << "Ingrese los 4 miembros distintos del equipo:\n";
            for (int i = 0; i < 4; i++) {
                while (true) {
                    string miembro = leerCampoSinComas(" Miembro " + to_string(i + 1) + ": ");
                    bool duplicado = false;
                    for (int j = 0; j < i; j++) {
                        if (aMinusculas(nuevoEq.miembros[j]) == aMinusculas(miembro)) {
                            duplicado = true;
                            break;
                        }
                    }
                    if (duplicado) {
                        cout << "No se pueden repetir personajes.\n";
                    } else {
                        nuevoEq.miembros[i] = miembro;
                        break;
                    }
                }
            }

            if (guardarNuevoEquipoArchivo("equipos.csv", nuevoEq)) {
                catalogoEquipos.push_back(nuevoEq);
                cout << " Equipo guardado y agregado al catálogo.\n";
            } else {
                cout << "Error. No se registró el equipo.\n";
            }

        } else if (opcion == 7) {
            cout << "Saliendo del sistema..." << endl;
        } else {
            cout << "Opción no válida. Intente de nuevo.\n";
        }

    } while (opcion != 7);

    return 0;
}