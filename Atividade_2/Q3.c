//Jonathas Gabriel e Uriel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE 4000

typedef struct NodoInterno {
    float valor;
    struct NodoInterno* proximo;
} NodoInterno;

typedef struct NodoExterno {
    int chave;
    NodoInterno* sublista;
    struct NodoExterno* anterior;
    struct NodoExterno* proximo;
} NodoExterno;

NodoExterno* criarNodoExterno(int chave) {
    NodoExterno* novo = (NodoExterno*)malloc(sizeof(NodoExterno));
    novo->chave = chave;
    novo->sublista = NULL;
    novo->anterior = NULL;
    novo->proximo = NULL;
    return novo;
}

NodoInterno* criarNodoInterno(float valor) {
    NodoInterno* novo = (NodoInterno*)malloc(sizeof(NodoInterno));
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

void adicionarOrdenadoExterno(NodoExterno** inicio, int chave) {
    NodoExterno* novo = criarNodoExterno(chave);
    if (*inicio == NULL || chave < (*inicio)->chave) {
        novo->proximo = *inicio;
        if (*inicio) (*inicio)->anterior = novo;
        *inicio = novo;
        return;
    }

    NodoExterno* atual = *inicio;
    while (atual->proximo && atual->proximo->chave < chave)
        atual = atual->proximo;

    novo->proximo = atual->proximo;
    if (atual->proximo) atual->proximo->anterior = novo;
    atual->proximo = novo;
    novo->anterior = atual;
}

void adicionarInterno(NodoInterno** inicio, float valor) {
    NodoInterno* novo = criarNodoInterno(valor);
    if (!*inicio) {
        *inicio = novo;
        novo->proximo = novo;
        return;
    }

    NodoInterno* atual = *inicio;
    while (atual->proximo != *inicio)
        atual = atual->proximo;
    atual->proximo = novo;
    novo->proximo = *inicio;
}

void vincularListas(NodoExterno* listaExterna, NodoInterno* listaInterna) {
    if (!listaInterna) return;
    NodoInterno* inicio = listaInterna;
    do {
        NodoExterno* atualExterno = listaExterna;
        while (atualExterno) {
            if (fabs(listaInterna->valor - atualExterno->chave) < 1.0) {
                NodoInterno* novo = criarNodoInterno(listaInterna->valor);
                novo->proximo = atualExterno->sublista;
                atualExterno->sublista = novo;
                break;
            }
            atualExterno = atualExterno->proximo;
        }
        listaInterna = listaInterna->proximo;
    } while (listaInterna != inicio);
}

void exibirResultado(NodoExterno* listaExterna, FILE* fp_out) {
    fprintf(fp_out, "[");
    NodoExterno* atual = listaExterna;
    while (atual) {
        fprintf(fp_out, "%d(", atual->chave);

        NodoInterno* sub = atual->sublista;
        NodoInterno* ordenada = NULL;
        while (sub) {
            NodoInterno* no = criarNodoInterno(sub->valor);
            if (!ordenada || no->valor > ordenada->valor) {
                no->proximo = ordenada;
                ordenada = no;
            } else {
                NodoInterno* temp = ordenada;
                while (temp->proximo && temp->proximo->valor > no->valor)
                    temp = temp->proximo;
                no->proximo = temp->proximo;
                temp->proximo = no;
            }
            sub = sub->proximo;
        }

        NodoInterno* ptr = ordenada;
        while (ptr) {
            fprintf(fp_out, "%.2f", ptr->valor);
            if (ptr->proximo) fprintf(fp_out, "−>");
            ptr = ptr->proximo;
        }
        fprintf(fp_out, ")");

        if (atual->proximo) fprintf(fp_out, "->");
        atual = atual->proximo;

        while (ordenada) {
            NodoInterno* temp = ordenada;
            ordenada = ordenada->proximo;
            free(temp);
        }
    }
    fprintf(fp_out, "]\n");
}

void liberarMemoria(NodoExterno* listaExterna) {
    while (listaExterna) {
        NodoExterno* tempExterno = listaExterna;
        listaExterna = listaExterna->proximo;

        NodoInterno* listaInt = tempExterno->sublista;
        while (listaInt) {
            NodoInterno* tempInterno = listaInt;
            listaInt = listaInt->proximo;
            free(tempInterno);
        }
        free(tempExterno);
    }
}

int main() {
    FILE* fp_in = fopen("L1Q3.in", "r");
    FILE* fp_out = fopen("L1Q3.out", "w");

    if (!fp_in || !fp_out) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    char linha[MAX_LINE];

    while (fgets(linha, sizeof(linha), fp_in)) {
        NodoExterno* listaExterna = NULL;
        NodoInterno* listaInterna = NULL;

        char* token = strtok(linha, " \n");
        int modo = 0;

        while (token) {
            if (strcmp(token, "LE") == 0) {
                modo = 0;
            } else if (strcmp(token, "LI") == 0) {
                modo = 1;
            } else {
                if (modo == 0) {
                    adicionarOrdenadoExterno(&listaExterna, atoi(token));
                } else {
                    adicionarInterno(&listaInterna, atof(token));
                }
            }
            token = strtok(NULL, " \n");
        }

        vincularListas(listaExterna, listaInterna);
        exibirResultado(listaExterna, fp_out);
        liberarMemoria(listaExterna);
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}