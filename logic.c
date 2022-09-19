#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct Rooms{
    int pos[2];
    int neighbour1[2];
    int neighbour2[2];
    int neighbour3[2];

    // 0 = tesoro, 1 = trampa, 2 = nada
    int cofferType;

    // 0 = spawn, 1 = normal, 2 = finish
    int type;
}Rooms[30];

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
    return matrix;
}

int getNeighboursQuantity(Matrix* m, int i, int j){
    int neighbours = 0;
    if(m -> data[(i-1)*(m->size) + j] == 1){
        neighbours++;
    }
    if(m -> data[(i+1)*(m->size) + j] == 1){
        neighbours++;
    }
    if(m -> data[i*(m->size) + (j-1)] == 1){
        neighbours++;
    }
    if(m -> data[i*(m->size) + (j+1)] == 1){
        neighbours++;
    }
    return neighbours;
}

Matrix* blockNextNeighbour(Matrix* m, int i, int j){
    if(m -> data[(i-1)*(m->size) + j] == 0){
        m -> data[(i-1)*(m->size) + j] = 2;
    }
    if(m -> data[(i+1)*(m->size) + j] == 0){
        m -> data[(i+1)*(m->size) + j] = 2;
    }
    if(m -> data[i*(m->size) + (j-1)] == 0){
        m -> data[i*(m->size) + (j-1)] = 2;
    }
    if(m -> data[i*(m->size) + (j+1)] == 0){
        m -> data[i*(m->size) + (j+1)] = 2;
    }
    return m;
}

int getCofferType(){
    int p = rand() % 10;
    if(p <= 3){
        return 0;
    } else if(p > 3 && p <= 7){
        return 1;
    } else{
        return 2;
    }
}

void setNeighbours(Matrix* m, Rooms *rooms){
    int i, j, z;
    for(int r = 0; r < m -> size; r++) {
        rooms[r] -> neighbour1[0] = -1;
        rooms[r] -> neighbour1[1] = -1;
        rooms[r] -> neighbour2[0] = -1;
        rooms[r] -> neighbour2[1] = -1;
        rooms[r] -> neighbour3[0] = -1;
        rooms[r] -> neighbour3[1] = -1;

        i = rooms[r] -> pos[0];
        j = rooms[r] -> pos[1];
        z = 0;
        while(z < getNeighboursQuantity(m, i, j)){
            if(m -> data[(i-1)*(m->size) + j] == 1){
                if(z == 2){
                    rooms[r] -> neighbour3[0] = i-1;
                    rooms[r] -> neighbour3[1] = j;
                    z++;
                }
                if(z == 1){
                    rooms[r] -> neighbour2[0] = i-1;
                    rooms[r] -> neighbour2[1] = j;
                    z++;
                }
                if(z == 0){
                    rooms[r] -> neighbour1[0] = i-1;
                    rooms[r] -> neighbour1[1] = j;
                    z++;
                }
            }
            if(m -> data[(i+1)*(m->size) + j] == 1){
                if(z == 2){
                    rooms[r] -> neighbour3[0] = i+1;
                    rooms[r] -> neighbour3[1] = j;
                    z++;
                }
                if(z == 1){
                    rooms[r] -> neighbour2[0] = i+1;
                    rooms[r] -> neighbour2[1] = j;
                    z++;
                }
                if(z == 0){
                    rooms[r] -> neighbour1[0] = i+1;
                    rooms[r] -> neighbour1[1] = j;
                    z++;
                }
            }
            if(m -> data[i*(m->size) + (j-1)] == 1){
                if(z == 2){
                    rooms[r] -> neighbour3[0] = i;
                    rooms[r] -> neighbour3[1] = j-1;
                    z++;
                }
                if(z == 1){
                    rooms[r] -> neighbour2[0] = i;
                    rooms[r] -> neighbour2[1] = j-1;
                    z++;
                }
                if(z == 0){
                    rooms[r] -> neighbour1[0] = i;
                    rooms[r] -> neighbour1[1] = j-1;
                    z++;
                }
            }
            if(m -> data[i*(m->size) + (j+1)] == 1){
                if(z == 2){
                    rooms[r] -> neighbour3[0] = i;
                    rooms[r] -> neighbour3[1] = j+1;
                    z++;
                }
                if(z == 1){
                    rooms[r] -> neighbour2[0] = i;
                    rooms[r] -> neighbour2[1] = j+1;
                    z++;
                }
                if(z == 0){
                    rooms[r] -> neighbour1[0] = i;
                    rooms[r] -> neighbour1[1] = j+1;
                    z++;
                }
            }
        }
    }
}

