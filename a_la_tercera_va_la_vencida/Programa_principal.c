#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<locale.h>
struct DatosEnergia {
    char tipodeenergia[100];
    double consumo;
};
struct fila{
    char filascompletas[432];
};
struct Data {
    float value;
    char tipo;
};
struct Data2 {
    char value[1000];
};
void menuprincipal(void);
void copiarArchivoModificado(const char* nombre_origen, const char* nombre_destino);
void mostrardatoscompletos(struct fila *, FILE *, int);
void menubusqueda(void);
void menubusquedafecha(struct fila *,FILE *);
void menubusquedafechaenergia(struct fila *,FILE *,FILE *);
void mostrarenergias(void);
void agregarDatos(FILE *archivo);
void mostrarDatos(FILE *archivo);
float funcionmedia(int, struct Data x[]);
double funciondesvtipica(int,struct Data x[]);

//void cadenasindependientes(FILE *, int ,int ,char [][560]);
int main(){
    setlocale(LC_CTYPE,"Spanish");
    int eleccion,eleccionbusqueda,eleccion2;
    int i=0,n=0,ncomas=0,year,mes,energia;
    int operador1=0;
    char c,comas;
    char caracter;
    char nombre_archivo_destino[100] = "copiageneracion.csv";
    struct fila *nfilas; //Declaracion del puntero para reserva de memoria mas adelante
    FILE *archivocompleto,*file,*historial; //Declaracion del archivo principal
    char *token;
    char *prevToken = NULL;
    char line[1000];
    struct Data data[1000];
    struct Data2 data2[1000];
    int count = 0;
    float operacionmedia=0;
    float operaciondesvtipica=0;
    while(eleccion!=5)
        {
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
                    nfilas=(struct fila*)malloc(n*sizeof(struct fila));
                    fclose(archivocompleto);
            switch(eleccion){
                case 1:
                printf("\n\n\t1.\tVer datos completos.\n"); // comprobacion
                //copiarArchivoModificado(nombre_archivo_origen, nombre_archivo_destino);
                mostrarDatosCompletos(nombre_archivo_destino);
                //rewind(nombre_archivo_destino);
                //funcionhistorial(historial,archivocompleto);
                break;
                case 2:
                while(eleccionbusqueda!=4){
                    printf("Seleccione el tipo de busqueda que desea:\n");
                    menubusqueda();
                    scanf("%i",&eleccionbusqueda);
                    switch(eleccionbusqueda){
                        case 1:
                            menubusquedafecha(nfilas,archivocompleto);
                            printf("Indique el año: 21 o 22?\n");
                            scanf("%i",&year);
                            printf("Indique el mes: 1,2,3,...,12\n");
                            scanf("%i",&mes);
                            if(year==22){
                                operador1=12;
                            }else operador1=0;
                            file = fopen("copiageneracion.csv", "r");
                            if (file == NULL) {
                                printf("No se pudo abrir el archivo.\n");
                                return 1;
                            }
                            // Leer y procesar cada línea del archivo
                                while (fgets(line, sizeof(line), file) != NULL && count < 1000) {
                                    char *token;
                                    char *prevToken = NULL;
                                // Buscar la primera coma en la línea
                                    token = strtok(line, ",");
                                        while (token != NULL) {
                                            if (prevToken != NULL) {
                                            // Convertir la cadena de caracteres a un valor float
                                            data[count].value = atof(prevToken);
                                            // Almacenar el valor anterior a la coma en la estructura correspondiente
                                            strcpy(data2[count].value, prevToken);
                                            count++;
                                            }
                                        prevToken = token;
                                        token = strtok(NULL, ",");
                                        }
                                }
                            // Cerrar el archivo
                            fclose(file);
                            // Mostrar los valores almacenados en el vector de estructuras
                            historial=fopen("historial.csv","a");
                            for (i = 32; i < 324; i += 25) {
                            printf("%s \t", data2[i].value);
                            fputs(data2[i].value,historial);
                            }
                            printf("\n\n\n\n");
                            for (i = 32+mes+operador1; i < 332; i += 25) {
                            printf("%.5f        ", data[i].value);
                            fprintf(historial,"%.5f            ",data[i].value);
                            }
                            printf("\n\n\n\n");
                            for (i = 332; i < 458; i += 25) {
                            printf("%s\t", data2[i].value);
                            fputs(data2[i].value,historial);
                            }
                            printf("\n\n\n\n");
                            for (i = 332+mes+operador1; i < count; i += 25) {
                            printf("%.5f            ", data[i].value);
                            fprintf(historial,"%.5f            ",data[i].value);
                            }
                            printf("\n\n\n\n");
                        fclose(historial);
                        break;
                        case 2:
                            menubusquedafechaenergia(nfilas,archivocompleto,historial);
                        break;
                        case 3:
                            printf("Indique el año: 21 o 22?\n");
                            scanf("%i",&year);
                            printf("Indique el mes: 1,2,3,...,12\n");
                            scanf("%i",&mes);
                            printf("Indique el tipo de energia:\n");
                            mostrarenergias();
                            scanf("%i",&energia);
                            if(year==22){
                                operador1=12;
                            }
                            else operador1=0;
                            file = fopen("copiageneracion.csv", "r");
                            if (file == NULL) {
                                printf("No se pudo abrir el archivo.\n");
                                return 1;
                            }
                            // Leer y procesar cada línea del archivo
                                while (fgets(line, sizeof(line), file) != NULL && count < 1000) {
                                    char *token;
                                    char *prevToken = NULL;

                                // Buscar la primera coma en la línea
                                    token = strtok(line, ",");
                                        while (token != NULL) {
                                            if (prevToken != NULL) {
                                            // Convertir la cadena de caracteres a un valor float
                                            data[count].value = atof(prevToken);
                                            // Almacenar el valor anterior a la coma en la estructura correspondiente
                                            strcpy(data2[count].value, prevToken);
                                            count++;
                                            }
                                        prevToken = token;
                                        token = strtok(NULL, ",");
                                        }
                                }
                            // Cerrar el archivo
                            fclose(file);
                            // Mostrar los valores almacenados en el vector de estructuras
                            historial=fopen("historial.csv","a");
                            for (i = 32+25*energia-25; i <=32+25*energia-25 ; i ++) {
                            printf("%s \t", data2[i].value);
                            fputs(data2[i].value,historial);
                            }
                            printf("\n\n");
                            for (i = 32+mes+operador1+25*energia-25; i <=32+mes+operador1+25*energia-25 ; i++) {
                            printf("%.5f        \n\n\n\n", data[i].value);
                            fprintf(historial,"%.5f        \n\n\n\n", data[i].value);
                            }
                            fclose(historial);

                     break;
                    }
                    }
                break;
    case 3:
        {
            printf("Seleccione la operación estadistica que desea: media (1) o desviacion tipica(2)\n");
            scanf("%i",&eleccion2);
            switch (eleccion2){
            case 1:
                printf("aqui va la media de las generaciones\n");
                mostrarenergias();
                file = fopen("copiageneracion.csv", "r");
                            if (file == NULL) {
                                printf("No se pudo abrir el archivo.\n");
                                return 1;
                            }
                            // Leer y procesar cada línea del archivo
                                while (fgets(line, sizeof(line), file) != NULL && count < 1000) {
                                // Buscar la primera coma en la línea
                                    token = strtok(line, ",");
                                        while (token != NULL) {
                                            if (prevToken != NULL) {
                                            // Convertir la cadena de caracteres a un valor float
                                            data[count].value = atof(prevToken);
                                            count++;
                                            }
                                        prevToken = token;
                                        token = strtok(NULL, ",");
                                        }
                                }
                            // Cerrar el archivo
                            fclose(file);
                            historial=fopen("historial.csv","a");
                            printf("\nSeleccione el tipo de energia:\n");
                            scanf("%i",&energia);
                            operacionmedia=funcionmedia(energia,data);
                            printf("%.5f\n\n",operacionmedia);
                            fprintf(historial,"%.5f\n\n",operacionmedia);
                            fclose(historial);
            break;
            case 2:
                 mostrarenergias();
                file = fopen("copiageneracion.csv", "r");
                            if (file == NULL) {
                                printf("No se pudo abrir el archivo.\n");
                                return 1;
                            }
                            // Leer y procesar cada línea del archivo
                                while (fgets(line, sizeof(line), file) != NULL && count < 1000) {


                                // Buscar la primera coma en la línea
                                    token = strtok(line, ",");
                                        while (token != NULL) {
                                            if (prevToken != NULL) {
                                            // Convertir la cadena de caracteres a un valor float
                                            data[count].value = atof(prevToken);
                                            count++;
                                            }
                                        prevToken = token;
                                        token = strtok(NULL, ",");
                                        }
                                }
                            // Cerrar el archivo
                            fclose(file);
                            historial=fopen("historial.csv","a");
                            printf("\nSeleccione el tipo de energia:\n");
                            scanf("%i",&energia);
                            operaciondesvtipica=funciondesvtipica(energia,data);
                            printf("%.5f\n\n",operaciondesvtipica);
                            fprintf(historial,"%.5f\n\n",operaciondesvtipica);
                            fclose(historial);
            }
        }
        break;
                case 4:
                    historial=fopen("historial.csv","r");
                    if (historial == NULL) {
                        printf("No se pudo abrir el archivo.\n");
                        return 1;
                    }
                    while ((caracter = fgetc(historial)) != EOF) {
                        printf("%c", caracter);
                    }
                    fclose(historial);
                break;
            }
        }
    return 0;
}

