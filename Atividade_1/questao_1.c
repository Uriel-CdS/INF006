#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAM_STR 500
#define TAM_COORD 300

int procurando(char string[], int (*vec)[2]) {
    int x = 0, y = 0;
    int j = 0;

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == '(') {
            int offset;
            if (sscanf(&string[i], "(%d,%d)%n", &x, &y, &offset) == 2) {
                vec[j][0] = x;
                vec[j][1] = y;
                j++;
                i += offset - 1; // evita reler o mesmo trecho
            }
        }
    }
    return j;
}

void ordenando(int (*vec)[2], int n){

    int temp_x, temp_y;

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(vec[i][0] > vec[j][0] ||
              (vec[i][0] == vec[j][0] && 
               vec[i][1] > vec[j][1])){

                temp_x = vec[i][0];
                temp_y = vec[i][1];

                vec[i][0] = vec[j][0];
                vec[i][1] = vec[j][1];

                vec[j][0] = temp_x;
                vec[j][1] = temp_y;
            }
        }
    }
}

void imprimindo(int (*vec)[2], int n){
    for(int i = 0; i < n; i++){
        printf("(%d, %d)", vec[i][0], vec[i][1]);
        if(i < n - 1) printf(", ");
    }
    printf("\n");
}

float distancia(int (*vec)[2], int n){

    float soma = 0.0;

    for(int i = 0; i < n - 1; i++){

        int dx = vec[i + 1][0] - vec[i][0]; 
        int dy = vec[i + 1][1] - vec[i][1];
        
        soma += sqrt(dx * dx + dy * dy);

    }

    return soma;
}

float distancia_extremos(int (*vec)[2], int n){

    int dx = vec[n - 1][0] - vec[0][0];
    int dy = vec[n - 1][1] - vec[0][1];

    return sqrt(dx * dx + dy * dy);
}

int main(){

    char str[TAM_STR];
    int vetor[TAM_COORD][2];

    printf("Informe as coordenadas: ");
    scanf(" %[^\n]", str);
    printf("\n");

    int n = procurando(str, vetor);

    if (n == 0) {
        printf("Nenhuma coordenada válida encontrada.\n");
        return 1;
    }

    printf(">> Coordenadas na sequencia original: ");
    imprimindo(vetor, n);

    ordenando(vetor, n);

    printf(">> coordenadas na sequencia ordenado: ");
    imprimindo(vetor, n);

    float distance = distancia(vetor, n);
    printf(">> Distance: %.2f\n", distance);

    float shortcut = distancia_extremos(vetor, n);
    printf(">> shortcut: %.2f\n", shortcut);

    return 0;
}
