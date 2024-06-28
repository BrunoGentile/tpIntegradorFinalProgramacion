#pragma once
#include <string>

void inicializarSemilla();
void jugarUnJugador(std::string& jugadorConMayorPuntajeNombre, int& puntajeMayor);
void mostrarPuntuacionMasAlta(const std::string& jugadorConMayorPuntajeNombre, int puntajeMayor);
void cargarAleatorio(int v[], int tam, int limite);
void cargarManual(int v[], int tam);
void mostrarVector(int v[], int tam);
int calcularPuntaje(int dados[], int tam);
void imprimirDados(int dados[], int tam, int posx, int posy);
bool esEscalera(int dados[], int tam);
bool esSexteto(int dados[], int tam, int& valor);
std::string determinarCombinacion(int dados[], int tam);
void dibujarDado(int valor, int posx, int posy);
void menu();
