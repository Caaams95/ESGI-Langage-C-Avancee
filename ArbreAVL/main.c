//
// Created by admin on 08/06/2023.
//
#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node* leftChild;
    struct Node* rightChild;
    int value;
    int height;
};

// Fonction utilitaire pour calculer la hauteur d'un nœud
int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Fonction utilitaire pour trouver le maximum de deux entiers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fonction pour effectuer une rotation simple à gauche
struct Node* rotateLeft(struct Node* node) {
    struct Node* newRoot = node->rightChild;
    struct Node* subtree = newRoot->leftChild;

    newRoot->leftChild = node;
    node->rightChild = subtree;

    node->height = max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
    newRoot->height = max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild)) + 1;

    return newRoot;
}

// Fonction pour effectuer une rotation simple à droite
struct Node* rotateRight(struct Node* node) {
    struct Node* newRoot = node->leftChild;
    struct Node* subtree = newRoot->rightChild;

    newRoot->rightChild = node;
    node->leftChild = subtree;

    node->height = max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
    newRoot->height = max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild)) + 1;

    return newRoot;
}

// Fonction pour insérer un nœud dans l'AVL
struct Node* insert(struct Node* node, int value) {
    if (node == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
        newNode->value = value;
        newNode->height = 1;
        return newNode;
    }

    if (value < node->value)
        node->leftChild = insert(node->leftChild, value);
    else if (value > node->value)
        node->rightChild = insert(node->rightChild, value);
    else
        return node; // La valeur existe déjà, donc rien à faire

    node->height = max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;

    // Vérification et rééquilibrage de l'arbre
    int balance = getHeight(node->leftChild) - getHeight(node->rightChild);

    // Cas de rotation à gauche
    if (balance > 1 && value < node->leftChild->value)
        return rotateRight(node);

    // Cas de rotation à droite
    if (balance < -1 && value > node->rightChild->value)
        return rotateLeft(node);

    // Cas de rotation gauche-droite
    if (balance > 1 && value > node->leftChild->value) {
        node->leftChild = rotateLeft(node->leftChild);
        return rotateRight(node);
    }

    // Cas de rotation droite-gauche
    if (balance < -1 && value < node->rightChild->value) {
        node->rightChild = rotateRight(node->rightChild);
        return rotateLeft(node);
    }

    return node;
}

// Fonction pour trouver le nœud avec la plus petite valeur (prédécesseur) dans l'arbre
struct Node* findMinValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->leftChild != NULL)
        current = current->leftChild;
    return current;
}

// Fonction pour supprimer un nœud de l'AVL
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL)
        return root;

    if (value < root->value)
        root->leftChild = deleteNode(root->leftChild, value);
    else if (value > root->value)
        root->rightChild = deleteNode(root->rightChild, value);
    else {
        // Nœud trouvé, effectuer la suppression

        // Cas de nœud avec un seul enfant ou sans enfant
        if (root->leftChild == NULL) {
            struct Node* temp = root->rightChild;
            free(root);
            return temp;
        }
        else if (root->rightChild == NULL) {
            struct Node* temp = root->leftChild;
            free(root);
            return temp;
        }

        // Cas de nœud avec deux enfants, trouver le prédécesseur et le remplacer
        struct Node* minValueNode = findMinValueNode(root->rightChild);
        root->value = minValueNode->value;
        root->rightChild = deleteNode(root->rightChild, minValueNode->value);
    }

    root->height = max(getHeight(root->leftChild), getHeight(root->rightChild)) + 1;

    // Vérification et rééquilibrage de l'arbre
    int balance = getHeight(root->leftChild) - getHeight(root->rightChild);

    // Cas de rotation à gauche
    if (balance > 1 && getHeight(root->leftChild->leftChild) >= getHeight(root->leftChild->rightChild))
        return rotateRight(root);

    // Cas de rotation à droite
    if (balance < -1 && getHeight(root->rightChild->rightChild) >= getHeight(root->rightChild->leftChild))
        return rotateLeft(root);

    // Cas de rotation gauche-droite
    if (balance > 1 && getHeight(root->leftChild->leftChild) < getHeight(root->leftChild->rightChild)) {
        root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }

    // Cas de rotation droite-gauche
    if (balance < -1 && getHeight(root->rightChild->rightChild) < getHeight(root->rightChild->leftChild)) {
        root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }

    return root;
}


// Fonction pour afficher l'arbre AVL (parcours infixe)
void printAVL(struct Node* node) {
    if (node == NULL)
        return;

    printAVL(node->leftChild);
    printf("%d ", node->value);
    printAVL(node->rightChild);
}


int main() {
    struct Node* root = NULL;

    // Insertion de quelques valeurs pour tester
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);

    printf("Arbre AVL avant suppression : ");
    printAVL(root);
    printf("\n");

    // Suppression d'une valeur
    int valueToDelete = 30;
    root = deleteNode(root, valueToDelete);

    printf("Arbre AVL apres suppression de la valeur %d : ", valueToDelete);
    printAVL(root);
    printf("\n");

    return 0;
}
