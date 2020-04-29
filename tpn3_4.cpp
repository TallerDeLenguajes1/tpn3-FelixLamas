#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAMANIO 100

char *TiposProductos[]={"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

typedef struct Producto {
int ProductoID; //Numerado en ciclo iterativo
int Cantidad; // entre 1 y 10
char *TipoProducto; // Algún valor del arreglo TiposProductos
float PrecioUnitario; // entre 10 - 100
} Producto;

typedef struct Cliente {
int ClienteID; // Numerado en el ciclo iterativo
char *NombreCliente; // Ingresado por usuario
int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
Producto *Productos;//El tamaño de este arreglo depende de la variable
// “CantidadProductosAPedir”
} Cliente;

void cargarcliente (Cliente **ppcliente, int cantidadClientes);
float costoProducto( Producto * pProducto);
void mostrarVenta (Cliente **ppCliente, int cantidadClientes);

int main(int argc, char const *argv[])
{
    int cantidadClientes;
    Cliente *pCliente;
    float costoTotal=0;
    
    printf("Ingrese la cantidad de clientes:");
    scanf("%d", &cantidadClientes);
    getchar();
    pCliente= (Cliente *) malloc(sizeof(Cliente)*cantidadClientes);
    cargarcliente( &pCliente, cantidadClientes);
    mostrarVenta(&pCliente, cantidadClientes);

    free(pCliente);
    return 0;
}

void cargarcliente(Cliente ** ppcliente, int cantidadClientes)
{
    srand (time(NULL));
    char nombre[TAMANIO];
    for (int i = 0; i < cantidadClientes ; i++)
    {
        (*ppcliente + i)->ClienteID=i+1;
        puts("Ingrese el nombre del cliente:");
        gets(nombre);
        (*ppcliente + i)->NombreCliente=(char *) malloc(sizeof(char)* strlen(nombre));
        strcpy((*ppcliente + i)->NombreCliente,nombre);
        srand (time(NULL));
        (*ppcliente + i)->CantidadProductosAPedir= rand()%5;
        printf("El cliente pidio la cantidad de: %d productos\n",(*ppcliente + i)->CantidadProductosAPedir);
        (*ppcliente + i)->Productos=(Producto *) malloc(sizeof(Producto)*(*ppcliente + i)->CantidadProductosAPedir);
        for (int j = 0; j < (*ppcliente + i)->CantidadProductosAPedir ; j++)
        {
            (((*ppcliente + i)->Productos) + j)->ProductoID= j+1;
            printf("El id del producto es :%d \n", (((*ppcliente + i)->Productos) + j)->ProductoID);
            (((*ppcliente + i)->Productos) + j)->Cantidad=1+ rand()%(11-1);
            printf("La cantidad de productos es :%d \n", (((*ppcliente + i)->Productos) + j)->Cantidad);
            ((*ppcliente + i)->Productos + j)->TipoProducto= (char *) malloc(sizeof(char)*(strlen(*(TiposProductos+rand()%5))));
            strcpy(((*ppcliente + i)->Productos + j)->TipoProducto,*(TiposProductos+rand()%5));
            puts("El tipo de producto es:");
            puts(((*ppcliente + i)->Productos + j)->TipoProducto);
            ((*ppcliente + i)->Productos + j)->PrecioUnitario=10 + rand()%(101-10);
            printf("El precio unitario es: %.2f\n", ((*ppcliente + i)->Productos + j)->PrecioUnitario);
            
        }
        
    }
    
}


float costoProducto( Producto * pProducto)
{
    return ((pProducto->Cantidad)*(pProducto->PrecioUnitario));
}

void mostrarVenta (Cliente **ppCliente,  int cantidadClientes)
{
    float costoP=0 , total;;
    for (int i = 0; i < cantidadClientes; i++)
    {
        printf("El ID del cliente es: %d\n",(*ppCliente + i)->ClienteID );
        printf("El nombre del cliente es:");
        puts((*ppCliente + i)->NombreCliente);
        printf("\nLa cantidad de productos pedidos por el cliente es:%d \n",(*ppCliente + i)->CantidadProductosAPedir );
        for (int j = 0; j < (*ppCliente + i)->CantidadProductosAPedir; j++)
        {
            printf("La cantidad de productos de ID n°%d es: %d\n", ((*ppCliente + i )->Productos +j)->ProductoID,((*ppCliente + i )->Productos +j)->Cantidad);
            printf("El tipo de producto es:");
            puts(((*ppCliente + i )->Productos +j)->TipoProducto);
            printf("El precio unitario del producto es: %.2f\n",((*ppCliente + i )->Productos +j)->PrecioUnitario);
            costoP = costoProducto(((*ppCliente+ i)->Productos)+j);
            printf("El costo total de la cantidad de productos del ID es: %.2f", costoP);
            total = total + costoP;
            costoP=0;
            getchar();
        }
        printf("El costo total de los productos para el cliente con ID n° %d es %.2f\n",(*ppCliente + i)->ClienteID, total);
        total=0;
        getchar();
    }
    
}