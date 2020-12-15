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
// Entradas: arreglo ciudad, entero equivalente a la columna deseada a buscar y un entero del numero maximo de columnas
// Salida: un entero llamado verificador, que si vale 1 no encontro fallas en la posicion buscada y si es un -1 ubo alguna que estuviera horizontal o diagonal a la buscada 
int verificarCiudad(int *ciudad, int Ncolumna, int columnas){
    int suma = Ncolumna + ciudad[Ncolumna]; // es la suma de las filas y columnas para verificar si tiene alguna diagonal
    int resta = ciudad[Ncolumna]- Ncolumna;// lo mismo que el anterior pero con la resta
    int contador = 0;
    int verificador = 1;//verificador para saber si esta bien colocada o no, si es un 1 esta bien, si es un -1 mal
    while(contador < columnas){//mientras el contador no pase por todas las columnas no se detendra, en si esto ira revisando si se encuentra otra red de forma horizontal o diagonal
        
        if(contador != Ncolumna){
            if(ciudad[contador]!= -1){
                if(ciudad[contador] == ciudad[Ncolumna]){
                    verificador = -1;
                    contador = columnas +1;
                }
                else if (ciudad[contador] + contador == suma){
                    verificador = -1;
                    contador = columnas +1;
                }
                else if (ciudad[contador] - contador == resta){
                    verificador = -1;
                    contador = columnas +1;
                }
                

            }
        }
         contador++;
    }
    return verificador;
}

int main(int argc, char const *argv[])
{
    //Hola mundo
    int columnas,filas;
    int *ciudad = openFile(argv[1],&columnas,&filas);
   // ciudad[4] = 7; esto solo esta porque anduve probando si funcionaba
    imprimirCiudad(ciudad,columnas);
    int verificador = verificarCiudad(ciudad,5,columnas);
   // printf("el verificador vale: %d \n",verificador);
    free(ciudad);




    return 0;
}
