#include <stdio.h>
#include <stdlib.h>
#include "../incl/array.h"
#include "../incl/ciudad.h"

/**
 * @brief Abre el archivo de entrada y crea un arreglo de enteros que representa una ciudad
 * @param filename Nomrbre archivo de entrada
 * @param col Cantidad de columnas del arreglo
 * @param fil Cantidad de filas en el arreglo
 * @return Arreglo de enteros
 */
int * openFile(const char * filename,int *col,int *fil)
{
    FILE * f;
    f = fopen (filename, "r");
    if(f == NULL){
        fputs ("File error",stderr); 
		exit (1);
    }
    // Si el archivo no es NULL
    
    fscanf(f,"%d %d ",&(*col),&(*fil));     // Se guardan las columnas y filas
    int * ciudad = (int *)malloc((*col)*sizeof(int)); // Arreglo que representa una ciudad
    for (size_t i = 0; i < (*col); i++) 
    {
        ciudad[i] = -1;    // Se representa con un -1 cuando la ciudad no tiene sucursal
    }
    
    int sucursales;
    fscanf(f,"%d ",&sucursales);    // Se guardan la cantidad de sucursales iniciales
    for (size_t i = 0; i < sucursales; i++)
    {
        int columna,fila;
        fscanf(f,"%d %d ",&columna,&fila);
        ciudad[columna] = fila;         // Se colocan las sucursales en el arreglo 
    }

    fclose(f);
	return ciudad;    
}

/**
 * @brief Escribe un archivo con la solucion del problema
 * 
 * @param ciudad Arreglo que representa la ciudad solucion
 * @param filename i.e salida.out
 */
void writeFile(int *ciudad,int col,const char*filename,int fil)
{
    char *buffer = ciudadToString(ciudad,col,fil);
    FILE *fp;
    fp = fopen(filename, "w+");
    fputs(buffer,fp);
    fclose(fp);
    free(buffer);
}

/**
 * @brief Transforma la ciudad en un string posible de visualizar y guardar en un archivo de texto
 * @param ciudad Arreglo de enteros
 * @param col Cantidad de columnas en el arreglo
 * @return char *String
 */
char * ciudadToString(int *ciudad,int col,int fil)
{
    char *buffer = malloc(sizeof(char)*1000);
    int a = 0;
    a += snprintf(buffer+a,1000-a,"Cantidad de sucursales en la ciudad: %d\n",cantidadSucursales(ciudad,col));
    //strcat(buffer,"La ciudad cuenta con %d sucursales.\n|");
    a += snprintf(buffer+a,1000-a,"Lista cordenadas sucursales (x,y):\n|");
    for (size_t i = 0; i < col; i++)
	{
        if ( ciudad[i] != -1 )
        {
            a += snprintf(buffer+a,1000-a," (%d,%d) |",ciudad[i],i);  //snprintf transforma a string
        }        
            
	}
    a += snprintf(buffer+a,1000-a,"\n");

    for (size_t n = 0; n < fil; n++)
    {
        for (size_t i = 0; i < col; i++)
        {
            if ( ciudad[i] != -1 && ciudad[i] == n )
            {
                a += snprintf(buffer+a,1000-a,"x ",ciudad[i],i);  //snprintf transforma a string
            }
            else
            {
               a += snprintf(buffer+a,1000-a,"_ ");  //snprintf transforma a string 
            }       
                
        }
        a += snprintf(buffer+a,1000-a,"\n");
    }
    return buffer;
}