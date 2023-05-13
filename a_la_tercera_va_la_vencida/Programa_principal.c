#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct fila{
    char filascompletas[432];
    char numero[100];
};
void menuprincipal(void);
void copiarArchivoModificado(const char* nombre_origen, const char* nombre_destino);
void mostrardatoscompletos(struct fila *, FILE *, int);
void menubusqueda(void);
void menubusquedafecha(struct fila *,FILE *);
//void cadenasindependientes(FILE *, int ,int ,char [][560]);
int main(){
    int eleccion,eleccionbusqueda;
    int i=0,j,n=0,ncomas=0;
    char c,comas;
    char datos[50][560];
    char nombre_archivo_origen[100] = "generacion.csv";
    char nombre_archivo_destino[100] = "copiabonita.txt";
    struct fila *nfilas; //Declaracion del puntero para reserva de memoria mas adelante
    FILE *archivocompleto, copiabonita; //Declaracion del archivo principal

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
                copiarArchivoModificado(nombre_archivo_origen, nombre_archivo_destino);
                mostrarDatosCompletos(nombre_archivo_destino);
                break;




                case 2:
                while(eleccionbusqueda!=4){
                    printf("Seleccione el tipo de busqueda que desea:\n");
                    menubusqueda();
                    scanf("%i",&eleccionbusqueda);
                    switch(eleccionbusqueda){
                        case 1:
                            menubusquedafecha(nfilas,archivocompleto);
                            //cadenasindependientes(archivocompleto,n,ncomas,datos);
                            //rewind(archivocompleto);
                            printf("Seleccione la columna que desea mostrar:\n");

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


void mostrarDatosCompletos(const char* nombre_archivo) {
    FILE* archivo = fopen("copiabonita.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char caracter;
    printf("Contenido del archivo %s:\n", nombre_archivo);
    while ((caracter = fgetc(archivo)) != EOF) {
        printf("%c", caracter);
    }

    printf("\n");

    fclose(archivo);
}

void copiarArchivoModificado(const char* nombre_origen, const char* nombre_destino) {
    FILE *archivo_origen, *archivo_destino;
    char caracter;

    archivo_origen = fopen("generacion.csv", "r");
    if (archivo_origen == NULL) {
        printf("No se pudo abrir el archivo de origen.\n");
        return;
    }

    archivo_destino = fopen(nombre_destino, "w");
    if (archivo_destino == NULL) {
        printf("No se pudo abrir el archivo de destino.\n");
        return;
    }

    while ((caracter = fgetc(archivo_origen)) != EOF) {
        if (caracter == ',' || caracter == ';'|| caracter == '"') {
            fputc(' ', archivo_destino);
        } else {
            fputc(caracter, archivo_destino);
        }
    }

    printf("El archivo ha sido copiado y modificado correctamente.\n");

    fclose(archivo_origen);
    fclose(archivo_destino);
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

/*void cadenasindependientes(FILE *archivo, int filas,int columnas,char datosindependientes[][560]){
    int i,j;
    archivo=fopen("generacion.csv","r");
    for(i=0;i<filas;i++){
        for(j=0;j<columnas;j++){
            fgets(datosindependientes[i][j],sizeof(datosindependientes),archivo);
        }
    }
    fclose(archivo);
}*/
