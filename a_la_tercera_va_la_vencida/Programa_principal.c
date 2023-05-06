#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct fila{
    char filascompletas[432];
};
void menuprincipal(void);
void mostrardatoscompletos(struct fila *, FILE *, int);
int main(){
    int eleccion;
    int i,j,n=0;
    char c;
    struct fila *nfilas; //Declaracion del puntero para reserva de memoria mas adelante
    FILE *archivocompleto; //Declaracion del archivo principal

    while(eleccion!=6){
        menuprincipal();
        scanf("%i",&eleccion);
        switch(eleccion){
    case 1:
        printf("\n\n\t1.\tVer datos completos.\n");
        archivocompleto=fopen("generacion.csv","r");
        while(!feof(archivocompleto)){ //Se cuenta el numero de filas
        c=fgetc(archivocompleto);
        if (c=='\n') n++;
        }
        printf("El numero de filas es: %i\n",n);
        nfilas=(struct fila*)malloc(n*sizeof(struct fila)); //Se asigan dimension n=23 al vector de estructuras nfilas
        rewind(archivocompleto);
        mostrardatoscompletos(nfilas,archivocompleto,n);
        fclose(archivocompleto);
        //mostrardatoscompletos(nfilas,archivocompleto,n);
        break;
    case 2:
        printf("Seleccione el tipo de busqueda que desea:\n");
        break;
    case 3:
         printf("Seleccione los datos que desea añadir:\n");
        break;
    case 4:
        printf("Seleccione la operación estadistica que desea:\n");
        break;
    case 5:
        printf("Indique como desea ver el historial:\n");
        }


        }





    return 0;
}

void menuprincipal(void){
    printf("\t\t\tMENU PRINCIPAL\n\n");
    printf("Introduzca el numero indicado para acceder a la opción:\n\n");
    printf("\t1.\tVer datos completos.\n");
    printf("\t2.\tBusqueda de datos.\n");
    printf("\t3.\tAñadir datos.\n");
    printf("\t4.\tEstadísticas del archivo.\n");
    printf("\t5.\tHistorial.\n");
    printf("\t6.\tCerrar el programa.\n");
}
void mostrardatoscompletos(struct fila *nfilas, FILE *archivocompleto,int n){
    int i;

    for(i=0;i<n;i++){

	fgets(nfilas[i].filascompletas,sizeof(nfilas[i].filascompletas),archivocompleto);

	nfilas[i].filascompletas[strlen(nfilas[i].filascompletas)-1]=';';

	nfilas[i].filascompletas[strlen(nfilas[i].filascompletas)]='\0';

}


for(i=0;i<n;i++){

	printf ("%s\n",nfilas[i].filascompletas);

}
}
