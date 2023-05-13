#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct fila{
    char filascompletas[432];
    char numero[100];
};
void menuprincipal(void);
void mostrardatoscompletos(struct fila *, FILE *, int);
void menubusqueda(void);
void menubusquedafecha(struct fila *,FILE *);
void cadenasindependientes(FILE *, int ,int ,char [][25]);
int main(){
    int eleccion,eleccionbusqueda;
    int i=0,j,n=0,ncomas=0;
    char c,comas;
    char datos[50][560];
    struct fila *nfilas; //Declaracion del puntero para reserva de memoria mas adelante
    FILE *archivocompleto; //Declaracion del archivo principal

    while(eleccion!=6){
        menuprincipal();
            scanf("%i",&eleccion);
            archivocompleto=fopen("generacion.csv","r");
                    while(!feof(archivocompleto)){ //Se cuenta el numero de filas
                        c=fgetc(archivocompleto);
                        if (c=='\n') n++;
                        }
                    rewind(archivocompleto);
                    while(!feof(archivocompleto)){ //Se cuenta el numero de filas
                        comas=fgetc(archivocompleto);
                        if (comas==',') ncomas++;
                        }
                    printf("El numero de filas es: %i\n",n);// comprobacion
                    printf("El numero de comas es: %i\n",ncomas);
                    printf("El numero de columnas es: %i\n",ncomas/23+1);
                    nfilas=(struct fila*)malloc(n*sizeof(struct fila));
                    fclose(archivocompleto);
            switch(eleccion){
                case 1:
                printf("\n\n\t1.\tVer datos completos.\n"); // comprobacion
                archivocompleto=fopen("generacion.csv","r");
                    nfilas=(struct fila*)malloc(n*sizeof(struct fila)); //Se asigan dimension n=23 al vector de estructuras nfilas
                    mostrardatoscompletos(nfilas,archivocompleto,n);
                fclose(archivocompleto);

                break;
                case 2:
                while(eleccionbusqueda!=4){
                    printf("Seleccione el tipo de busqueda que desea:\n");
                    menubusqueda();
                    scanf("%i",&eleccionbusqueda);
                    switch(eleccionbusqueda){
                        case 1:
                            menubusquedafecha(nfilas,archivocompleto);
                            cadenasindependientes(archivocompleto,n,ncomas/23+1,datos);
                    }


                    }
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

    for(i=-2;i<n;i++){

	fgets(nfilas[i].filascompletas,sizeof(nfilas[i].filascompletas),archivocompleto);

		nfilas[i].filascompletas[strlen(nfilas[i].filascompletas)]='\0';

	nfilas[i].filascompletas[strlen(nfilas[i].filascompletas)-1]=';';


}
    rewind(archivocompleto);
    for(i=-2;i<n;i++){
        fgets(nfilas[i].filascompletas,sizeof(nfilas[i].filascompletas),archivocompleto);

		nfilas[i].filascompletas[strlen(nfilas[i].filascompletas)]='"';

	nfilas[i].filascompletas[strlen(nfilas[i].filascompletas)-1]='\n';
    }


for(i=0;i<n;i++){

	printf ("%s\n",nfilas[i].filascompletas);

}
}
void menubusqueda(void){
    printf("\t1.\tFecha.");
    printf("\t2.\tEnergia.");
    printf("\t3.\tFecha y energia.");
    printf("\t4.\tVolver al menu.");
}
void menubusquedafecha(struct fila *filafechas,FILE *fechas){
    fechas=fopen("generacion.csv","r");
    int i;
    for(i=0;i<=4;i++){
        fgets(filafechas[i].filascompletas,sizeof(filafechas[i].filascompletas),fechas);
    }
    for(i=4;i<=4;i++){

	printf ("%s\n",filafechas[i].filascompletas);
    fclose(fechas);
}
}
//void busquedafecha()

void cadenasindependientes(FILE *archivo, int filas,int columnas,char datosindependientes[][25]){
    int i,j;
    archivo=fopen("generacion.csv","r");
    for(i=0;i<filas;i++){
        for(j=0;j<columnas;j++){
            fgets(datosindependientes[i][j],sizeof(datosindependientes),archivo);
        }
    }
    fclose(archivo);
}
