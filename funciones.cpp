#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "rlutil.h"

void inicializarSemilla() {
    std::srand(std::time(NULL));  // Inicializar la semilla para generaci¢n de n£meros aleatorios
}

void jugarUnJugador(std::string & jugadorConMayorPuntajeNombre, int & puntajeMayor) {
    std::string nombre;
    int puntaje = 0;

    std::cout << "Ingrese su nombre: ";
    std::cin >> nombre;

    bool modoSimulado = false;
    char opcionModo;
    std::cout << "\n" << (char) 168 << "Desea jugar en modo simulado? (s/n): ";
    std::cin >> opcionModo;
    if (opcionModo == 'n' || opcionModo == 'N') {
        modoSimulado = true; //Si ponemos N se cambia a true
    }

    for (int ronda = 1; ronda <= 3; ++ronda) {
        int puntajeMaximoRonda = 0;
        std::cout << "\nTURNO DE: " << nombre << " | RONDA N" << (char) 167 << " " << ronda << " | PUNTAJE TOTAL: " << puntaje << std::endl;
        std::cout << "------------------------------------------------------------------\n";

        for (int lanzamiento = 1; lanzamiento <= 3; ++lanzamiento) {
            std::cout << "Presione dos veces la tecla ENTER para realizar el lanzamiento N" << (char) 167 << " " << lanzamiento << ".";
            std::cin.ignore();
            std::cin.get();
            system("cls");

            int dados[6];
            if (modoSimulado) {
                cargarAleatorio(dados, 6, 6);
            } else {
                cargarManual(dados, 6); //Si ponemos S seria false.
            }

            int puntajeLanzamiento = calcularPuntaje(dados, 6);
            std::string combinacion = determinarCombinacion(dados, 6);
            puntajeMaximoRonda = std::max(puntajeMaximoRonda, puntajeLanzamiento);

            rlutil::locate(1, 1);
            for (int i = 0; i < 7; ++i) { //Limpiar una secci¢n de la consola. Al mover el cursor a la posici¢n (1, 1) y luego imprimir 7 l¡neas de espacios en blanco
                std::cout << "                                                      " << std::endl;
            }

            imprimirDados(dados, 6, 5, 2); // Dibujar los dados en la parte superior
            rlutil::locate(1, 9);

            std::cout << "\nTURNO DE: " << nombre << " | RONDA N" << (char) 167 << " " << ronda << " | PUNTAJE TOTAL: " << puntaje << std::endl;
            std::cout << "MAXIMO PUNTAJE DE LA RONDA: " << puntajeMaximoRonda << std::endl;
            std::cout << "LANZAMIENTO N" << (char) 167 << " " << lanzamiento << std::endl;
            std::cout << "------------------------------------------------------------------\n";

            std::cout << combinacion << std::endl;
            std::cout << "Puntaje de este lanzamiento: " << puntajeLanzamiento << std::endl;

            if (puntajeLanzamiento == 100) {  // Si se obtiene una escalera
                puntaje = 100;
                std::cout << "\n" << (char) 173 << "Felicidades, " << nombre << "! Has obtenido una escalera y ganado la partida." << std::endl;
                if (puntaje > puntajeMayor) {
                    jugadorConMayorPuntajeNombre = nombre;
                    puntajeMayor = puntaje;
                }
                return;  // Terminar el juego y volver al men£ principal
            } else if (puntajeLanzamiento == 0) { // Si se obtiene un sexteto de 6
                std::cout << "\n" << (char) 173 << "Oh no, " << nombre << "! Has obtenido un sexteto de 6 y tu puntaje acumulado se reduce a 0." << std::endl;
                puntaje = 0;
                puntajeMaximoRonda = 0; // Reiniciar el puntaje m ximo de la ronda
                break;  // Terminar la ronda actual
            }
        }

        puntaje += puntajeMaximoRonda; // Sumar el puntaje m ximo de la ronda al puntaje total
        std::cout << "\nPuntaje total despues de la ronda " << ronda << ": " << puntaje << std::endl;

        if (puntaje >= 100) {
            std::cout << "\n­Felicidades, " << nombre << "! Has alcanzado o superado los 100 puntos." << std::endl;
            break;
        }
    }

    if (puntaje > puntajeMayor) {
        jugadorConMayorPuntajeNombre = nombre;
        puntajeMayor = puntaje;
    }
}
//termina un Jugador

void mostrarPuntuacionMasAlta(const std::string& jugadorConMayorPuntajeNombre, int puntajeMayor) {
    if (jugadorConMayorPuntajeNombre.empty()) {
        //empty,verifica si la cadena esta vacia o no.
        std::cout << "\nNo hay puntuaciones registradas aun." << std::endl;
    } else {
        std::cout << "\nLa puntuacion mas alta es de " << jugadorConMayorPuntajeNombre << " con " << puntajeMayor << " puntos." << std::endl;
    }
}

void cargarAleatorio(int v[], int tam, int limite) {
    int i;
    srand(time(NULL));
    for (int i = 0; i < tam; ++i) {
        v[i] = (rand() % limite) + 1;//genera numero aleatorio y asignarlo en la posicion i del array v
    }
}

