//Jonathas Gabriel e Uriel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 3001
#define MAX_NAMES_STACK 100
#define MAX_NAME_LEN 50
#define MAX_OUTPUT_BUFFER_LEN (MAX_NAMES_STACK * (MAX_NAME_LEN + 6 + 1) + MAX_NAMES_STACK * 10)

typedef struct {
    char nomes[MAX_NAMES_STACK][MAX_NAME_LEN];
    int topo;
} StackNomes;

void inicializar_stack(StackNomes *s);
int stack_vazia(StackNomes *s);
int stack_cheia(StackNomes *s);
void inserir_stack(StackNomes *s, const char *nome);
char* remover_stack(StackNomes *s);

int comparar_nomes(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

void inicializar_stack(StackNomes *s) {
    s->topo = -1;
}

int stack_vazia(StackNomes *s) {
    return (s->topo == -1);
}

int stack_cheia(StackNomes *s) {
    return (s->topo == MAX_NAMES_STACK - 1);
}

void inserir_stack(StackNomes *s, const char *nome) {
    if (stack_cheia(s)) {
        return;
    }
    s->topo++;
    strcpy(s->nomes[s->topo], nome);
}

char* remover_stack(StackNomes *s) {
    if (stack_vazia(s)) {
        return NULL;
    }
    return s->nomes[s->topo--];
}

void adicionar_operacao_buffer(char *buffer, const char *op, int *primeira_op_ptr) {
    if (!(*primeira_op_ptr)) {
        strcat(buffer, " ");
    }
    strcat(buffer, op);
    *primeira_op_ptr = 0;
}

void processar_linha(char *linha, FILE *fp_out) {
    StackNomes s;
    inicializar_stack(&s);

    char nomes_removidos_temp[MAX_NAMES_STACK][MAX_NAME_LEN];
    int contador_removidos;

    char buffer_saida[MAX_OUTPUT_BUFFER_LEN];
    buffer_saida[0] = '\0';

    int primeira_operacao = 1;

    char *token = strtok(linha, " ");
    while (token != NULL) {
        char novo_nome[MAX_NAME_LEN];
        strcpy(novo_nome, token);

        contador_removidos = 0;

        while (!stack_vazia(&s) && strcmp(s.nomes[s.topo], novo_nome) > 0) {
            strcpy(nomes_removidos_temp[contador_removidos], remover_stack(&s));
            contador_removidos++;
        }

        if (contador_removidos > 0) {
            char str_operacao_remover[20];
            sprintf(str_operacao_remover, "%dx-pop", contador_removidos);
            adicionar_operacao_buffer(buffer_saida, str_operacao_remover, &primeira_operacao);
        }

        inserir_stack(&s, novo_nome);
        char str_operacao_inserir[MAX_NAME_LEN + 6];
        sprintf(str_operacao_inserir, "push-%s", novo_nome);
        adicionar_operacao_buffer(buffer_saida, str_operacao_inserir, &primeira_operacao);

        for (int i = contador_removidos - 1; i >= 0; i--) {
            inserir_stack(&s, nomes_removidos_temp[i]);
            sprintf(str_operacao_inserir, "push-%s", nomes_removidos_temp[i]);
            adicionar_operacao_buffer(buffer_saida, str_operacao_inserir, &primeira_operacao);
        }

        token = strtok(NULL, " ");
    }

    fprintf(fp_out, "%s\n", buffer_saida);
}

int main() {
    FILE *fp_in = fopen("L1Q2.in", "r");
    FILE *fp_out = fopen("L1Q2.out", "w");

    if (!fp_in || !fp_out) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    char linha[MAX_LINE];

    while (fgets(linha, sizeof(linha), fp_in)) {
        size_t len = strlen(linha);
        if (len > 0 && linha[len - 1] == '\n') {
            linha[len - 1] = '\0';
        }

        processar_linha(linha, fp_out);
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}