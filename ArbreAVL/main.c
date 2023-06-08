#include <stdio.h>
#include <stdlib.h>

//test
typedef struct Node {
    int value;
    struct Node* leftChild;
    struct Node* rightChild;
    int height;
} Node;

int getHeight(Node* node) {
    if (node == NULL)
        return -1;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->height = 0;
    return newNode;
}

void updateHeight(Node* node) {
    if (node == NULL)
        return;
    node->height = 1 + max(getHeight(node->leftChild), getHeight(node->rightChild));
}

Node* rotateRight(Node* node) {
    Node* newRoot = node->leftChild;
    node->leftChild = newRoot->rightChild;
    newRoot->rightChild = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

Node* rotateLeft(Node* node) {
    Node* newRoot = node->rightChild;
    node->rightChild = newRoot->leftChild;
    newRoot->leftChild = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

Node* balance(Node* node) {
    if (node == NULL)
        return node;

    updateHeight(node);

    int balanceFactor = getHeight(node->leftChild) - getHeight(node->rightChild);

    if (balanceFactor > 1) {
        if (getHeight(node->leftChild->leftChild) < getHeight(node->leftChild->rightChild))
            node->leftChild = rotateLeft(node->leftChild);
        return rotateRight(node);
    }
    if (balanceFactor < -1) {
        if (getHeight(node->rightChild->rightChild) < getHeight(node->rightChild->leftChild))
            node->rightChild = rotateRight(node->rightChild);
        return rotateLeft(node);
    }

    return node;
}

Node* insertNode(Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->value)
        root->leftChild = insertNode(root->leftChild, value);
    else if (value > root->value)
        root->rightChild = insertNode(root->rightChild, value);

    return balance(root);
}

Node* getMaxNode(Node* root) {
    if (root == NULL || root->rightChild == NULL)
        return root;
    return getMaxNode(root->rightChild);
}

Node* deleteNode(Node* root, int value) {
    if (root == NULL)
        return root;

    if (value < root->value)
        root->leftChild = deleteNode(root->leftChild, value);
    else if (value > root->value)
        root->rightChild = deleteNode(root->rightChild, value);
    else {
        if (root->leftChild == NULL || root->rightChild == NULL) {
            Node* temp = root->leftChild ? root->leftChild : root->rightChild;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
                free(temp);
            }
        } else {
            Node* maxNode = getMaxNode(root->leftChild);
            root->value = maxNode->value;
            root->leftChild = deleteNode(root->leftChild, maxNode->value);
        }
    }

    return balance(root);
}

void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->leftChild);

        printf("Noeud %d (h%d)", root->value, root->height);

        if (root->leftChild != NULL)
            printf(" | FG: %d", root->leftChild->value);
        if (root->rightChild != NULL)
            printf(" | FD: %d", root->rightChild->value);

        printf("\n");

        inOrderTraversal(root->rightChild);
    }
}


int main() {
    Node* root = NULL;

    // Création de l'arbre AVL avec les valeurs et hauteurs spécifiées
    root = createNode(6);
    root->height = 3;
    root->leftChild = createNode(4);
    root->leftChild->height = 2;
    root->rightChild = createNode(7);
    root->rightChild->height = 1;
    root->leftChild->leftChild = createNode(2);
    root->leftChild->leftChild->height = 1;
    root->leftChild->rightChild = createNode(5);
    root->leftChild->rightChild->height = 0;
    root->rightChild->rightChild = createNode(8);
    root->rightChild->rightChild->height = 0;
    root->leftChild->leftChild->leftChild = createNode(1);
    root->leftChild->leftChild->leftChild->height = 0;
    root->leftChild->leftChild->rightChild = createNode(3);
    root->leftChild->leftChild->rightChild->height = 0;

    printf("Arbre AVL apres insertion:\n");
    inOrderTraversal(root);
    printf("\n");

    int nodeToDelete = 5;
    root = deleteNode(root, nodeToDelete);

    printf("Arbre AVL apres suppression du noeud %d:\n", nodeToDelete);
    inOrderTraversal(root);
    printf("\n");

    return 0;
}
