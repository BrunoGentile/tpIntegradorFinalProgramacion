#include <iostream>
#include "Juego.h"
#include "rlutil.h"

int main() {
    inicializarSemilla(); //Llama a una funci¢n que inicializa una semilla para un generador de n£meros aleatorio//
    std::string jugadorConMayorPuntajeNombre = "";// Declara una variable para almacenar el nombre del jugador con el puntaje m s alto, inicialmente vac¡a//
    int puntajeMayor = 0;// Declara una variable de tipo int para almacenar el puntaje m s alto, inicialmente 0.
    int opcion; // Declara una variable de tipo int para almacenar la opci¢n seleccionada por el usuario en el men£.
    bool continuar = true;// Declara una variable booleana que controla el ciclo del men£. Inicialmente es true para que el ciclo se ejecute.

    while (continuar) { // Inicia un ciclo while que continuar  ejecut ndose mientras continuar sea true//
        rlutil::cls();//  Llama a una funci¢n para limpiar la pantalla (rlutil es una biblioteca).
        std::cout << "Menu de opciones:" << std::endl;
        std::cout << "------------------------" << std::endl;
        std::cout << "1. Jugar un jugador" << std::endl;
        std::cout << "2. Mostrar puntuacion mas alta" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "------------------------" << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                rlutil::cls();
                jugarUnJugador(jugadorConMayorPuntajeNombre, puntajeMayor);//Llama a la funci¢n jugarUnJugador para jugar con un jugador, actualizando el nombre y puntaje mayor
                rlutil::anykey("Presione cualquier tecla para continuar...");//Presione cualquier tecla para continuar...");: Espera a que el usuario presione cualquier tecla para continuar.
                break;
            }
            case 2: {
                rlutil::cls();
                mostrarPuntuacionMasAlta(jugadorConMayorPuntajeNombre, puntajeMayor);//Llama a la funci¢n mostrarPuntuacionMasAlta para mostrar el nombre y puntaje del jugador con la mayor puntuaci¢n.
                rlutil::anykey("Presione cualquier tecla para continuar...");
                break;
            }
            case 0: {
                rlutil::cls();
                continuar = false; //continuar = false;: Establece continuar como false, para salir del ciclo while
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            }
            default: {
                std::cout << "Opcion no valida. Intente nuevamente" << std::endl;
                rlutil::anykey("Presione cualquier tecla para continuar...");
                break;
            }
        }
    }

    return 0;
}
