#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define GUS 20  //gustos maximos 20




typedef struct {int cod;            //entero de 3 cifras no correlativo y sin repetidos
                char gusto [26];
                char coccion;       //H – Horno, F – Fritas, S – Sin Cocción
                int cantVendida;    // >0
                float precio;       // >0
                float imptotal;
                }TEmpanadas;

///////////////////////////////FUNCIONES////////////////////////////////////////

int carga (TEmpanadas [], int);
int buscar (TEmpanadas [], int, int);
int IngrDatoVal (int, int, int);
int esDatoVal (int, int, int);
void MostrarCodigos (TEmpanadas [], int);
void ventaSemana (TEmpanadas [], float [][7], int);
void mostrarDias (TEmpanadas [], float [][7], int );
int maximo (TEmpanadas [], int);
void mostrarMax(TEmpanadas [], int, int);
void vendidasCoccion ( TEmpanadas [], int);





//////////////////////MAIN/////////////////////
int main ()
{
    TEmpanadas VEmpa [GUS];

    int cant, max;
    float MDias[20][7]={{0}};

    cant = carga (VEmpa, GUS);

    ventaSemana (VEmpa,MDias, cant);
    mostrarDias (VEmpa,MDias, cant);
    max = maximo (VEmpa, cant);
    mostrarMax (VEmpa, cant, max);
    vendidasCoccion(VEmpa, cant);


    return 0;
}





//////////////////////////////DESARROLLO FUNCIONES///////////////////////////////


int esDatoVal (int n, int li, int ls)
{
    if(n>=li && n<=ls)
        return 1;   //devuelve 1 si es valido
    else
        return 0;
}


//////////////////////////////////////////////////////////////////////////////////
int IngrDatoVal (int li, int ls, int fin)
{
    int num, error=0;
    do{
        if(error)   //error!=0
            printf("Codigo incorrecto, ingrese nuevamente:");
        scanf("%d", &num);

        if(num==fin)
            return num;

        error=1;
    }while(esDatoVal(num, li, ls)==0);  //tiene que devolver 1 para que sea valido

    return num;
}


////////////////////////////////////////////////////////////////////////////////////////////

int buscar (TEmpanadas v[], int dato, int ce)
{
    int i=0, pos=-1;

    while(pos == -1 && i<ce)
    {
        if (v[i].cod== dato)
            pos= i;         //si devuelde i, osea pos!= -1 es porque lo encontró
        else
            i++;             // si devuelve pos = -1 es porque no lo encontró
    }


    return pos;

}


/////////////////////////////////////////////////////////////////////////////////////////////

int carga (TEmpanadas vec[], int ce)
{
    TEmpanadas aux;
    int i=0, auxi,pos;

    printf("Ingrese el codigo de empanada(entero de 3 cifras o 0 para fin): ");
    aux.cod = IngrDatoVal (100, 999, 0);

    while(aux.cod !=0 && i<ce)
    {
        printf("Nombre gusto: ");
        fflush (stdin);
        fgets(aux.gusto, 26, stdin);
        aux.gusto[strlen(aux.gusto)-1]='\0';

        do
        {
             printf("Coccion deseada (H – Horno, F – Fritas, S – Sin Coccion): ");
        fflush (stdin);
        scanf("%c", &aux.coccion);
        aux.coccion= toupper(aux.coccion);

        }while(aux.coccion!='H' && aux.coccion !='F' && aux.coccion!= 'S');


        do
        {
            printf("Cantidad vendida: ");
            scanf("%d", &aux.cantVendida);
        }while(aux.cantVendida<0);

        do
        {
            printf("Precio: ");
            scanf("%f", &aux.precio);
        }while(aux.precio<=0);

        aux.imptotal = aux.precio * aux.cantVendida;




        vec[i]=aux;

        i++;
        do
        {   printf("\nIngrese el codigo de empanada(entero de 3 cifras o 0 para fin): ");
            auxi = IngrDatoVal (100, 999, 0);
            pos = buscar (vec, auxi, i);
            if (pos!= -1)
                printf("Codigo ya ingresado, intente nuevamente\n");
        }while (pos!= -1);
        aux.cod = auxi;
//fin

    }


    return i;
}


//////////////////////////////////////////////////////////////////////////////////////////////

void MostrarCodigos (TEmpanadas vec[], int ce)
{
    int i;

    for(i=0; i<ce; i++)
    {
        printf("\n\t%d", vec[i].cod);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////

void ventaSemana (TEmpanadas vec[], float m[][7], int ce )
{
    int i, cant, pos, dato, contVentas;
    printf ("\n\n\nIngreso de ventas semanales...\n");
    do
    {
        printf("\nIngrese codigo de empanada: ");
        MostrarCodigos(vec, ce);
        printf("\nCodigo: ");
        scanf("%d", &dato);
        if(dato==0)
            pos=1;
        else
            pos = buscar (vec, dato, ce);
    }while(pos== -1);




    while(dato!=0)
    {

        for(i=0; i<7; i++)
        {
           printf("\nCantidad de ventas dia %d: ", i+1);
           scanf("%d", &cant);

           m[pos][i]= cant*vec[pos].precio;
           printf("Total: %.3f", m [pos][i]);

           vec[pos].cantVendida += cant;
        }


        do
        {   printf("\nIngrese codigo de empanada: ");
            MostrarCodigos(vec, ce);
            printf("\nCodigo: ");
            scanf("%d", &dato);
             if(dato==0)
            pos=1;
        else
            pos = buscar (vec, dato, ce);
        }while(pos== -1);

    }

}


//////////////////////////////////////////////////////////////////////////////////////////////

void mostrarDias(TEmpanadas v[], float m[][7], int ce)
{
    int i, j;

    for(i=0; i<ce ;i++)
    {printf("\nCod: %d Nombre: %s\n", v[i].cod, v[i].gusto);
        for(j=0;j<7; j++)
            printf("\tPrecio dia %d: %.3f", j+1, m[i][j]);
    }



}


//////////////////////////////////////////////////////////////////////////////////////////////

int maximo (TEmpanadas v[], int ce)
{
    int i, max;

    for(i=0;i<ce;i++)
    {
        if(i==0 || v[i].cantVendida>max)
            max = v[i].cantVendida;
    }

    return max;
}


//////////////////////////////////////////////////////////////////////////////////////////////
void mostrarMax(TEmpanadas v[], int ce, int max)
{
    int i;
    printf("\n\nEl o los gustos con mayores ventas:\n");
    for(i=0;i<ce;i++)
    {
        if(v[i].cantVendida == max)
            printf("Gusto '%s' Tuvo %d ventas.\n", v[i].gusto, v[i].cantVendida);
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////

void vendidasCoccion (TEmpanadas v[], int ce)
{
    int i;
    int horno=0, frita=0, sin=0;

    for(i=0;i<ce;i++)
    {
        switch(v[i].coccion)
        {
        case 'H':
            horno+= v[i].cantVendida;
            break;

        case 'F':
            frita+= v[i].cantVendida;
            break;

        case 'S':
            sin+=v[i].cantVendida;
            break;
        }

    }

    printf("Las empanadas al Horno tuvieron %d ventas.\n", horno);
    printf("Las empanadas Fritas tuvieron %d ventas.\n", frita);
    printf("Las empanadas Sin Coccion tuvieron %d ventas.\n", sin);


}




