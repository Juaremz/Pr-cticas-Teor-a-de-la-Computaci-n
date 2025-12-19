#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Nodo {

    char* dato;
    struct Nodo* siguiente;

}Nodo;

void concatenacion(Nodo** cabeza);
void potencia(Nodo** cabeza, char cad[]);
void longitudCadena(char cad[]);
void prefijos(char cad[]);
void sufijos(char cad[]);
void subcadenas(char cad[]);
char* crearCadenaSinCaracter(const char* original, int indice);
int existeEnLista(Nodo* cabeza, const char* cadena);
void generarSubsecuenciasRecursivo(Nodo** cabeza, const char* cad_actual);
void mostrarListaSubsecuencias(Nodo* cabeza);
void subsecuencias(Nodo** cabeza, char cad[]);
void menu(Nodo** cabeza, char cad[]);

void menu(Nodo** cabeza, char cad[]){

    int opc;

    printf("\n\n\n\t Elige una opcion: \n");
    printf("\n 1. Concatenacion");
    printf("\n 2. Potencia");
    printf("\n 3. Calculo de la longitud");
    printf("\n 4. Generacion de prefijos");
    printf("\n 5. Generacion de sufijos");
    printf("\n 6. Generacion de subcadenas");
    printf("\n 7. Generacion de subsecuencias");
    printf("\n 8. Salir");
    printf("\n\n Opcion? ");
    scanf("%i", &opc);
    
    printf("\n");

    switch(opc){
    
        case 1:
            concatenacion(cabeza);
            menu(cabeza, cad);
        break;
            
        case 2:
            potencia(cabeza, cad);
            menu(cabeza, cad);
        break;
        
        case 3:
            longitudCadena(cad);
            menu(cabeza, cad);
        break;
        
        case 4:
            prefijos(cad);
            menu(cabeza, cad);
        break;
        
        case 5:
            sufijos(cad);
            menu(cabeza, cad);
        break;
        
        case 6:
            subcadenas(cad);
            menu(cabeza, cad);
        break;
        
        case 7:
            subsecuencias(cabeza, cad);
            menu(cabeza, cad);
        break;

        case 8:
            printf("Vuelve pronto! :)\n\n");
        break;
        
        default:
            printf("Opcion no valida, ingrese una del menu...");
            menu(cabeza, cad);
        break;
        
    }
    

}

Nodo* crearNodo(const char* dato){

    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    
    if(nuevo == NULL){
        
        printf("Error: memoria insuficiente\n");
        exit(1);

    }

    nuevo->dato = (char*)malloc(strlen(dato) + 1);
    
    if(nuevo->dato == NULL){

        printf("Error: Memoria insuficiente\n");
        free(nuevo);
        exit(1);

    }

    strcpy(nuevo->dato, dato);
    
    nuevo->siguiente = NULL;
    return nuevo;

}

void mostrarLista(Nodo* cabeza){

    Nodo* actual = cabeza;

    if(actual == NULL){
        
        printf("Cadena vacia\n");
        return;
    }

    printf("Resultado: ");

    while(actual != NULL){
        printf("%s", actual->dato);
        actual = actual->siguiente;
    }
    
    printf("\n");

}

void liberarLista(Nodo* cabeza){

    Nodo* actual = cabeza;

    while(actual != NULL){
        Nodo* temp = actual;
        actual = actual->siguiente;
        free(temp->dato);
        free(temp);
    }
    
}

void concatenacion(Nodo** cabeza){

    char cad2[50];

    printf("Ingresa la segunda cadena para concatenar (si deseas concatenar una cadena vacia ingresa 0): ");
    scanf("%s", cad2);
    
    Nodo* nuevo = crearNodo(cad2);

    if(strcmp(cad2, "0") == 0){

        mostrarLista(*cabeza);
        return;

    }else if(*cabeza == NULL){
        *cabeza = nuevo;
    }else{
        Nodo* actual = *cabeza;
        while(actual->siguiente != NULL){
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }

    mostrarLista(*cabeza);
    
}

void invertirCadena(char* cad){
    
    int lon = strlen(cad);
    char temp;

    for(int i = 0, j = lon-1; i<j; i++, j--){
        temp = cad[i];
        cad[i] = cad[j];
        cad[j] = temp;
    }

}

void potencia(Nodo** cabeza, char cad[]){

    int pot;
    
    printf("Ingresa el valor de la potencia: ");
    scanf("%i", &pot);

    int absPot = abs(pot);
    
    if(*cabeza != NULL){
        
        liberarLista(*cabeza);
        *cabeza = NULL;
    }

    if(pot == 0){
        
        printf("Potencia: Cadena vacia");
        return;
    
    }if(pot < 0){ 

        invertirCadena(cad);

    }


        for(int i=1; i <= absPot; i++){
            
            Nodo* nuevo = crearNodo(cad);
            
            if(*cabeza == NULL){
                *cabeza = nuevo;
            }else{
                Nodo* actual = *cabeza;
                while(actual->siguiente != NULL){
                    actual = actual->siguiente;
                }
                actual->siguiente = nuevo;
            }
            
        }

        mostrarLista(*cabeza);

    
}

void longitudCadena(char cad[]){
    
    int lon = 0;
    
    while(cad[++lon] != 0); // incrementar� la variable y regresar� el valor despu�s de incrementarla
    printf("La longitud de %s es %d", cad, lon);
    
}

void prefijos(char cad[]){
    
    int l = strlen(cad);
    char cadMod[50];

    for(int i=0; i<=l; i++){
        cadMod[i] = cad[i];
    }

    for(int i=0; i<=l; i++){
        printf("Prefijo %d: ", i);
        for(int j=0; j<i; j++){
            printf("%c", cadMod[j]);
        }
        printf("\n");
    }

}

void sufijos(char cad[]){
    
    int l = strlen(cad);
    char cadMod[50];

    for(int i=0; i<=l; i++){
        cadMod[i] = cad[i];
    }

    invertirCadena(cadMod);

    for(int i=0; i<=l; i++){
        printf("Sufijo %d: ", i);
        for(int j=i-1; j<l && j>=0; j--){
            printf("%c", cadMod[j]);
        }
        printf("\n");
    }

}

void subcadenas(char cad[]){

    int l = strlen(cad);

    printf("\n");
    
    for(int i=0; i<=l; i++){
    
        for(int j=0; j<l-i; j++){

            for(int k=0; k<=i; k++){

                printf("%c", cad[j+k]);

            }
            
            printf("\n");

        }

    }

}

void eliminarElemento(Nodo** cabeza, const char* datoEli){

    Nodo* actual = *cabeza;
    Nodo* anterior = NULL;

    while(actual != NULL && strcmp(actual->dato, datoEli) != 0) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("El elemento no se encontro en la lista.\n");
        return;
    }
    
    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    
    free(actual->dato);
    free(actual);
    printf("Elemento eliminado exitosamente.\n");

}

