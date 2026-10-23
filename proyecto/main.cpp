#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip> 
#include "Equipo.h"

using namespace std;

bool cargarEquipos(const string& nombreArchivo, vector<Equipo>& lista) {//O(N)
    ifstream archivo(nombreArchivo); //1
    if (!archivo.is_open()) return false; //1

    string linea;
    while (getline(archivo, linea)) {//N
        stringstream ss(linea);//N
        string nombreEquipo, reaccion, danoStr, p1, p2, p3, p4;

        getline(ss, nombreEquipo, ','); //1
        getline(ss, reaccion, ',');//1
        getline(ss, danoStr, ',');//1
        getline(ss, p1, ','); getline(ss, p2, ','); getline(ss, p3, ','); getline(ss, p4, ',');//1

        if (!nombreEquipo.empty() && !danoStr.empty()) {//1
            Equipo eq = {nombreEquipo, reaccion, stoll(danoStr), {p1, p2, p3, p4}};//1
            lista.push_back(eq);//1
        }
    }
    archivo.close();//1
    return true;
}

bool cargarPersonajesInfo(const string& nombreArchivo, vector<PersonajeInfo>& lista) {//O/(N)
    ifstream archivo(nombreArchivo);//1
    if (!archivo.is_open()) {//1
        cerr << "El archivo no abre." << endl;
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {//N
        stringstream ss(linea);//1
        string nombre, estrellasStr;//1

        getline(ss, nombre, ',');//1
        getline(ss, estrellasStr, ',');//1

        if (!nombre.empty() && !estrellasStr.empty()) {//1
            PersonajeInfo p = {nombre, stoi(estrellasStr)};//1
            lista.push_back(p);//1
        }
    }
    archivo.close();//1
    return true;
}

void mostrarPersonajesClasificados(const vector<PersonajeInfo>& personajesInfo) {//O(N)
    vector<string> cincoEstrellas;//1
    vector<string> cuatroEstrellas;//1

    for (const auto& p : personajesInfo) {//N
        if (p.estrellas == 5) {//1
            cincoEstrellas.push_back(p.nombre);//1
        } else if (p.estrellas == 4) {//1
            cuatroEstrellas.push_back(p.nombre);//1
        }
    }

    cout << "\n--- Personajes 5Stars ---" << endl;
    for (size_t i = 0; i < cincoEstrellas.size(); i++) {//N(1)
        cout << " • " << left << setw(22) << cincoEstrellas[i];//1
        if ((i + 1) % 3 == 0) {
            cout << endl;//N(1)
        }
    }
    if (cincoEstrellas.size() % 3 != 0) cout << endl; //1

    cout << "\n--- Personajes 4Stars ---" << endl;
    for (size_t i = 0; i < cuatroEstrellas.size(); i++) {//N(1)
        cout << " • " << left << setw(22) << cuatroEstrellas[i];//1
        if ((i + 1) % 3 == 0) {
            cout << endl;
        }
    }
    if (cuatroEstrellas.size() % 3 != 0) cout << endl;//1
}

vector<Equipo> consultarPorPersonajes(const vector<Equipo>& lista, const vector<string>& personajesBuscados) {//O(N)
    vector<Equipo> resultados;//1
    for (const auto& eq : lista) {//N
        bool todosEncontrados = true;//1
        for (const auto& buscado : personajesBuscados) {//N
            bool encontradoActual = false;//1
            for (int i = 0; i < 4; i++) {//1
                if (eq.miembros[i] == buscado) {//N
                    encontradoActual = true;
                    break;
                }
            }
            if (!encontradoActual) {//1
                todosEncontrados = false;
                break;
            }
        }
        if (todosEncontrados) resultados.push_back(eq);
    }
    return resultados;
}
//implemente sort aqui
void ordenarPorDanoInsercion(vector<Equipo>& lista) { //O(n^2)
    int n = lista.size(); //1
    for (int i = 1; i < n; i++) { //n
        Equipo key = lista[i]; //n
        int j = i - 1;              //n
        while (j >= 0 && lista[j].danoTotal < key.danoTotal) { //n^2
            lista[j + 1] = lista[j];                   //n^2
            j = j - 1;                                 //n^2
        }
        lista[j + 1] = key;            //n
    }
}

int main() {
    #if defined(_WIN32) || defined(_WIN64)
        system("chcp 65001 > nul");
    #endif

    vector<Equipo> catalogoEquipos;
    vector<PersonajeInfo> catalogoPersonajes;

    if (!cargarEquipos("equipos.csv", catalogoEquipos) || !cargarPersonajesInfo("personajes.csv", catalogoPersonajes)) {
        cout << "El archivo esta mal." << endl;
        return 1;
    }

    int opcion = 0;
    do {
        cout << "\n========================================" << endl;
        cout << "  Gestor de equipos  -  Genshin Impact   " << endl;
        cout << "========================================" << endl;
        cout << "1. Equipos con 1 personaje" << endl;
        cout << "2. Equipos con 2 personajes" << endl;
        cout << "3. Equipos con 3 personajes" << endl;
        cout << "4. Equipos con 4 personajes (Rotacióm)" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opción: ";
        
        if (!(cin >> opcion)) break;
        cin.ignore();

        if (opcion >= 1 && opcion <= 4) {
            mostrarPersonajesClasificados(catalogoPersonajes);
            cout << "--------------------------------------------------------------------\n" << endl;

            vector<string> personajesBuscados;
            for (int i = 0; i < opcion; i++) {
                string p;
                cout << "Ingrese el personaje " << (i + 1) << ": ";
                getline(cin, p);
                personajesBuscados.push_back(p);
            }

            vector<Equipo> resultados = consultarPorPersonajes(catalogoEquipos, personajesBuscados);

            cout << "\n--- Equipos posibles ---" << endl;
            if (resultados.empty()) {
                cout << "No hay equipos con esos personajes.\n";
            } else {
                ordenarPorDanoInsercion(resultados);
                for (const auto& eq : resultados) {
                    cout << " • Equipo: " << eq.nombreEquipo << " (" << eq.reaccion << ") | Daño por segundo aprox: " << eq.danoTotal<< endl;
                    cout << "   Rotación: " << eq.miembros[0] << ", " << eq.miembros[1] << ", " 
                         << eq.miembros[2] << ", " << eq.miembros[3] << "\n" << endl;
                }
            }
        } else if (opcion == 5) {
            mostrarPersonajesClasificados(catalogoPersonajes);
        } else if (opcion == 6) {
            cout << "Saliendo..." << endl;
        } else {
            cout << "Opción no válida.\n";
        }

    } while (opcion != 6);

    return 0;
}