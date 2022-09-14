#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Matrix{
    int size;
    int* data;
}Matrix;

void printMatrix(Matrix* m) {
    for(int i = 0; i < m->size; i++) {
        for(int j = 0; j < m->size; j++) {
            printf("%d\t", m->data[i*(m->size) + j]);
        }
        printf("\n");
    }
    printf("\n");
}

Matrix* createMatrix(int mSize) {
    struct Matrix* matrix = malloc(sizeof(struct Matrix));
    matrix -> size = mSize;
    matrix -> data = malloc(sizeof(int)*mSize*mSize);
    for(int i = 0; i < mSize; i++) {
        for(int j = 0; j < mSize; j++) {
            matrix -> data[i*mSize + j] =  0;
        }
    }
    struct Matrix *m;
    m = matrix;
    return m;
}