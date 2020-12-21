#ifndef CIUDAD_H
#define CIUDAD_H
#include "../incl/ciudad.h"

int verificarCiudad(int *ciudad, int Ncolumna, int col);
int verificarCiudadInicial(int *ciudad,int col);
int cantidadSucursales(int *ciudad,int col);
int * copiarCiudad(int *ciudad,int col);

#endif