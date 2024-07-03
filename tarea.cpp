#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void imprimirConResaltado(const string &linea, const string &palabra) {
    size_t longitudLinea = linea.length();
    size_t longitudPalabra = palabra.length();
    size_t i = 0;

    while (i < longitudLinea) {
        // Verificar si la palabra coincide en esta posición
        bool coincidencia = true;
        if (i + longitudPalabra <= longitudLinea) {
            for (size_t j = 0; j < longitudPalabra; ++j) {
                if (linea[i + j] != palabra[j]) {
                    coincidencia = false;
                    break;
                }
            }
        } else {
            coincidencia = false;
        }

        // Imprimir la coincidencia en color o el carácter normal
        if (coincidencia) {
            cout << "\033[1;31m" << palabra << "\033[0m";
            i += longitudPalabra;  // Saltar la longitud de la palabra
        } else {
            cout << linea[i];
            i++;
        }
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <nombre_del_archivo> <palabra>" << endl;
        return 1;
    }

    ifstream archivo(argv[1]);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << argv[1] << endl;
        return 1;
    }

    string palabra = argv[2];
    string linea;
    int numLineasConCoincidencias = 0;
    int numCoincidencias = 0;
    int numLinea = 0;

    while (getline(archivo, linea)) {
        numLinea++;
        bool lineaTieneCoincidencia = false;
        size_t longitudLinea = linea.length();
        size_t longitudPalabra = palabra.length();
        
        // Recorremos la línea buscando todas las coincidencias
        for (size_t i = 0; i <= longitudLinea - longitudPalabra; ++i) {
            bool coincidencia = true;
            for (size_t j = 0; j < longitudPalabra; ++j) {
                if (linea[i + j] != palabra[j]) {
                    coincidencia = false;
                    break;
                }
            }
            if (coincidencia) {
                numCoincidencias++;
                lineaTieneCoincidencia = true;
            }
        }

        // Imprimir la línea con resaltado si tiene coincidencias
        if (lineaTieneCoincidencia) {
            numLineasConCoincidencias++;
            cout << "Línea " << numLinea << ": ";
            imprimirConResaltado(linea, palabra);
        }
    }

    archivo.close();

    cout << "Número de líneas con coincidencias: " << numLineasConCoincidencias << endl;
    cout << "Número total de coincidencias: " << numCoincidencias << endl;

    return 0;
}