Matrix* createMap(Matrix* m, Rooms *rooms){
    int quantity, tempI, tempJ;
    
    int remainingRooms = m -> size;
    int i = rand() % m -> size;
    int j = rand() % m -> size;
    tempI = i;
    tempJ = j;
    m -> data[i*(m->size) + j] = 1;

    rooms[m -> size - remainingRooms] -> pos[0] = tempI;
    rooms[m -> size - remainingRooms] -> pos[1] = tempJ;
    rooms[m -> size - remainingRooms] -> cofferType = 0;
    rooms[m -> size - remainingRooms] -> type = 0;
    
    remainingRooms--;
    while(remainingRooms > 0){
        // Genera un random entre 1 y 3 (numero de cuartos con los que va a limitar)
        quantity = (rand() % (3 - 1 + 1)) + 1;
        for(int z = 0; z < quantity; z++){
            // 0 = Arriba, 1 = Abajo, 2 = Izquierda, 3 = Derecha
            switch(rand() % 4){
                case 0:
                    if(i-1 >= 0){
                        if((m -> data[(i-1)*(m->size) + j] == 0) && (getNeighboursQuantity(m,i,j)<3)){
                            m -> data[(i-1)*(m->size) + j] = 1;
                            tempI = i-1;
                            tempJ = j;

                            rooms[m -> size - remainingRooms] -> pos[0] = tempI;
                            rooms[m -> size - remainingRooms] -> pos[1] = tempJ;
                            rooms[m -> size - remainingRooms] -> cofferType = getCofferType();
                            if(remainingRooms == 1){
                                rooms[m -> size - remainingRooms] -> type = 2;
                            } else{
                                rooms[m -> size - remainingRooms] -> type = 1;
                            }

                            remainingRooms--;
                        }
                    }
                    break;
                case 1:
                    if((i+1 < m -> size) && (getNeighboursQuantity(m,i,j)<3)){
                        if(m -> data[(i+1)*(m->size) + j] == 0){
                            m -> data[(i+1)*(m->size) + j] = 1;
                            tempI = i+1;
                            tempJ = j;

                            rooms[m -> size - remainingRooms] -> pos[0] = tempI;
                            rooms[m -> size - remainingRooms] -> pos[1] = tempJ;
                            rooms[m -> size - remainingRooms] -> cofferType = getCofferType();
                            if(remainingRooms == 1){
                                rooms[m -> size - remainingRooms] -> type = 2;
                            } else{
                                rooms[m -> size - remainingRooms] -> type = 1;
                            }

                            remainingRooms--;
                        }
                    }
                    break;
                case 2:
                    if(j-1 >= 0){
                        if((m -> data[i*(m->size) + (j-1)] == 0) && (getNeighboursQuantity(m,i,j)<3)){
                            m -> data[i*(m->size) + (j-1)] = 1;
                            tempI = i;
                            tempJ = j-1;

                            rooms[m -> size - remainingRooms] -> pos[0] = tempI;
                            rooms[m -> size - remainingRooms] -> pos[1] = tempJ;
                            rooms[m -> size - remainingRooms] -> cofferType = getCofferType();
                            if(remainingRooms == 1){
                                rooms[m -> size - remainingRooms] -> type = 2;
                            } else{
                                rooms[m -> size - remainingRooms] -> type = 1;
                            }

                            remainingRooms--;
                        }
                    }
                    break;
                case 3:
                    if(j+1 < m -> size){
                        if((m -> data[i*(m->size) + (j+1)] == 0) && (getNeighboursQuantity(m,i,j)<3)){
                            m -> data[i*(m->size) + (j+1)] = 1;
                            tempI = i;
                            tempJ = j+1;

                            rooms[m -> size - remainingRooms] -> pos[0] = tempI;
                            rooms[m -> size - remainingRooms] -> pos[1] = tempJ;
                            rooms[m -> size - remainingRooms] -> cofferType = getCofferType();
                            if(remainingRooms == 1){
                                rooms[m -> size - remainingRooms] -> type = 2;
                            } else{
                                rooms[m -> size - remainingRooms] -> type = 1;
                            }
                            
                            remainingRooms--;
                        }
                    }
                    break;
            }
            if(getNeighboursQuantity(m, i, j) == 3){
                m = blockNextNeighbour(m, i, j);
            }
        }
        i = tempI;
        j = tempJ;
    }
    setNeighbours(m, rooms);

    return m;
}