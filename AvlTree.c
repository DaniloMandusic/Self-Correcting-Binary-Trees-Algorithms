#include <stdio.h>
#include <stdlib.h>

void swap(int** matrix, int i, int j){

    int tmp = matrix[i][j];
    matrix[i][j] = matrix[j][i];
    matrix[j][i] = tmp;

}

void transposeMatrix(int **matrix, int numOfRows,int numOfColumns){

    for (int i = 0; i < numOfRows; ++i) {
        for (int j = i+1; j < numOfColumns; ++j) {

            swap(matrix, i, j);

        }
    }

}

void printMatrix(int ** matrix, int numOfRows, int numOfColumns){

    for (int i = 0; i < numOfRows; ++i) {
        for (int j = 0; j < numOfColumns; ++j) {

            printf("%d ",matrix[i][j]);

        }

        printf("\n");

    }

}

void sortRow(int **matrice,int column, int numOfColumns){

    for (int i = 0; i < numOfColumns; i++) {

        for (int j = i+1; j < numOfColumns; j++) {

            if(matrice[column][j] < matrice[column][i]){

                int temp = matrice[column][j];
                matrice[column][j] = matrice[column][i];
                matrice[column][i] = temp;

            }
        }
    }

}

void sortRows(int **matrix, int numOfColumns){

    for (int i = 0; i < numOfColumns; i++) {

        sortRow(matrix, i, numOfColumns);

    }

};

void sortMatrix(int **matrix, int numOfColumns,int numOfRows){

    sortRows(matrix,numOfColumns);

    transposeMatrix(matrix,numOfColumns,numOfRows);

    sortRows(matrix,numOfColumns);

    transposeMatrix(matrix,numOfColumns,numOfRows);

}

void unsuccessfulSearch(){
    printf("unsuccessful search\n");
}

void successfulSearch(){
    printf("successful search\n");
}

int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;

        printf("%d\n",arr[mid]);

        if (arr[mid] == x)
            successfulSearch();

        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        return binarySearch(arr, mid + 1, r, x);
    }

    return -1;
}

void binSearchMatrix(int** matrix, int numOfColumns, int numOfRows, int key) {

    int bool = 0;

    if (key < matrix[0][0]) unsuccessfulSearch();
    else {


        int dummy;

        for (int i = 0; i < numOfColumns; ++i) {
            dummy = binarySearch(matrix[i], 0, numOfColumns - 1, key);
            if (dummy != -1) break;
        }



    }
}

int* matrixToArray(int** matrix, int numOfRows){

    int k = 0, *array;

    array = malloc(numOfRows*numOfRows*sizeof(int));

    for (int i = 0; i < numOfRows; ++i) {
        for (int j = 0; j < numOfRows; ++j) {

            array[k] = matrix[i][j];
            k++;

        }
    }

    return array;

}

struct Node{

    struct Node* left;
    struct Node* right;
    int height;
    int key;
    int numberOfKeys;
    int balance;

};

void deleteTree(struct Node *root)
{
    if(root != NULL)
    {
        free(root);
        deleteTree(root->left);
        deleteTree(root->right);
    }
}

int getHeight(struct Node *node)
{
    int height;
    if (!node) height = 0;
    else height = node->height;

    return height;
}

int getBalance(struct Node *node)
{
    int balance;
    if (!node)
        balance = 0;
    else balance = getHeight(node->left) - getHeight(node->right);

    return balance;
}

int max(int a, int b)
{
    if(a > b) return a;
    else return b;
}

struct Node *rightRotation(struct Node *x)
{
    struct Node *y = x->left;
    struct Node *tmp = y->right;
    y->right = x;
    x->left = tmp;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    return y;
}

struct Node *leftRotation(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *tmp = y->left;
    y->left = x;
    x->right = tmp;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    return y;
}



void balanceTree(struct Node *root)
{
    if(root != NULL)
    {
        root->balance = getBalance(root);
        balanceTree(root->left);
        balanceTree(root->right);
    }
}

