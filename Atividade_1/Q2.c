#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TAM 50
#define MAX_TAM_STRING 500
#define MAX_PALAV 100 

int procurando_palavras(char string[], char palavras[][MAX_TAM]){
    int i = 0, palavra_idx = 0, letra_idx = 0; 
    
    while (string[i] != '\0'){
        if (isalpha(string[i])) {
            palavras[palavra_idx][letra_idx++] = string[i];
        } else if (letra_idx > 0) {
            palavras[palavra_idx][letra_idx] = '\0';
            palavra_idx++;
            letra_idx = 0;
        }
        i++;
    }

    if (letra_idx > 0) {
        palavras[palavra_idx][letra_idx] = '\0';
        palavra_idx++;
    }

    return palavra_idx;
}

void ordenando_palavras(char palavras[][MAX_TAM], int palavra_idx){
    char interm[MAX_TAM];

    for(int i = 0; i < palavra_idx - 1; i++){
        for(int j = i + 1; j < palavra_idx; j++){
            if(strcmp(palavras[i], palavras[j]) > 0) {
                strcpy(interm, palavras[i]);
                strcpy(palavras[i], palavras[j]);
                strcpy(palavras[j], interm);
            }
        }
    }
}

int procurando_numeros(char string[], float numeros[]){
    int i = 0, qtd = 0, temp_idx = 0;
    char num_encontrados[MAX_TAM];

    while(string[i] != '\0') {
        if(isdigit(string[i]) || string[i] == '.' || string[i] == '-'){
            num_encontrados[temp_idx++] = string[i];
        } else if (temp_idx > 0) {
            num_encontrados[temp_idx] = '\0';
            numeros[qtd++] = atof(num_encontrados);
            temp_idx = 0;

            if (qtd >= MAX_TAM_STRING) break;
        }
        i++;
    }

    if(temp_idx > 0 && qtd < MAX_TAM_STRING){
        num_encontrados[temp_idx] = '\0';
        numeros[qtd++] = atof(num_encontrados);
    }

    return qtd;
}

void ordenando_numeros(float numeros[], int numeros_idx){
    float interm = 0;

    for(int i = 0; i < numeros_idx; i++){
        for(int j = i + 1; j < numeros_idx; j++){
            if(numeros[i] > numeros[j]){
                interm = numeros[j];
                numeros[j] = numeros[i];
                numeros[i] = interm;
            }
        }
    }
}

int main(){
    FILE *fp_in = fopen("L0Q2.in", "r");
    FILE *fp_out = fopen("L0Q2.out", "w");

    if (fp_in == NULL || fp_out == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char string[MAX_TAM_STRING];
    char palavras[MAX_PALAV][MAX_TAM];
    float numeros[MAX_TAM_STRING];

    if (fgets(string, MAX_TAM_STRING, fp_in) == NULL) {
        fprintf(fp_out, "Erro ao ler a linha do arquivo.\n");
        return 1;
    }

    int qtd_palavras = procurando_palavras(string, palavras);
    ordenando_palavras(palavras, qtd_palavras);

    fprintf(fp_out, "Lista ordenada\n");
    fprintf(fp_out, "char: ");
    for(int i = 0; i < qtd_palavras; i++){
        fprintf(fp_out, "%s", palavras[i]);
        if(i < qtd_palavras - 1){
            fprintf(fp_out, ", ");
        } else{
            fprintf(fp_out, ".\n");
        }
    }

    int qtd_numeros = procurando_numeros(string, numeros);
    ordenando_numeros(numeros, qtd_numeros);

    fprintf(fp_out, "int/float: ");
    for(int i = 0; i < qtd_numeros; i++){
        fprintf(fp_out, "%.2f", numeros[i]);
        if(i < qtd_numeros - 1){
            fprintf(fp_out, ", ");
        } else{
            fprintf(fp_out, ".\n");
        }
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
