#ifndef ORDENACION_H_INCLUDED
#define ORDENACION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

void imprimirTablero(int tablero[10][15],int turno);                                        //Funcion que imprime el tablero por pantalla
int numAleatorio();                                                                         //Funcion que decide si comienza el jugador o IA
int comprobarGanador(int gameMatrix[10][15], int gameTurn);                                 //Funcion que comprueba si existen 6 en raya
int valueCheck(int gameMatrix[10][15], int stackArray[15],int turn);                        //Funcion que devuelve el valor máyor en función de IA o humano
int maxValue(int gameMatrix[10][15], int pl, int posH, int posV);                           //Funcion que devuelve el valor de cada columna
void cargarDeFichero(FILE *f,int tablero[10][15],int ocupados[10],int *turno,int *empieza); //Funcion que extrae datos de partida_g.dat para cargar la partida
void guardarPartida(int tablero[10][15],int ocupados[10],int empieza);                      //Funcion que crea el fichero partida_g.dat y guarda los datos en él

#endif // ORDENACION_H_INCLUDED
