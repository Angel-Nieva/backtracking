#include<stdio.h>
#include<stdlib.h>

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

void imprimirCiudad(int *ciudad,int col){
	printf("\t*");
	for (size_t i = 0; i < col; i++)
	{
		printf("---*");
	}
	printf("\n");
	printf("\t|");
	for (size_t i = 0; i < col; i++)
	{
        if(ciudad[i] > 10 || ciudad[i] < 0)
        {
            printf(" %d|", ciudad[i]);  
        }
		else
        {
            printf(" %d |", ciudad[i]);
        }       
	}
	printf("\n");
	printf("\t*");
	for (size_t i = 0; i < col; i++)
	{
		printf("---*");
	}
	printf("\n");
    return;
}

int main(int argc, char const *argv[])
{
    //Hola mundo
    int columnas,filas;
    int *ciudad = openFile(argv[1],&columnas,&filas);
    imprimirCiudad(ciudad,columnas);

    free(ciudad);
    return 0;
}
