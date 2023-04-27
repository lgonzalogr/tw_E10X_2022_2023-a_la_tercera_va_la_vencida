#include<stdio.h>
#include<stdlib.h>
void menuprincipal(void);
int main(){
    int eleccion;
    while(eleccion!=4){
        menuprincipal();
        scanf("%i",&eleccion);


    }
    return 0;
}

void menuprincipal(void){
    printf("\t\t\tMENU PRINCIPAL\n\n");
    printf("Introduzca el numero indicado para acceder a la opción:\n\n");
    printf("\t1.\tVer datos completos.\n");
    printf("\t2.\tBusqueda de datos.\n");
    printf("\t3.\tAñadir datos.\n");
    printf("\t4.\tCerrar el programa.\n");
}