void setHeight(struct Node *root)
{
    if(root != NULL)
    {
        root->height = 1 + max(getHeight(root->left),
                               getHeight(root->right));
        setHeight(root->left);
        setHeight(root->right);
    }
}

struct Node* chooseTypeOfRotation(struct Node* tmp,int key){

    if (tmp->balance > 1 && key < tmp->left->key)
        tmp = rightRotation(tmp);

    if (tmp->balance < -1 && key > tmp->right->key)
        tmp =  leftRotation(tmp);

    if (tmp->balance > 1 && key > tmp->left->key)
    {
        tmp->left =  leftRotation(tmp->left);
        tmp =  rightRotation(tmp);
    }

    if (tmp->balance < -1 && key < tmp->right->key)
    {
        tmp->right = rightRotation(tmp->right);
        tmp = leftRotation(tmp);
    }

    return tmp;

}

struct Node* bst(struct Node* tmp,int key){
    while(tmp) {
        if (key < tmp->key)
            if(tmp->left)
                tmp = tmp->left;
            else {

                tmp->left = (struct Node*)malloc(sizeof(struct Node));
                tmp->left->key   = key;
                tmp->left->left   = NULL;
                tmp->left->right  = NULL;
                tmp->left->height = 1;

                tmp = tmp->left;
                break;

            }
        else {
            if (key > tmp->key) {
                if (tmp->right)
                    tmp = tmp->right;
                else {
                    tmp->right = (struct Node*)malloc(sizeof(struct Node));
                    tmp->right->key   = key;
                    tmp->right->left   = NULL;
                    tmp->right->right  = NULL;
                    tmp->right->height = 1;

                    tmp = tmp->right;
                    break;
                }
            }
        }
    }

    return tmp;
}

struct Node* insert(struct Node* node, int key)
{
    if (node == NULL) { struct Node* node = (struct Node*)
                malloc(sizeof(struct Node));
        node->key   = key;
        node->left   = NULL;
        node->right  = NULL;
        node->height = 1;
        node->numberOfKeys = 1;
        node->balance = 0;
        return(node); }

    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else {
        node->numberOfKeys++;
        return node;
    }


    balanceTree(node);
    setHeight(node);

    if(node->balance == 0) return node;
    else node = chooseTypeOfRotation(node,key);

    return node;

}


void print(struct Node *root, int space)
{
    int count= 10;

    if (root == NULL)
        return;

    space += count;

    print(root->right, space);

    printf("\n");
    for (int i = count; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    print(root->left, space);
}

int main() {

    int counter = 0,n;

    int **matrix,*array;

    struct Node* root = NULL;

    printf("1. Unesi dimenzije za matricu 2.Binarna pretraga matrice 3.Dodaj kljuc u avl stablo 4.Ispisi stablo 5.Obrisi stablo\n");


    while(counter!=-1) {

        scanf("%d",&counter);

        if(counter == 1) {

            scanf("%d",&n);

            matrix = malloc(n * sizeof(int *));

            for (int i = 0; i < n; ++i) {

                matrix[i] = malloc(n * sizeof(int));

            }

            int h = 32;

            for (int k = 0; k < n; ++k) {

                for (int i = 0; i < n; ++i) {

                    matrix[k][i] = rand();

                }

            }



            sortMatrix(matrix,n,n);
            printf("\n");

            printMatrix(matrix, n, n);

        }

        if (counter == 2) {
            int g;
            scanf("%d",&g);

            binSearchMatrix(matrix,n,n,g);
            array = matrixToArray(matrix,n);

            for (int i = 0; i < n*n; ++i) {

                root = insert(root, array[i]);

            }

        }

        if(counter == 3){
            int k;
            scanf("%d",&k);

            root = insert(root,k);

        }

        if(counter == 4){

            print(root,0);

        }

        if(counter == 5){

            deleteTree(root);

        }

    }

       return 0;
}
