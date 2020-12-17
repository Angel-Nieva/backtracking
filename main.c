#include<stdio.h>
#include<stdlib.h>

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

/**
 * @brief Verifica si una ciudad cumple con las condiciones de las sucursales, no repetir columnas,filas ni diagonales
 * @param ciudad Arreglo que representa la ciudad
 * @param Ncolmna Columna que esta siendo verificada
 * @param col Cantidad de columnas en el arreglo
 * @return int 1 si la ciudad cumple con las condiciones, 0 en caso contrario
 */
int verificarCiudad(int *ciudad, int Ncolumna, int col){
    int suma = Ncolumna + ciudad[Ncolumna];  // es la suma de las filas y columnas para verificar si tiene alguna diagonal
    int resta = ciudad[Ncolumna]- Ncolumna;  // lo mismo que el anterior pero con la resta
    for (size_t i = 0; i < col; i++)    // Mientras no se revisen todas las columnas, en si esto ira revisando si se encuentra otra red de forma horizontal o diagonal
    {        
        if( i != Ncolumna && ciudad[i]!= -1 && ciudad[Ncolumna]!= -1 ){
            if(ciudad[i] == ciudad[Ncolumna]){
                return 0;
            }
            else if (ciudad[i] + i == suma){
                return 0;
            }
            else if (ciudad[i] - i == resta){
                return 0;
            }                            
        }
    }
    return 1;
}

/**
 * @brief Cuenta la cantidad de sucursales en una ciudad
 * 
 * @param ciudad Arreglo que representa la ciudad
 * @param col Cantidad de columnas en el arreglo
 * @return int con la cantidad de sucursales
 */
int cantidadSucursales(int *ciudad,int col)
{
    int sucursales = 0;    
    for (size_t i = 0; i < col; i++)
    {
        if (ciudad[i] != -1)
            sucursales+=1;    
    }
    return sucursales;
}

/**
 * @brief Crea una copia de una ciudad
 * @param ciudad Arreglo que representa una ciudad
 * @param col Cantidad de columnas en el arreglo
 * @return Arreglo de enteros
 */ 
int * copiarCiudad(int *ciudad,int col)
{
    int *nuevaCiudad = (int *)malloc(col*sizeof(int)); 
    for (size_t i = 0; i < col; i++)
    {
        nuevaCiudad[i] = ciudad[i];
    }
    return nuevaCiudad;
}

/**
 * @brief Busca todas las ciudades que cumplan los requisitos de las sucursales por busqueda en profundidad, en el caso de que el camino recorrido no tenga mas 
 *        ciudades se regresa a un camino anterior
 * @param ciudad Arreglo de enteros
 * @param actual Columna que se esta revisando
 * @param col Cantidad de columnas en el arreglo
 * @param fil Cantidad de filas en el arreglo
 * @param solucion Arreglo por referencia de enteros
 */
void backtracking(int *ciudad,int actual,int col,int fil,int **solucion)
{
    if ( actual>=col )
        return; 

    if ( ciudad[actual]!=-1 )                       // Si la columna contaba con una sucursal inicialmente
        backtracking(ciudad,actual+1,col,fil,solucion);    
    else
    {
        for (size_t i = 0; i < fil; i++)                  // Para cada columna en el arreglo
        {
            ciudad[actual] = i;
            if ( verificarCiudad(ciudad,actual,col) )
            {
                if( cantidadSucursales(ciudad,col)>cantidadSucursales((*solucion),col))
                {
                        free((*solucion));
                        (*solucion) = copiarCiudad(ciudad,col);
                }
                backtracking(ciudad,actual+1,col,fil,solucion);        
            }                
        }
        ciudad[actual] = -1;
    }      
    return;
}

int main(int argc, char const *argv[])
{
    int columnas,filas;
    int *ciudad = openFile(argv[1],&columnas,&filas);
    int *solucion = copiarCiudad(ciudad,columnas);
    
 
    imprimirCiudad(ciudad,columnas);
    printf("\n");    
    //Muestra un arreglo con 0 y 1 para verificar si la sucursal es correcta o no en la ciudad
    printf("\t");
    for (size_t i = 0; i < columnas; i++)
    {
        printf("|  %d",verificarCiudad(ciudad,i,columnas));
    }

    printf("\n\n");
    backtracking(ciudad,0,columnas,filas,&solucion);   
    imprimirCiudad(solucion,columnas);
    //Muestra un arreglo con 0 y 1 para verificar si la sucursal es correcta o no en la ciudad solucion
    printf("\t");
    for (size_t i = 0; i < columnas; i++)
    {
        printf("|  %d",verificarCiudad(solucion,i,columnas));
    }
    

    free(solucion);
    free(ciudad);
    return 0;
}
