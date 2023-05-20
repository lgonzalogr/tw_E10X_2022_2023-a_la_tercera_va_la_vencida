#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct fila{
    char filascompletas[432];
};

typedef struct {
    float value;
    char tipo;
} Data;

typedef struct {
    char value[1000];
} Data2;

void menuprincipal(void);
void copiarArchivoModificado(const char* nombre_origen, const char* nombre_destino);
void mostrardatoscompletos(struct fila *, FILE *, int);
void ordenarMenorMayor(const char* nombre_origen, const char* nombre_destino);
void ordenarMayorMenor(const char* nombre_origen, const char* nombre_destino);
void escribirMenorMayor(const char* nombre_archivo_origen, const char* nombre_archivo_destino);
void escribirMayorMenor(const char* nombre_archivo_origen, const char* nombre_archivo_destino);
void menubusqueda(void);
void menubusquedafecha(struct fila *,FILE *);
void datosindependientes(FILE *,struct datos *,struct datos *);
void menubusquedafechaenergia(struct fila *,FILE *);
//void cadenasindependientes(FILE *, int ,int ,char [][560]);
int main(){
    int eleccion,eleccionbusqueda,eleccion2;
    int i=0,j,n=0,ncomas=0,year,mes;
    int contador=0;
    int operador1=0,operador2=0;
    char c,comas;
    char filasindependientes[1000];
    char nombre_archivo_origen[100] = "generacion.csv";
    char nombre_archivo_destino[100] = "copiageneracion.csv";
    char nombre_archivo_mayor_menor[100] = "mayormenor.txt";
    char nombre_archivo_menor_mayor[100] = "menormayor.txt";
    struct fila *nfilas; //Declaracion del puntero para reserva de memoria mas adelante
    FILE *archivocompleto, copiabonita,*file; //Declaracion del archivo principal

    char line[1000];
    Data data[1000];
    Data2 data2[1000];
    int count = 0;

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

                            for (i = 32; i < 324; i += 25) {
                            printf("%s \t", data2[i].value);
                            }
                            printf("\n\n\n\n");
                            for (i = 32+mes+operador1; i < 332; i += 25) {
                            printf("%.5f        ", data[i].value);
                            }
                            printf("\n\n\n\n");
                            for (i = 332; i < 458; i += 25) {
                            printf("%s\t", data2[i].value);
                            }
                            printf("\n\n\n\n");
                            for (i = 332+mes+operador1; i < count; i += 25) {
                            printf("%.5f            ", data[i].value);
                            }
                            printf("\n\n\n\n");

                        case 2:
                            menubusquedafechaenergia(nfilas,archivocompleto);

                    }


                    }
                break;
    case 3:
         printf("Seleccione los datos que desea añadir:\n");
        break;
    case 4:
        {
            printf("Seleccione la operación estadistica que desea: mayor a menor (1) o menor a mayor(2)\n");
            scanf("%i",&eleccion2);
            switch (eleccion2){

            case 1:
                printf("Contenido del archivo 'mayormenor.txt':\n");

            case 2:
                printf("Contenido del archivo 'menormayor.txt':\n");
        ordenarMenorMayor(nombre_archivo_destino, nombre_archivo_menor_mayor);
        printf("Contenido del archivo 'menormayor.txt':\n");
        mostrarDatosCompletos(nombre_archivo_menor_mayor);

            }
        }

        break;
    case 5:
        printf("Indique como desea ver el historial:\n");
        }


        }





    return 0;
}