void cargarManual(int v[], int tam) {
    std::cout << "\nIngrese los valores de los dados (entre 1 y 6):\n";
    for (int i = 0; i < tam; ++i) { //recorre cada posicion del vector.
        std::cout << "Dado " << (i + 1) << ": ";
        std::cin >> v[i];
        // Validar que el valor ingresado est‚ en el rango v lido (1-6)
        while (v[i] < 1 || v[i] > 6) {
            std::cout << "Valor invalido. Ingrese un valor entre 1 y 6 para el dado " << (i + 1) << ": ";
            std::cin >> v[i];//ingresar nuevo numero
        }
    }
}

void mostrarVector(int v[], int tam) {
    int i;
    for (int i = 0; i < tam; ++i) {
        std::cout << v[i] << "\t";
    }
    std::cout << std::endl;
}

int calcularPuntaje(int dados[], int tam) {
    int valor;
    if (esEscalera(dados, tam)) {
        return 100;  // Puntaje alto para indicar escalera
    } else if (esSexteto(dados, tam, valor)) {
        if (valor == 6) {
            return 0;  // Reiniciar puntaje si hay sexteto de 6
        } else {
            return valor * 10;  // Puntaje por sexteto de otro valor
        }
    } else {
        int suma = 0;
        for (int i = 0; i < tam; ++i) {
            suma += dados[i];
        }
        return suma;
    }
}

void imprimirDados(int dados[], int tam, int posx, int posy) {
    for (int i = 0; i < tam; ++i) { // recorre todos los elementos del array
        dibujarDado(dados[i], posx + i * 10, posy);
    }
}

bool esEscalera(int dados[], int tam) {
    int cuenta[6] = {0};
    for (int i = 0; i < tam; ++i) {
        if (dados[i] >= 1 && dados[i] <= 6) {
            cuenta[dados[i] - 1]++;
        }
    }
    bool escalera = true;
    for (int i = 0; i < 6; ++i) {
        if (cuenta[i] != 1) {
            escalera = false;
            break;
        }
    }
    return escalera;
}

bool esSexteto(int dados[], int tam, int& valor) {
    int cuenta[7] = {0};
    for (int i = 0; i < tam; ++i) {
        if (dados[i] >= 1 && dados[i] <= 6) {
            cuenta[dados[i]]++;
        }
    }
    for (int i = 1; i <= 6; ++i) {
        if (cuenta[i] == 6) {
            valor = i;
            return true;
        }
    }
    return false;
}

std::string determinarCombinacion(int dados[], int tam) {
    int valor;
    if (esEscalera(dados, tam)) {
        return "Escalera";
    } else if (esSexteto(dados, tam, valor)) {
        return "Sexteto de " + std::to_string(valor);
    } else {
        return "Suma de dados";
    }
}

void dibujarDado(int valor, int posx, int posy) {
    rlutil::locate(posx, posy);
    std::cout << "+-------+";  // Ancho 9 (incluyendo bordes)
    rlutil::locate(posx, posy + 1);
    std::cout << "|       |";
    rlutil::locate(posx, posy + 2);
    std::cout << "|       |";
    rlutil::locate(posx, posy + 3);
    std::cout << "|       |";
    rlutil::locate(posx, posy + 4);
    std::cout << "+-------+";

    // Coloca los puntos seg£n el valor del dado
    switch (valor) {
        case 1:
            rlutil::locate(posx + 4, posy + 2);
            std::cout << "*";
        break;
        case 2:
            rlutil::locate(posx + 2, posy + 1);
            std::cout << "*";
            rlutil::locate(posx + 6, posy + 3);
            std::cout << "*";
        break;
        case 3:
            rlutil::locate(posx + 2, posy + 1);
            std::cout << "*";
            rlutil::locate(posx + 4, posy + 2);
            std::cout << "*";
            rlutil::locate(posx + 6, posy + 3);
            std::cout << "*";
        break;
        case 4:
            rlutil::locate(posx + 2, posy + 1);
            std::cout << "*";
            rlutil::locate(posx + 6, posy + 1);
            std::cout << "*";
            rlutil::locate(posx + 2, posy + 3);
            std::cout << "*";
            rlutil::locate(posx + 6, posy + 3);
            std::cout << "*";
        break;
        case 5:
            rlutil::locate(posx + 2, posy + 1);
            std::cout << "*";
            rlutil::locate(posx + 6, posy + 1);
            std::cout << "*";
            rlutil::locate(posx + 4, posy + 2);
            std::cout << "*";
            rlutil::locate(posx + 2, posy + 3);
            std::cout << "*";
            rlutil::locate(posx + 6, posy + 3);
            std::cout << "*";
        break;
        case 6:
            rlutil::locate(posx + 2, posy + 1);
            std::cout << "*";
            rlutil::locate(posx + 6, posy + 1);
            std::cout << "*";
            rlutil::locate(posx + 2, posy + 2);
            std::cout << "*";
            rlutil::locate(posx + 6, posy + 2);
            std::cout << "*";
            rlutil::locate(posx + 2, posy + 3);
            std::cout << "*";
            rlutil::locate(posx + 6, posy + 3);
            std::cout << "*";
        break;
        default:
        break;
    }
}
