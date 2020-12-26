#include<stdio.h>
#include<stdlib.h>
#include "../incl/ciudad.h"
#include "../incl/array.h"
#include "../incl/backtracking.h"

int main(int argc, char const *argv[])
{
    int columnas,filas;
    int *ciudad = openFile(argv[1],&columnas,&filas);
    int *solucion = copiarCiudad(ciudad,columnas);

    if ( verificarCiudadInicial(ciudad,columnas) )
    {
    backtracking(ciudad,0,columnas,filas,&solucion);
    writeFile(solucion,columnas,argv[2],filas);

    free(solucion);
    free(ciudad);
    }
    else
    {
        printf("Error de archivo de entrada\n");
    }
    return 0;
}