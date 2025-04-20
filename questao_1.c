#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void ordenando(int (*vec)[2], int n){

    int interm_1, interm_2;

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(vec[i][0] > vec[j][0] ||
              (vec[i][0] == vec[j][0] && 
               vec[i][1] > vec[j][1])){

                interm_1 = vec[i][0];
                interm_2 = vec[i][1];

                vec[i][0] = vec[j][0];
                vec[i][1] = vec[j][1];

                vec[j][0] = interm_1;
                vec[j][1] = interm_2;
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

    float soma_distance = 0.0;

    for(int i = 0; i < n - 1; i++){

        int dx = vec[i + 1][0] - vec[i][0]; 
        int dy = vec[i + 1][1] - vec[i][1];
        
        soma_distance += sqrt(dx * dx + dy * dy);

    }

    return soma_distance;
}

float distancia_extremos(int (*vec)[2], int n){

    float shortcut = 0;

    int dx = vec[n - 1][0] - vec[0][0];
    int dy = vec[n - 1][1] - vec[0][1];

    return sqrt(dx * dx + dy * dy);
}

int main(){

    int n;
    printf("Informe a quantidade coordenadas: ");
    scanf("%d", &n);
    printf("\n");

    int (*vetor)[2] = malloc (n * sizeof(int[2]));

    if( vetor == NULL){
        printf("Erro: Sem memória!\n");
        return 1;
    }
    
    for(int i = 0; i < n; i++){
        printf("Informe a coordenada %d de x: ", i + 1);
        scanf("%d", &vetor[i][0]);
        printf("Informe a coordenada %d de y: ", i + 1);
        scanf("%d", &vetor[i][1]);
    }

    printf("\n");

    printf(">> Coordenadas na sequencia original: ");
    imprimindo(vetor, n);

    ordenando(vetor, n);

    printf(">> coordenadas na sequencia ordenado: ");
    imprimindo(vetor, n);

    float distance = distancia(vetor, n);
    printf(">> Distance: %.2f\n", distance);

    float shortcut = distancia_extremos(vetor, n);
    printf(">> shortcut: %.2f\n", shortcut);

    free(vetor);

    return 0;
}
