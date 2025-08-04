// Jonathas Gabriel e Uriel Correia

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

Node* createNode(int key, Node* parent) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->parent = parent;
    return node;
}

Node* search(Node* root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

Node* findMin(Node* node) {
    while (node->left)
        node = node->left;
    return node;
}

Node* insert(Node* root, int key, Node* parent) {
    if (!root) return createNode(key, parent);
    if (key == root->key) return root; // não insere duplicado
    if (key < root->key)
        root->left = insert(root->left, key, root);
    else
        root->right = insert(root->right, key, root);
    return root;
}

Node* delete(Node* root, int key) {
    if (!root) return NULL;
    if (key < root->key)
        root->left = delete(root->left, key);
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = delete(root->right, temp->key);
    }
    return root;
}

int nodeHeight(Node* node) {
    int height = 0;
    while (node->parent) {
        node = node->parent;
        height++;
    }
    return height;
}

void inOrderPrint(Node* root, FILE* fp_out) {
    if (!root) return;
    inOrderPrint(root->left, fp_out);
    fprintf(fp_out, "%d (%d) ", root->key, nodeHeight(root));
    inOrderPrint(root->right, fp_out);
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void processLine(FILE* fp_out, char* line) {
    Node* root = NULL;

    char* token = strtok(line, " \n");
    while (token != NULL) {
        if (token[0] == 'a' || token[0] == 'r') {
            char op = token[0];
            token = strtok(NULL, " \n");
            if (!token) break;
            int num = atoi(token);

            if (op == 'a') {
                if (!search(root, num)) {
                    root = insert(root, num, NULL);
                }
            } else if (op == 'r') {
                if (search(root, num)) {
                    root = delete(root, num);
                } else {
                    root = insert(root, num, NULL);
                }
            }
        }
        token = strtok(NULL, " \n");
    }

    inOrderPrint(root, fp_out);
    fprintf(fp_out, "\n");
    freeTree(root);
}

int main() {
    FILE* fp_in = fopen("L2Q3.in", "r");
    FILE* fp_out = fopen("L2Q3.out", "w");

    if (!fp_in || !fp_out) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp_in)) {
        processLine(fp_out, line);
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}