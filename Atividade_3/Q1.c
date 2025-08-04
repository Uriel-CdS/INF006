// Jonathas Gabriel e Uriel Correia
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 50000

typedef struct TreeNode {
    int key;
    int depth;
    struct TreeNode *left, *right, *parent;
} TreeNode;

TreeNode *createNode(int key, TreeNode* parent) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->depth = 0;
    newNode->left = newNode->right = NULL;
    newNode->parent = parent;
    return newNode;
}

void insertNode(TreeNode **root, int key, int *depthLog, int *logIndex, TreeNode* insertedNodes[], int* nodeIndex) {
    if (*root == NULL) {
        *root = createNode(key, NULL);
        depthLog[(*logIndex)++] = (*root)->depth;
        insertedNodes[(*nodeIndex)++] = *root;
        return;
    }

    TreeNode *current = *root;
    TreeNode *parentNode = NULL;
    while (current != NULL) {
        parentNode = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    TreeNode* newNode = createNode(key, parentNode);
    newNode->depth = parentNode->depth + 1;

    if (key < parentNode->key) {
        parentNode->left = newNode;
    } else {
        parentNode->right = newNode;
    }
    depthLog[(*logIndex)++] = newNode->depth;
    insertedNodes[(*nodeIndex)++] = newNode;
}

void findDeepestNode(TreeNode *node, TreeNode **deepest) {
    if (node == NULL) return;
    if (*deepest == NULL || node->depth > (*deepest)->depth) {
        *deepest = node;
    }
    findDeepestNode(node->left, deepest);
    findDeepestNode(node->right, deepest);
}

void freeTree(TreeNode* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    FILE *inputFile = fopen("L2Q1.in", "r");
    FILE *outputFile = fopen("L2Q1.out", "w");
    if (!inputFile || !outputFile) {
        perror("Error opening files");
        return 1;
    }

    char lineBuffer[MAX_LINE_SIZE];
    int isFirstLine = 1;

    while (fgets(lineBuffer, sizeof(lineBuffer), inputFile)) {
        TreeNode *root = NULL;
        int depthLog[MAX_LINE_SIZE];
        int logIndex = 0;
        TreeNode* insertedNodes[MAX_LINE_SIZE];
        int nodeIndex = 0;

        char *token = strtok(lineBuffer, " \r\n");
        while (token) {
            int value = atoi(token);
            insertNode(&root, value, depthLog, &logIndex, insertedNodes, &nodeIndex);
            token = strtok(NULL, " \r\n");
        }

        if (nodeIndex == 0) {
            continue;
        }

        if (!isFirstLine) {
            fprintf(outputFile, "\n");
        }
        isFirstLine = 0;

        for (int i = 0; i < logIndex; i++) {
            fprintf(outputFile, "%d", depthLog[i]);
            if (i < logIndex - 1) {
                fprintf(outputFile, " ");
            }
        }

        TreeNode *deepestNode = NULL;
        findDeepestNode(root, &deepestNode);
        int maxDepth = deepestNode ? deepestNode->depth : 0;

        TreeNode* maxNode = root;
        TreeNode* parentOfMax = NULL;
        if (root) {
            while(maxNode->right != NULL) {
                parentOfMax = maxNode;
                maxNode = maxNode->right;
            }
        }

        fprintf(outputFile, " max %d alt %d pred ", maxNode->key, maxDepth);
        if (parentOfMax != NULL) {
            fprintf(outputFile, "%d", parentOfMax->key);
        } else {
            fprintf(outputFile, "NaN");
        }

        freeTree(root);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}