char* crearCadenaSinCaracter(const char* original, int indice) {
    
    int lon = strlen(original);

    if (indice < 0 || indice >= lon) {
        return NULL;
    }

    
    char* nueva = (char*)malloc(lon);
    
    if (nueva == NULL) {
        return NULL;
    }

    strncpy(nueva, original, indice);
    strcpy(nueva + indice, original + indice + 1);

    return nueva;

}

int existeEnLista(Nodo* cabeza, const char* dato) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        if (strcmp(actual->dato, dato) == 0) {
            return 1;
        }
        actual = actual->siguiente;
    }
    return 0;
}

void generarSubsecuenciasRecursivo(Nodo** cabeza, const char* cad_actual) {
    int lon = strlen(cad_actual);

    if (lon <= 1) {
        if (!existeEnLista(*cabeza, cad_actual)) {
            Nodo* nuevo_nodo = crearNodo(cad_actual);
            if (*cabeza == NULL) {
                *cabeza = nuevo_nodo;
            } else {
                Nodo* actual = *cabeza;
                while (actual->siguiente != NULL) {
                    actual = actual->siguiente;
                }
                actual->siguiente = nuevo_nodo;
            }
        }
        return;
    }

    if (!existeEnLista(*cabeza, cad_actual)) {
        Nodo* nuevo_nodo = crearNodo(cad_actual);
        if (*cabeza == NULL) {
            *cabeza = nuevo_nodo;
        } else {
            Nodo* actual = *cabeza;
            while (actual->siguiente != NULL) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo_nodo;
        }
    }

    for (int i = 0; i < lon; i++) {
        char* sub_cadena = crearCadenaSinCaracter(cad_actual, i);
        if (sub_cadena != NULL) {
            generarSubsecuenciasRecursivo(cabeza, sub_cadena);
            free(sub_cadena);
        }
    }
}

void mostrarListaSubsecuencias(Nodo* cabeza) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        printf("%s", actual->dato);
        if (actual->siguiente != NULL) {
            printf(", ");
        }
        actual = actual->siguiente;
    }
    printf("\n");
}

void subsecuencias(Nodo** cabeza, char cad[]) {
    int l = strlen(cad);

    if (l > 14) {
        printf("La cadena excede el limite de caracteres (máximo 14).\n");
        return;
    }

    liberarLista(*cabeza);
    *cabeza = NULL;

    generarSubsecuenciasRecursivo(cabeza, cad);

    printf("Las subsecuencias generadas son:\n");
    mostrarListaSubsecuencias(*cabeza);

}


int main(){
    
    int numcad;
    char cad1[50];
    char cad2[50]; 
    
    //Variables para concatenar cadenas
    char cadCon[100];
    char *ptrcadCon = cadCon;
    char *ptrcad1 = cad1;
    char *ptrcad2 = cad2;

    Nodo* cabeza = NULL;
     
    printf("Con cuantas cadenas desea trabajar: ");
    scanf("%i", &numcad);
    fflush(stdin);
     
    if(numcad == 1){

    printf("Ingresa la cadena alfanumerica: ");
    scanf("%s", cad1);
    Nodo* nodoMain = crearNodo(cad1);
    nodoMain->siguiente = cabeza;
    cabeza = nodoMain;
    menu(&cabeza, cad1);
     
    }if(numcad == 2){
        
    printf("Ingresa la primer cadena alfanumerica: ");
    scanf("%s", cad1);
    printf("Ingresa la segunda cadena alfanumerica: ");
    scanf("%s", cad2);

    printf("Cadenas ingresadas: \n 1- %s \n 2- %s", cad1, cad2);

            
            while(*ptrcad1 != '\0'){
                
                *ptrcadCon = *ptrcad1;
                ptrcadCon++;
                ptrcad1++;
            }

            *ptrcadCon = '\0';

            while(*ptrcadCon != '\0'){
                
                ptrcadCon++;
            
            }

            while(*ptrcad2 != '\0'){
        
                *ptrcadCon = *ptrcad2;
                ptrcadCon++;
                ptrcad2++;
            }
    
            *ptrcadCon = '\0';

            printf("\n La cadena concatenada es: %s\n", cadCon);
            Nodo* nodoMain = crearNodo(cadCon);
            nodoMain->siguiente = cabeza;
            cabeza = nodoMain;
            menu(&cabeza, cadCon);
    }

        return 0;
    
}
