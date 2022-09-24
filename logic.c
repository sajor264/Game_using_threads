#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>

pthread_mutex_t lock;

typedef struct Rooms{
    int pos[2];
    int neighbour1[2];
    int neighbour2[2];
    int neighbour3[2];
    bool isCofferOpened;
    int idMonster;

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

typedef struct Monster{   
    int id;
    int x;
    int y;
    int live;
}Monster[15];

typedef struct MonsterAd{
    int pos;
    Monster* Monster;
    Rooms* Roons;
    int mSize;
    Hero* hero;
}MonsterAd[15];


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
    rooms[(m -> size) - remainingRooms] -> idMonster = -1;
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
    rooms[0] -> isCofferOpened = false;
    rooms[0] -> idMonster = -1;

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


bool itsOk(int i , int ri, int rj, Rooms *rooms, Matrix *m){
    for(int i = 0; i < m->size ; i++){
            if (rooms[i]->idMonster == -1 && rooms[i]->type == 1 && rooms[i]->pos[0] == ri && rooms[i]->pos[1] == rj)
            {
                rooms[i]->idMonster = i;
                return true;
            }
            
        }
    return false;
}
// En parametros hay que poner los cuartos 
void createMonster(Monster* monsterList, int mSize, Rooms *rooms, Matrix *m){

        for(int i = 0; i < mSize/2 ; i++){
            bool x = true;
            while (x)
            {
            int ri = rand() % m -> size;
            int rj = rand() % m -> size;
            if (itsOk(i, ri,rj,rooms,m))
            {
                monsterList[i]->id = i;
                monsterList[i]->live = 3;
                monsterList[i]->x = ri;
                monsterList[i]->y = rj;
                x = false;
            }
            

            }
            
        }
}

void imprimirMos(Monster* mos, Matrix *m){
    for(int i = 0; i < (m->size)/2 ; i++){
        printf("%d\t", mos[i]->id);
        printf("%d\t",  mos[i]->x);
        printf("%d\t", mos[i]->y);
        printf("\n");
     }
 }


bool auxItsRoomFree(Monster* monster, Rooms *rooms, int id, int mSize, int x , int y){
    for(int i = 0; i < mSize ; i++){
        if(rooms[i]->pos[0] == x && rooms[i]->pos[1] == y){
            pthread_mutex_lock(&lock);
            if (rooms[i]->idMonster == -1 && rooms[i]->type != 0 && rooms[i]->type != 2 )
            {    
               rooms[i]->idMonster = id;
               pthread_mutex_unlock(&lock);
               return true;
            }else{
            pthread_mutex_unlock(&lock);
            }
            
        }
    }
    return false;

}



bool itsRoomFree(Monster* monster, Rooms *rooms, int id, int posRoom, int mSize){
    //printf("%d\t", id,"\n");
    //printf("%d\t", posRoom);
    //printf("%d\t", mSize);
    //printf("\n");
    for(int i = 0; i < mSize ; i++){

        if (rooms[i]->pos[0] == monster[id]->x && rooms[i]->pos[1] == monster[id]->y)
           {
            if (posRoom == 1)
                {
                    if (auxItsRoomFree(monster,rooms,id,mSize,rooms[i]->neighbour1[0],rooms[i]->neighbour1[1]))
                    {
                        monster[id]->x = rooms[i]->neighbour1[0];
                        monster[id]->y = rooms[i]->neighbour1[1];
                        //pthread_mutex_lock(&lock);
                        rooms[i]->idMonster = -1;
                        //pthread_mutex_unlock(&lock);
                        return true;
                    }
            
                }else{
                    if (posRoom == 2)
                    {
                        if (auxItsRoomFree(monster,rooms,id,mSize,rooms[i]->neighbour2[0],rooms[i]->neighbour2[1]))
                        {
                            monster[id]->x = rooms[i]->neighbour2[0];
                            monster[id]->y = rooms[i]->neighbour2[1];
                            //pthread_mutex_lock(&lock);
                            rooms[i]->idMonster = -1;
                            //pthread_mutex_unlock(&lock);
                            return true;
                        }
                    }else{
                        if (posRoom == 3)
                        {
                           if (auxItsRoomFree(monster,rooms,id,mSize,rooms[i]->neighbour3[0],rooms[i]->neighbour3[1]))
                            {
                            monster[id]->x = rooms[i]->neighbour3[0];
                            monster[id]->y = rooms[i]->neighbour3[1];
                            //pthread_mutex_lock(&lock);
                            rooms[i]->idMonster = -1;
                            //pthread_mutex_unlock(&lock);
                            return true;
                            }
                        }
                        
                    }
                    
                }
           }
           
        

    }
    return false;

}


void deleteMonster(Monster* monster, Rooms *rooms, int id, int mSize, int x , int y){
    for(int i = 0; i < mSize ; i++){ 
        if(rooms[i]->pos[0] == x && rooms[i]->pos[1] == y){ 
            rooms[i]->idMonster =-1;
        }
    }
}


void* monsterAdmin(void * ad){
    struct MonsterAd* datos = (struct MonsterAd*) ad;
    printf("%d\n", datos->pos);

    while (true)
    {   
        if (datos->Monster[datos->pos]->live == 0)
        {   

            break;
        }
        
        //aqui vemos si esta el heroe
        if(datos->hero->posX == datos->Monster[datos->pos]->x && datos->hero->posY == datos->Monster[datos->pos]->y){
            datos->hero->life = datos->hero->life - 1;
        //aqui validamos si se puede mover al cuarto del vecino y si hay otro mounstro en la habitacion, ver que no sea el cuarto inicial o final
        }else
        {
            if (itsRoomFree(datos->Monster,datos->Roons,datos->pos,1,datos->mSize))
            {   
                printf("Monster\t");
                printf("%d\n", datos->Monster[datos->pos]->id);
                printf("%d\n", datos->Monster[datos->pos]->x);
                printf("%d\n", datos->Monster[datos->pos]->y);
                printf("Entro a la primera avitacion\n");
                printf("\n");
            }else{
                if (itsRoomFree(datos->Monster,datos->Roons,datos->pos,2,datos->mSize))
                {   
                    printf("Monster\t");
                    printf("%d\n", datos->Monster[datos->pos]->id);
                    printf("%d\n", datos->Monster[datos->pos]->x);
                    printf("%d\n", datos->Monster[datos->pos]->y);
                    printf("Entro a la segunda avitacion\n");
                    printf("\n");
                }else{
                    if (itsRoomFree(datos->Monster,datos->Roons,datos->pos,3,datos->mSize))
                    {
                    printf("Monster\t");
                    printf("%d\n", datos->Monster[datos->pos]->id);
                    printf("%d\n", datos->Monster[datos->pos]->x);
                    printf("%d\n", datos->Monster[datos->pos]->y);
                    printf("Entro a la tercera avitacion\n");
                    printf("\n");
                    }
                }
            }
            
        }
        
        
        sleep(1);
        /* code */
    }
    deleteMonster(datos->Monster, datos->Roons,datos->pos,datos->mSize,datos->Monster[datos->pos]->x,datos->Monster[datos->pos]->y);
    pthread_exit(0);
    return 0;
}

void createMonsterThread(Monster* monster, Rooms *rooms, int mSize, Hero* heroApunt){
    pthread_mutex_init(&lock, NULL);
    MonsterAd* tempMoster = malloc(sizeof(struct MonsterAd));
    pthread_t monsterThread[mSize/2];
    for(int i = 0; i < mSize/2 ; i++){
        tempMoster[i] -> pos = i;
        tempMoster[i] -> Monster = monster;
        tempMoster[i] -> Roons = rooms;
        tempMoster[i] -> mSize = mSize;
        tempMoster[i] -> hero  = heroApunt;
        pthread_create(&monsterThread[i], NULL, monsterAdmin, (void *) &tempMoster[i]);
        
    }
 }

