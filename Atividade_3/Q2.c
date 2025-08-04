// Jonathas Gabriel e Uriel Correia

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int key) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int key) {
    if (root == NULL) return createNode(key);
    if (key == root->key) return root; // não insere duplicados
    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return root;
}

int subtreeSum(Node* root) {
    if (!root) return 0;
    return root->key + subtreeSum(root->left) + subtreeSum(root->right);
}

void preorderPrint(Node* root, FILE* fp_out) {
    if (!root) return;
    int left_sum = subtreeSum(root->left);
    int right_sum = subtreeSum(root->right);
    int diff = right_sum - left_sum;
    fprintf(fp_out, "%d (%d) ", root->key, diff);
    preorderPrint(root->left, fp_out);
    preorderPrint(root->right, fp_out);
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void processLine(FILE* fp_out, int values[], int size) {
    Node* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert(root, values[i]);
    }
    preorderPrint(root, fp_out);
    fprintf(fp_out, "\n");
    freeTree(root);
}

int main() {
    FILE* fp_in = fopen("L2Q2.in", "r");
    FILE* fp_out = fopen("L2Q2.out", "w");

    if (!fp_in || !fp_out) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp_in)) {
        int values[100];
        int count = 0;

        char* token = strtok(line, " \n");
        while (token != NULL) {
            values[count++] = atoi(token);
            token = strtok(NULL, " \n");
        }

        if (count > 0)
            processLine(fp_out, values, count);
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}