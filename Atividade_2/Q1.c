//Jonathas Gabriel e Uriel

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100
#define MAX_LINE 1000

typedef struct {
    int numeros[MAX];
    int qtd;
    int soma;
} Lista;

Lista listas[MAX];
int total_listas = 0;

void ordenando(int vector[], int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (vector[j] > vector[j + 1]) {
                int interm = vector[j + 1];
                vector[j + 1] = vector[j];
                vector[j] = interm;
            }
        }
    }
}

int capturar_lista(char entrance[]) {
    char *ptr = entrance;

    while ((ptr = strstr(ptr, "start")) != NULL) {
        ptr += 5; // pula "start"

        Lista nova;
        nova.qtd = 0;

        while (*ptr) {
            while (*ptr == ' ') ptr++;

            if (strncmp(ptr, "start", 5) == 0)
                break;

            int num;
            if (sscanf(ptr, "%d", &num) == 1) {
                nova.numeros[nova.qtd++] = num;
            }

            while (*ptr && !isspace(*ptr)) ptr++;
        }

        ordenando(nova.numeros, nova.qtd);

        nova.soma = 0;
        for (int i = 0; i < nova.qtd; i++)
            nova.soma += nova.numeros[i];

        listas[total_listas++] = nova;
    }

    return total_listas;
}

int remover_duplicadas(Lista listas[], int total) {
    int usadas[2001] = {0};  // deslocamento de -1000 a +1000
    Lista resultado[MAX];
    int nova_qtd = 0;

    for (int i = total - 1; i >= 0; i--) {
        int soma = listas[i].soma;
        if (!usadas[soma + 1000]) {
            usadas[soma + 1000] = 1;
            resultado[nova_qtd++] = listas[i];
        }
    }

    for (int i = 0; i < nova_qtd; i++) {
        listas[i] = resultado[nova_qtd - 1 - i];
    }

    return nova_qtd;
}

void ordenar_lista_por_soma(Lista lista[], int total) {
    for (int i = 0; i < total; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (lista[j].soma < lista[j + 1].soma) {
                Lista temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}

int main() {
    FILE* fp_in = fopen("L1Q1.in", "r");
    FILE* fp_out = fopen("L1Q1.out", "w");

    if (!fp_in || !fp_out) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    char linha[MAX_LINE];

    while (fgets(linha, sizeof(linha), fp_in)) {
        total_listas = 0; // zera para cada linha processada

        int total = capturar_lista(linha);

        total = remover_duplicadas(listas, total);

        ordenar_lista_por_soma(listas, total);

        for (int i = 0; i < total; i++) {
            fprintf(fp_out, "start");
            for (int j = 0; j < listas[i].qtd; j++) {
                fprintf(fp_out, " %d", listas[i].numeros[j]);
            }
            fprintf(fp_out, "\n");
        }
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}