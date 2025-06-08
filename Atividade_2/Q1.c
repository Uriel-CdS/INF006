#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

void ordering(int vector[], int qtd){
    for(int i = 0; i < qtd - 1; i++){
        for(int j = 0; j < qtd - i - 1; j++){
            if(vector[j] > vector[j + 1]){
                int interm = vector[j + 1];
                vector[j + 1] = vector[j];
                vector[j] = interm;
            }
        }
    }
}

void capture(char entrance[]) {

    int numbers[MAX];
    int qtd = 0;

    char *ptr = entrance;

    while ((ptr = strstr(ptr, "start")) != NULL) {
        ptr += 5; // Pula a palavra "start"

        // Captura os números depois de "start" até achar outro "start" ou fim de linha
        while (*ptr) {
            // Ignora espaços
            while (*ptr == ' ') ptr++;

            // Se acharmos outra palavra "start", paramos esse bloco
            if (strncmp(ptr, "start", 5) == 0)
                break;

            int num;

            sscanf(ptr, "%d", &num);

            numbers[qtd++] = num;

            // Avança o ponteiro até depois do número
            while (*ptr && !isspace(*ptr)) ptr++;
        }

        // Ordena a lista atual
        ordering(numbers, qtd);

        printf("start");
        for(int i = 0; i < qtd; i++){
            printf(" %d", numbers[i]);
        }
        printf("\n");

        qtd = 0; // Reseta o contador para a próxima lista
    }
}

int main(){

    char str[1000];

    printf("Digite: ");
    scanf(" %[^\n]", str);

    capture(str);

    return 0;
}
