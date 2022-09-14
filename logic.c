#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct Room{
    int pos[2];
    int neighbour1[2];
    int neighbour2[2];
    int neighbour3[2];
    int hasMonster;
}Room;

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

Matrix* createMap(Matrix* m){
    srand (time(NULL));
    int quantity, tempI, tempJ;
    
    int remainingRooms = m -> size;
    int i = rand() % m -> size;
    int j = rand() % m -> size;
    m -> data[i*(m->size) + j] = 1;
    remainingRooms--;
    while(remainingRooms > 0){
        // Genera un random entre 1 y 3 (numero de cuartos con los que va a limitar)
        quantity = (rand() % (3 - 1 + 1)) + 1;
        for(int z = 0; z < quantity; z++){
            // 0 = Arriba, 1 = Abajo, 2 = Izquierda, 3 = Derecha
            switch(rand() % 4){
                case 0:
                    if(i-1 >= 0){
                        if(m -> data[(i-1)*(m->size) + j] == 0){
                            m -> data[(i-1)*(m->size) + j] = 1;
                            tempI = i-1;
                            tempJ = j;
                            remainingRooms--;
                        }
                    }
                    break;
                case 1:
                    if(i+1 <= m -> size){
                        if(m -> data[(i+1)*(m->size) + j] == 0){
                            m -> data[(i+1)*(m->size) + j] = 1;
                            tempI = i+1;
                            tempJ = j;
                            remainingRooms--;
                        }
                    }
                    break;
                case 2:
                    if(j-1 >= 0){
                        if(m -> data[i*(m->size) + (j-1)] == 0){
                            m -> data[i*(m->size) + (j-1)] = 1;
                            tempI = i;
                            tempJ = j-1;
                            remainingRooms--;
                        }
                    }
                    break;
                case 3:
                    if(j+1 <= m -> size){
                        if(m -> data[i*(m->size) + (j+1)] == 0){
                            m -> data[i*(m->size) + (j+1)] = 1;
                            tempI = i;
                            tempJ = j+1;
                            remainingRooms--;
                        }
                    }
                    break;
            }
        }
        i = tempI;
        j = tempJ;
    }
    return m;
}