void mostrarDatosCompletos(const char* nombre_archivo) {
    FILE* archivo = fopen("copiageneracion.csv", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char caracter;
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
    printf("\t3.\tAñadir datos.\n");
    printf("\t4.\tEstadísticas del archivo.\n");
    printf("\t5.\tHistorial.\n");
    printf("\t6.\tCerrar el programa.\n");
}


void ordenarMenorMayor(const char* nombre_origen, const char* nombre_destino) {
    FILE *archivo_origen, *archivo_destino;
    char caracter;
    char* datos;
    int num_datos = 0;

    archivo_origen = fopen("generacion.csv", "r");
    if (archivo_origen == NULL) {
        printf("No se pudo abrir el archivo de origen.\n");
        return;
    }

    archivo_destino = fopen("menormayor.txt", "w");
    if (archivo_destino == NULL) {
        printf("No se pudo abrir el archivo de destino.\n");
        return;
    }

    // Saltar las primeras 5 filas
    for (int i = 0; i < 5; i++) {
        while ((caracter = fgetc(archivo_origen)) != '\n' && caracter != EOF);
    }

    // Obtener el número de datos en el archivo de origen
    while ((caracter = fgetc(archivo_origen)) != EOF) {
        if (caracter == ',' || caracter == ';') {
            num_datos++;
        }
    }
    num_datos++;  // Sumar uno más para contar el último dato sin coma o punto y coma

    // Volver al inicio del archivo de origen
    fseek(archivo_origen, 0, SEEK_SET);

    // Saltar las primeras 5 filas
    for (int i = 0; i < 5; i++) {
        while ((caracter = fgetc(archivo_origen)) != '\n' && caracter != EOF);
    }

    // Leer y almacenar los datos en un arreglo
    datos = (char*)malloc(num_datos * sizeof(char));
    int i = 0;
    while ((caracter = fgetc(archivo_origen)) != EOF) {
        if (caracter != ',' && caracter != ';') {
            datos[i] = caracter;
            i++;
        }
    }
    datos[i] = '\0';  // Agregar el carácter nulo al final del arreglo de datos

    // Ordenar los datos de menor a mayor
    for (int j = 0; j < num_datos - 1; j++) {
        for (int k = j + 1; k < num_datos; k++) {
            if (datos[j] > datos[k]) {
                char temp = datos[j];
                datos[j] = datos[k];
                datos[k] = temp;
            }
        }
    }

    // Guardar los datos ordenados en el archivo de destino
    for (int j = 0; j < num_datos - 1; j++) {
        if (datos[j] == ',' || datos[j] == ';') {
            fputc(' ', archivo_destino);
        } else {
            fputc(datos[j], archivo_destino);
        }
    }
    fputc(datos[num_datos - 1], archivo_destino);

    printf("El archivo ha sido copiado y ordenado de menor a mayor correctamente.\n");

    fclose(archivo_origen);
    fclose(archivo_destino);
    free(datos);
}

void ordenarMayorMenor(const char* nombre_origen, const char* nombre_destino) {
    FILE *archivo_origen, *archivo_destino;
    char caracter;
    char* datos;
    int num_datos = 0;

    archivo_origen = fopen("generacion.csv", "r");
    if (archivo_origen == NULL) {
        printf("No se pudo abrir el archivo de origen.\n");
        return;
    }

    archivo_destino = fopen("mayormenor.txt", "w");
    if (archivo_destino == NULL) {
        printf("No se pudo abrir el archivo de destino.\n");
        return;
    }

    // Saltar las primeras 5 filas
    for (int i = 0; i < 5; i++) {
        while ((caracter = fgetc(archivo_origen)) != '\n' && caracter != EOF);
    }

    // Obtener el número de datos en el archivo de origen
    while ((caracter = fgetc(archivo_origen)) != EOF) {
        if (caracter == ',' || caracter == ';') {
            num_datos++;
        }
    }
    num_datos++;  // Sumar uno más para contar el último dato sin coma o punto y coma

    // Volver al inicio del archivo de origen
    fseek(archivo_origen, 0, SEEK_SET);

    // Saltar las primeras 5 filas
    for (int i = 0; i < 5; i++) {
        while ((caracter = fgetc(archivo_origen)) != '\n' && caracter != EOF);
    }

    // Leer y almacenar los datos en un arreglo
    datos = (char*)malloc(num_datos * sizeof(char));
    int i = 0;
    while ((caracter = fgetc(archivo_origen)) != EOF) {
        if (caracter != ',' && caracter != ';') {
            datos[i] = caracter;
            i++;
        }
    }
    datos[i] = '\0';  // Agregar el carácter nulo al final del arreglo de datos

    // Ordenar los datos de mayor a menor
    for (int j = 0; j < num_datos - 1; j++) {
        for (int k = j + 1; k < num_datos; k++) {
            if (datos[j] < datos[k]) {
                char temp = datos[j];
                datos[j] = datos[k];
                datos[k] = temp;
            }
        }
    }

    // Guardar los datos ordenados en el archivo de destino
    for (int j = 0; j < num_datos - 1; j++) {
        if (datos[j] == ',' || datos[j] == ';') {
            fputc(' ', archivo_destino);
        } else {
            fputc(datos[j], archivo_destino);
        }
    }
    fputc(datos[num_datos - 1], archivo_destino);

    printf("El archivo ha sido copiado y ordenado de mayor a menor correctamente.\n");

    fclose(archivo_origen);
    fclose(archivo_destino);
    free(datos);
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
void menubusquedafechaenergia(struct fila *filafechas,FILE *fechas){
    fechas=fopen("copiageneracion.csv","r");
    int i,numero;
    printf("Seleccione con el numero el tipo de energia:\n");
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
    fclose(fechas);
}
}

