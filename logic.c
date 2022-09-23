#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

typedef struct Rooms{
    int pos[2];
    int neighbour1[2];
    int neighbour2[2];
    int neighbour3[2];
    bool isCofferOpened;

    // 0 = tesoro, 1 = trampa, 2 = nada
    int cofferType;

    // 0 = spawn, 1 = normal, 2 = finish
    int type;
}Rooms[30];

typedef struct Matrix{
    int size;
    int* data;
}Matrix;

typedef struct Hero{
    int posX;
    int posY;
    int life;
    int attack;
}Hero;

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
    Matrix* matrix = malloc(sizeof(struct Matrix));
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

int getCofferType(){
    int p = (rand() % 10) + 1;
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

int getRemainingRooms(Matrix *m){
    int quantity = m -> size;
    for(int i = 0; i < (m -> size); i++){
        for(int j = 0; j < (m -> size); j++){
            if(m -> data[i*(m -> size) + j] == 1){
                quantity--;
            }
        }
    }
    return quantity;
}

bool isValidPos(Matrix *m, int i, int j){
    if((getNeighboursQuantity(m, i, j) <= 3) && (i >= 0) && (j >= 0) && (i < (m -> size)) && (j < (m -> size)) && (m -> data[i*(m->size) + j] == 0))
        return true;
    return false;
}

void putRoom(Matrix *m, int i, int j, Rooms *rooms){
    int remainingRooms = getRemainingRooms(m);
    m -> data[i*(m -> size) + j] = 1;
    rooms[(m -> size) - remainingRooms] -> pos[0] = i;
    rooms[(m -> size) - remainingRooms] -> pos[1] = j;
    rooms[(m -> size) - remainingRooms] -> isCofferOpened = false;
    if(remainingRooms == 1){
        rooms[(m -> size) - remainingRooms] -> cofferType = 2;
        rooms[(m -> size) - remainingRooms] -> type = 2;
    } else {
        rooms[(m -> size) - remainingRooms] -> cofferType = getCofferType();
        rooms[(m -> size) - remainingRooms] -> type = 1;
    }
}

void removeRoom(Matrix *m, int i, int j, Rooms *rooms){
    int remainingRooms = getRemainingRooms(m);
    m -> data[i*(m -> size) + j] = 0;
    rooms[(m -> size) - remainingRooms] -> pos[0] = -1;
    rooms[(m -> size) - remainingRooms] -> pos[1] = -1;
    rooms[(m -> size) - remainingRooms] -> cofferType = -1;
    rooms[(m -> size) - remainingRooms] -> type = -1;
}

bool createMapAux(Matrix* m, int i, int j, Rooms *rooms){
    bool result = false;
    if(getRemainingRooms(m) <= 0)
        return true;
    switch (rand() % 4){
        case 0:
            if((isValidPos(m, i-1, j)) && (getNeighboursQuantity(m, i, j) <= 2)){
                putRoom(m, i-1, j, rooms);                
                if(createMapAux(m, i-1, j, rooms)){
                    result = true;
                } else{
                    removeRoom(m, i-1, j, rooms);
                    result = createMapAux(m, i, j, rooms);
                }
            }
            break;
        case 1:
            if((isValidPos(m, i+1, j)) && (getNeighboursQuantity(m, i, j) <= 2)){
                putRoom(m, i+1, j, rooms); 
                if(createMapAux(m, i+1, j, rooms)){
                    result = true;
                } else{
                    removeRoom(m, i+1, j, rooms);
                    result = createMapAux(m, i, j, rooms);
                }
            }
            break;
        case 2:
            if((isValidPos(m, i, j-1)) && (getNeighboursQuantity(m, i, j) <= 2)){
                putRoom(m, i, j-1, rooms); 
                if(createMapAux(m, i, j-1, rooms)){
                    result = true;
                } else{
                    removeRoom(m, i, j-1, rooms);
                    result = createMapAux(m, i, j, rooms);
                }
            }
            break;
        case 3:
            if((isValidPos(m, i, j+1)) && (getNeighboursQuantity(m, i, j) <= 2)){
                putRoom(m, i, j+1, rooms); 
                if(createMapAux(m, i, j+1, rooms)){
                    result = true;
                } else{
                    removeRoom(m, i, j+1, rooms);
                    result = createMapAux(m, i, j, rooms);
                }
            }
            break;
        default:
            break;
    }
    return result;
}

void createMap(Matrix* m, Rooms *rooms){    
    bool isCreated = false;
    int i = rand() % m -> size;
    int j = rand() % m -> size;
    m -> data[i*(m->size) + j] = 1;

    rooms[0] -> pos[0] = i;
    rooms[0] -> pos[1] = j;
    rooms[0] -> cofferType = 2;
    rooms[0] -> type = 0;

    while(!isCreated){
        isCreated = createMapAux(m, i, j, rooms);
    }
    setNeighbours(m, rooms);
}

int indexCurrentRoom(Rooms *rooms, int size, int xPlayer, int yPlayer){
    for(int i = 0; i < size; i++){
        if ((xPlayer == (rooms[i] -> pos[0])) && (yPlayer == (rooms[i] -> pos[1]))){
             return i;
        }
    }
    return -1;
}

 int locateNeighbor(int xRoom ,int yRoom ,int xNeighbor, int yNeighbor){
    if(xNeighbor == -1 || yNeighbor == -1){
        return -1;
    }
    if(xRoom-1 == xNeighbor){
        // UP
        return 2;
    }
    if(xRoom+1 == xNeighbor){
        // DOWN
        return 3;
    }
    if(yRoom-1 == yNeighbor){
        // LEFT
        return 0;
    }
    if(yRoom+1 == yNeighbor){
        // RIGHT
        return 1;
    } else{
        return -1;
    }
 }