void mostrarDatosCompletos(const char* nombre_archivo) {
    FILE* archivo = fopen("archivo_mas_bonito.csv", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char caracter;
    while ((caracter = fgetc(archivo)) != EOF) {
        printf("%c", caracter);
    }

    printf("\n\n\n");

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

    archivo_destino = fopen(nombre_destino, "a");
    if (archivo_destino == NULL) {
        printf("No se pudo abrir el archivo de destino.\n");
        return;
    }

    while ((caracter = fgetc(archivo_origen)) != EOF) {
        if ( caracter == '\0'|| caracter == '"') {
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
    printf("\t3.\tEstadisticas del archivo.\n");
    printf("\t4.\tHistorial.\n");
    printf("\t5.\tCerrar el programa.\n");
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
void menubusquedafechaenergia(struct fila *filafechas,FILE *fechas,FILE *historial){
    fechas=fopen("copiageneracion.csv","r");
    historial=fopen("historial.csv","a");
    int i,numero;
    printf("Seleccione con el numero el tipo de energia del que quiere ver los datos:\n");
    printf("1. Hidraulica\n");
    printf("2. Turbinacion bombeo\n");
    printf("3. Nuclear\n");
    printf("4. Carbon\n");
    printf("5. Fuel + Gas\n");
    printf("6. Motores diesel\n");
    printf("7. Turbina de gas\n");
    printf("8. Turbina de vapor\n");
    printf("9. Ciclo combinado\n");
    printf("10. Hidroeolica\n");
    printf("11. Eolica\n");
    printf("12. Solar fotovoltaica\n");
    printf("13. Solar termica\n");
    printf("14. Otras renovables\n");
    printf("15. Cogeneracion\n");
    printf("16. Residuos no renovables\n");
    printf("17. Residuos renovables\n");
    printf("18. Generacion total\n");
    scanf("%i",&numero);
    for(i=0;i<=25;i++){
        fgets(filafechas[i].filascompletas,sizeof(filafechas[i].filascompletas),fechas);
    }
    for(i=4+numero;i<=4+numero;i++){
	printf ("%s\n",filafechas[i].filascompletas);
	fputs(filafechas[i].filascompletas,historial);
    fclose(fechas);
    fclose(historial);
}
}

void mostrarenergias(void){
    printf("Seleccione con el numero el tipo de energia del que quiere ver los datos:\n");
    printf("1. Hidraulica\n");
    printf("2. Turbinacion bombeo\n");
    printf("3. Nuclear\n");
    printf("4. Carbon\n");
    printf("5. Fuel + Gas\n");
    printf("6. Motores diesel\n");
    printf("7. Turbina de gas\n");
    printf("8. Turbina de vapor\n");
    printf("9. Ciclo combinado\n");
    printf("10. Hidroeolica\n");
    printf("11. Eolica\n");
    printf("12. Solar fotovoltaica\n");
    printf("13. Solar termica\n");
    printf("14. Otras renovables\n");
    printf("15. Cogeneracion\n");
    printf("16. Residuos no renovables\n");
    printf("17. Residuos renovables\n");
    printf("18. Generacion total\n");
}

float funcionmedia(int energia,struct Data x[]){
    int i=0,dim=24;
    float media,sumatorio=0;
    for(i=38+26*energia-26;i<(38+26*energia-26)+24;i++){
        sumatorio+=x[i].value;
        //printf("Posicion %i: %.2f\n",i,x[i].value); Comprobación
    }
    media=sumatorio/dim;
    return media;
}

double funciondesvtipica (int energia,struct Data x[])
{
    int i, dim=24;
    int media;
    float sumatorio=0;
    double varianza = 0,diff=0,potencia=0,desvtipica=0;
    for(i=38+26*energia-26;i<(38+26*energia-26)+24;i++){
        sumatorio+=x[i].value;
    //printf("Posicion %i: %.2f\n",i,x[i].value); Comprobación
    }
    media=sumatorio/dim;
    for(i=38+26*energia-26;i<(32+26*energia-26)+24;i++) {
            diff=x[i].value-media;
            potencia+=pow(diff,2);
    //double diff = sumatorio*(sqrt(energia - media));
    //varianza += diff / dim;
    }
        varianza=potencia/dim;
        if (energia >= 1) {
        desvtipica = sqrt(varianza);
    }
    return desvtipica;
}
