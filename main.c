#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "logic.c"

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1800
#define MAX_LIFE 20
#define MAX_ATTACK 20

int main(int argc, char *argv[]){
    srand (time(NULL));

    int difficulty, matrixSize;
    struct Matrix* matrix;

    // Asks for the matrix size
    printf("Seleccione la dificultad:\n1-Facil\n2-Medio\n3-Dificil\n");
    printf("Dificultad: ");
    scanf("%d", &difficulty);
    printf("--------------------------\n\n");

    switch (difficulty){
        case 1:
            matrixSize = 10;
            matrix = createMatrix(matrixSize);
            break;
        case 2:
            matrixSize = 20;
            matrix = createMatrix(matrixSize);
            break;
        case 3:
            matrixSize = 30;
            matrix = createMatrix(matrixSize);
            break;
        default:
            break;
    }


    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    
    SDL_Window* win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
 
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
 
    // creates heroe texture
    SDL_Surface* surface = IMG_Load("Images/heroe.png");
    SDL_Texture* heroe = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates monster texture
    surface = IMG_Load("Images/monster.png");
    SDL_Texture* monster = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates room texture
    surface = IMG_Load("Images/room.png");
    SDL_Texture* roomTexture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates trap dialog texture
    surface = IMG_Load("Images/trapDialog.jpg");
    SDL_Texture* trapDialog = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates treasure dialog texture
    surface = IMG_Load("Images/treasureDialog.jpg");
    SDL_Texture* treasureDialog = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates doorUp texture
    surface = IMG_Load("Images/doorUp.png");
    SDL_Texture* doorUp = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates doorDown texture
    surface = IMG_Load("Images/doorDown.png");
    SDL_Texture* doorDown = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates doorLeft texture
    surface = IMG_Load("Images/doorLeft.png");
    SDL_Texture* doorLeft = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

     // creates doorRight texture
    surface = IMG_Load("Images/doorRight.png");
    SDL_Texture* doorRight = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    //
     // creates signUp texture
    surface = IMG_Load("Images/signUp.png");
    SDL_Texture* signUp = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates signDown texture
    surface = IMG_Load("Images/signDown.png");
    SDL_Texture* signDown = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates signLeft texture
    surface = IMG_Load("Images/signLeft.png");
    SDL_Texture* signLeft = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

     // creates signRight texture
    surface = IMG_Load("Images/signRight.png");
    SDL_Texture* signRight = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);


    // creates openedTreasure texture
    surface = IMG_Load("Images/openedTreasure.png");
    SDL_Texture* openedTreasure = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates closedTreasure texture
    surface = IMG_Load("Images/closedTreasure.png");
    SDL_Texture* closedTreasure = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates closedTrap texture
    surface = IMG_Load("Images/closedTreasure.png");
    SDL_Texture* closedTrap = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
 
    // creates hero attack texture
    surface = IMG_Load("Images/pow.png");
    SDL_Texture* powAttack = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates hero damaged texture
    surface = IMG_Load("Images/ouch.png");
    SDL_Texture* ouchDamage = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates heart texture
    surface = IMG_Load("Images/heart.png");
    SDL_Texture* heart = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates sword texture
    surface = IMG_Load("Images/sword.png");
    SDL_Texture* sword = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // Let us control our image position
    SDL_Rect heroeRect;
    SDL_Rect monsterRect;
    SDL_Rect trapDialogRect;
    SDL_Rect treasureDialogRect;
    SDL_Rect doorUpRect;
    SDL_Rect doorDownRect;
    SDL_Rect doorLeftRect;
    SDL_Rect doorRightRect;
    SDL_Rect signUpRect;
    SDL_Rect signDownRect;
    SDL_Rect signLeftRect;
    SDL_Rect signRightRect;
    SDL_Rect closedTreasureRect;
    SDL_Rect closedTrapRect;
    SDL_Rect openedTreasureRect;
    SDL_Rect powAttackRect;
    SDL_Rect ouchDamageRect;
    SDL_Rect lives[MAX_LIFE];
    SDL_Rect attacks[MAX_ATTACK];


    // connects our textures with Rects to control position
    SDL_QueryTexture(heroe, NULL, NULL, &heroeRect.w, &heroeRect.h);
    SDL_QueryTexture(monster, NULL, NULL, &monsterRect.w, &monsterRect.h);
    SDL_QueryTexture(trapDialog, NULL, NULL, &trapDialogRect.w, &trapDialogRect.h);
    SDL_QueryTexture(treasureDialog, NULL, NULL, &treasureDialogRect.w, &treasureDialogRect.h);
    SDL_QueryTexture(doorUp, NULL, NULL, &doorUpRect.w, &doorUpRect.h);
    SDL_QueryTexture(doorDown, NULL, NULL, &doorDownRect.w, &doorDownRect.h);
    SDL_QueryTexture(doorRight, NULL, NULL, &doorRightRect.w, &doorRightRect.h);
    SDL_QueryTexture(doorLeft, NULL, NULL, &doorLeftRect.w, &doorLeftRect.h);

     SDL_QueryTexture(signUp, NULL, NULL, &signUpRect.w, &signUpRect.h);
    SDL_QueryTexture(signDown, NULL, NULL, &signDownRect.w, &signDownRect.h);
    SDL_QueryTexture(signRight, NULL, NULL, &signRightRect.w, &signRightRect.h);
    SDL_QueryTexture(signLeft, NULL, NULL, &signLeftRect.w, &signLeftRect.h);

    SDL_QueryTexture(closedTreasure, NULL, NULL, &closedTreasureRect.w, &closedTreasureRect.h);
    SDL_QueryTexture(closedTrap, NULL, NULL, &closedTrapRect.w, &closedTrapRect.h);
    SDL_QueryTexture(openedTreasure, NULL, NULL, &openedTreasureRect.w, &openedTreasureRect.h);
    SDL_QueryTexture(powAttack, NULL, NULL, &powAttackRect.w, &powAttackRect.h);
    SDL_QueryTexture(ouchDamage, NULL, NULL, &ouchDamageRect.w, &ouchDamageRect.h);

    for(int i = 0; i <MAX_LIFE; i++){
        SDL_QueryTexture(heart, NULL, NULL, &lives[i].w, &lives[i].h);
    }

    for(int i = 0; i <MAX_ATTACK; i++){
        SDL_QueryTexture(sword, NULL, NULL, &attacks[i].w, &attacks[i].h);
    }

    // adjust height and width of our image box.
    heroeRect.w /= 4;
    heroeRect.h /= 4;

    monsterRect.w /= 3;
    monsterRect.h /= 3;

    trapDialogRect.w /= 1;
    trapDialogRect.h /= 1;

    treasureDialogRect.w /= 1;
    treasureDialogRect.h /= 1;

    doorUpRect.w /= 1;
    doorUpRect.h /= 1;

    doorDownRect.w /= 1;
    doorDownRect.h /= 1;

    doorLeftRect.w /= 1;
    doorLeftRect.h /= 1;

    doorRightRect.w /= 1;
    doorRightRect.h /= 1;

    signUpRect.w /= 1;
    signUpRect.h /= 1;

    signDownRect.w /= 1;
    signDownRect.h /= 1;

    signLeftRect.w /= 1;
    signLeftRect.h /= 1;

    signRightRect.w /= 1;
    signRightRect.h /= 1;

    closedTreasureRect.w /= 12;
    closedTreasureRect.h /= 12;

    closedTrapRect.w /= 12;
    closedTrapRect.h /= 12;

    openedTreasureRect.w /= 4;
    openedTreasureRect.h /= 4;

    powAttackRect.w /= 6;
    powAttackRect.h /= 6;

    ouchDamageRect.w *= 2;
    ouchDamageRect.h *= 2;

    for(int i = 0; i <MAX_LIFE; i++){
        lives[i].w /= 10;
        lives[i].h /= 10;
    }

    for(int i = 0; i <MAX_ATTACK; i++){
        attacks[i].w /= 3;
        attacks[i].h /= 3;
    }


    // sets initial x-position of object
    heroeRect.x = (WINDOW_WIDTH - heroeRect.w) / 2;
    monsterRect.x = ((WINDOW_WIDTH - monsterRect.w) / 2) + 150;
    trapDialogRect.x = (WINDOW_WIDTH - trapDialogRect.w) / 2;
    treasureDialogRect.x = (WINDOW_WIDTH - treasureDialogRect.w) / 2;
    closedTreasureRect.x = (WINDOW_WIDTH - closedTreasureRect.w) - 300;
    closedTrapRect.x = (WINDOW_WIDTH - closedTrapRect.w) - 300;
    openedTreasureRect.x = (WINDOW_WIDTH - openedTreasureRect.w) - 300;
    powAttackRect.x = (WINDOW_WIDTH - powAttackRect.w) / 2;
    ouchDamageRect.x = (WINDOW_WIDTH - ouchDamageRect.w) / 2;    
    for(int i = 0; i < MAX_LIFE; i++){
        lives[i].x = i*75;
    }
    for(int i = 0; i < MAX_ATTACK; i++){
        attacks[i].x = i*75;
    }
    
    // sets initial y-position of object
    heroeRect.y = (WINDOW_HEIGHT - heroeRect.h) / 2;
    monsterRect.y = (WINDOW_HEIGHT - monsterRect.h) / 2;
    trapDialogRect.y = (WINDOW_HEIGHT - trapDialogRect.h) - 50;
    treasureDialogRect.y = (WINDOW_HEIGHT - treasureDialogRect.h) - 50;
    closedTreasureRect.y = (WINDOW_HEIGHT - closedTreasureRect.h) - 200;
    closedTrapRect.y = (WINDOW_HEIGHT - closedTrapRect.h) - 200;
    openedTreasureRect.y = (WINDOW_HEIGHT - openedTreasureRect.h) - 200;
    powAttackRect.y = (WINDOW_HEIGHT - powAttackRect.h) / 2;
    ouchDamageRect.y = (WINDOW_HEIGHT - ouchDamageRect.h) / 2;   
    for(int i = 0; i < MAX_LIFE; i++){
        lives[i].y = 0;
    }
    for(int i = 0; i < MAX_ATTACK; i++){
        attacks[i].y = 70;
    }
    // controls animation loop
    int close = 0;

    // Create Map and Rooms
    Rooms *rooms = malloc(sizeof(struct Rooms)*30);
    createMap(matrix, rooms);


    
    // printMatrix(matrix);
    // for(int i = 0; i < matrixSize; i++){
    // printf("POS:\tx = %d y = %d\n N1:\tx = %d y = %d\n N2:\tx = %d y = %d\n N3:\tx = %d y = %d\n COFFER TYPE:\t %d\n ROOM TYPE:\t%d\n\n", rooms[i] -> pos[0], rooms[i] -> pos[1], rooms[i] -> neighbour1[0], rooms[i] -> neighbour1[1], rooms[i] -> neighbour2[0], rooms[i] -> neighbour2[1], rooms[i] -> neighbour3[0], rooms[i] -> neighbour3[1], rooms[i] -> cofferType, rooms[i] -> type);
    // } 

    Hero heroStruct;
    heroStruct.posX = rooms[0] -> pos[0];
    heroStruct.posY = rooms[0] -> pos[1];
    heroStruct.life = 3; //MAX 3
    heroStruct.attack = 9; //MAX 6

    Hero* apuntHero = &heroStruct;

    Monster* monsterList = malloc(sizeof(struct Monster)*15); 
    createMonster(monsterList,matrixSize,rooms,matrix);
    createMonsterThread(monsterList,rooms,matrixSize,apuntHero);
    
    


    int index = indexCurrentRoom(rooms, matrixSize, heroStruct.posX, heroStruct.posY);
    int n1 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour1[0],rooms[index]->neighbour1[1]);
    int n2 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour2[0],rooms[index]->neighbour2[1]);
    int n3 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour3[0],rooms[index]->neighbour3[1]);
    int roomCofferType = rooms[index] -> cofferType;
    bool isCofferOpened = rooms[index] -> isCofferOpened;
    int idMonster = rooms[index] -> idMonster;
    int heroAttack = 0;
    int heroDamage = 0;
    int trapMessage = 0;
    int treasureMessage = 0;

    int sign = -1;

    while (!close) {
        SDL_Event event;

        if(heroStruct.life == 0){
            printf("GAME OVER\n");
            close = 1;
        }
        if((heroStruct.posX == rooms[matrixSize-1] -> pos[0]) && (heroStruct.posY == rooms[matrixSize-1] -> pos[1])){
            printf("\n\nYOU WON!!\n\n");
            close = 1;
        }
 
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                close = 1;
 
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                
                case SDL_SCANCODE_SPACE:
                    if ((rooms[indexCurrentRoom(rooms, matrixSize, heroStruct.posX , heroStruct.posY)] -> idMonster >= 0) && heroStruct.attack>0 ){
                        monsterList[idMonster]->live --;
                        heroStruct.attack --;
                        heroAttack = 1; //Cantidad de renders pow attack
                    }
                    break;

                case SDL_SCANCODE_W:
                    if(n1 == 2 || n2 == 2 || n3 == 2){
                        int x = heroStruct.posX; 
                        x--;
                        if (rooms[indexCurrentRoom(rooms, matrixSize, x , heroStruct.posY)] -> idMonster <= 0 ){
                              heroStruct.posX--;
                            index = indexCurrentRoom(rooms, matrixSize, heroStruct.posX,heroStruct.posY);
                            n1 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour1[0],rooms[index]->neighbour1[1]);
                            n2 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour2[0],rooms[index]->neighbour2[1]);
                            n3 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour3[0],rooms[index]->neighbour3[1]);
                            roomCofferType = rooms[index] -> cofferType;
                            isCofferOpened = rooms[index] -> isCofferOpened;


                        }else{
                           // printf("Habitacion arriba bloqueada");
                            sign = 2; // arriba 
                           
                        }

                      
                    }
                    break;
                case SDL_SCANCODE_A:
                    if(n1 == 0 || n2 == 0 || n3 == 0 ){
                        int y = heroStruct.posY; 
                        y--;
                        if (rooms[indexCurrentRoom(rooms, matrixSize, heroStruct.posX , y)] -> idMonster <= 0 ){
                            heroStruct.posY--;
                            index = indexCurrentRoom(rooms, matrixSize, heroStruct.posX,heroStruct.posY);
                            n1 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour1[0],rooms[index]->neighbour1[1]);
                            n2 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour2[0],rooms[index]->neighbour2[1]);
                            n3 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour3[0],rooms[index]->neighbour3[1]);
                            roomCofferType = rooms[index] -> cofferType;
                            isCofferOpened = rooms[index] -> isCofferOpened;
                
                        }
                        else{
                            // izquierda
                            sign = 0; // izquierda
                            
                        }
                    }
                    break;
                case SDL_SCANCODE_S:
                    if(n1 == 3 || n2 == 3 || n3 == 3){
                        int x = heroStruct.posX; 
                        x++;
                        if (rooms[indexCurrentRoom(rooms, matrixSize, x , heroStruct.posY)] -> idMonster <= 0 ){
                            heroStruct.posX++;
                            index = indexCurrentRoom(rooms, matrixSize, heroStruct.posX,heroStruct.posY);
                            n1 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour1[0],rooms[index]->neighbour1[1]);
                            n2 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour2[0],rooms[index]->neighbour2[1]);
                            n3 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour3[0],rooms[index]->neighbour3[1]);
                            roomCofferType = rooms[index] -> cofferType;
                            isCofferOpened = rooms[index] -> isCofferOpened;
                    
                        }else{
                              sign = 3; // abajo
                        }
                    }
                    break;
                case SDL_SCANCODE_D:
                    if(n1 == 1 || n2 == 1 || n3 == 1){
                        int y = heroStruct.posY; 
                        y++;
                        if (rooms[indexCurrentRoom(rooms, matrixSize, heroStruct.posX , y)] -> idMonster <= 0 ){
                            heroStruct.posY++;
                            index = indexCurrentRoom(rooms, matrixSize, heroStruct.posX,heroStruct.posY);
                            n1 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour1[0],rooms[index]->neighbour1[1]);
                            n2 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour2[0],rooms[index]->neighbour2[1]);
                            n3 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour3[0],rooms[index]->neighbour3[1]);
                            roomCofferType = rooms[index] -> cofferType;
                            isCofferOpened = rooms[index] -> isCofferOpened;
                        
                        }else{
                             //printf("Habitacion derecha bloqueada");
                                sign = 1; // derecha 
                        }
                    }
                    break;
                case SDL_SCANCODE_E:                    
                    if(rooms[index] -> cofferType == 0){
                        treasureMessage = 10;
                        rooms[index] -> isCofferOpened = true;
                        isCofferOpened = true;
                        if((rand() % 2) == 0){
                            heroStruct.attack++;
                        } else {
                            heroStruct.life++;
                        }
                    }

                    if(rooms[index] -> cofferType == 1){
                        trapMessage = 10;
                        rooms[index] -> isCofferOpened = true;
                        isCofferOpened = true;
                        heroStruct.life--;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        idMonster = rooms[index] -> idMonster;
        //clears the screen
        SDL_SetRenderDrawColor(rend, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(rend);

        // Renderiza el cuarto
        SDL_RenderCopy(rend, roomTexture, NULL, NULL);
           
        // Renderiza las puertas
        if(n1 == 0){
            // Izquierda
             doorLeftRect.x = -15;
             doorLeftRect.y =(WINDOW_HEIGHT -  doorLeftRect.h) / 2;
             SDL_RenderCopy(rend, doorLeft, NULL, &doorLeftRect);
           
        }else if(n1 == 1){
            // Derecha
             doorRightRect.x = (WINDOW_WIDTH -  doorRightRect.w) +15;
             doorRightRect.y =(WINDOW_HEIGHT -   doorRightRect.h) / 2;
             SDL_RenderCopy(rend, doorRight, NULL, & doorRightRect);
            
        }else if(n1 == 2){
            // Arriba
             doorUpRect.x = (WINDOW_WIDTH -  doorUpRect.w) / 2;
             doorUpRect.y =-30;
             SDL_RenderCopy(rend, doorUp, NULL, &doorUpRect);
            
        }else if(n1 == 3){
            // Abajo
             doorDownRect.x = (WINDOW_WIDTH -   doorDownRect.w) / 2;
              doorDownRect.y =(WINDOW_HEIGHT -    doorDownRect.h)+35;
             SDL_RenderCopy(rend, doorDown, NULL, &  doorDownRect);
        
        }
        if(n2 == 0){
            // Izquierda
             doorLeftRect.x = -15;
             doorLeftRect.y =(WINDOW_HEIGHT -  doorLeftRect.h) / 2;
             SDL_RenderCopy(rend, doorLeft, NULL, &doorLeftRect);
           
        }else if(n2 == 1){
            // Derecha
             doorRightRect.x = (WINDOW_WIDTH -  doorRightRect.w) +15;
             doorRightRect.y =(WINDOW_HEIGHT -   doorRightRect.h) / 2;
             SDL_RenderCopy(rend, doorRight, NULL, & doorRightRect);
            
        }else if(n2 == 2){
            // Arriba
             doorUpRect.x = (WINDOW_WIDTH -  doorUpRect.w) / 2;
             doorUpRect.y =-30;
             SDL_RenderCopy(rend, doorUp, NULL, &doorUpRect);
            
        }else if(n2 == 3){
            // Abajo
             doorDownRect.x = (WINDOW_WIDTH -   doorDownRect.w) / 2;
              doorDownRect.y =(WINDOW_HEIGHT -    doorDownRect.h)+35;
             SDL_RenderCopy(rend, doorDown, NULL, &  doorDownRect);
        
        }

         if(n3 == 0){
            // Izquierda
             doorLeftRect.x = -15;
             doorLeftRect.y =(WINDOW_HEIGHT -  doorLeftRect.h) / 2;
             SDL_RenderCopy(rend, doorLeft, NULL, &doorLeftRect);
           
        }else if(n3 == 1){
            // Derecha
             doorRightRect.x = (WINDOW_WIDTH -  doorRightRect.w)+15;
             doorRightRect.y =(WINDOW_HEIGHT -   doorRightRect.h) / 2;
             SDL_RenderCopy(rend, doorRight, NULL, & doorRightRect);
            
        }else if(n3 == 2){
            // Arriba
             doorUpRect.x = (WINDOW_WIDTH -  doorUpRect.w) / 2;
             doorUpRect.y = -30;
             SDL_RenderCopy(rend, doorUp, NULL, &doorUpRect);
            
        }else if(n3 == 3){
            // Abajo
             doorDownRect.x = (WINDOW_WIDTH -   doorDownRect.w) / 2;
              doorDownRect.y =(WINDOW_HEIGHT -    doorDownRect.h)+35;
             SDL_RenderCopy(rend, doorDown, NULL, &  doorDownRect);
        
        }

         if(sign == 0){
            // Izquierda
             signLeftRect.x = -15;
             signLeftRect.y =(WINDOW_HEIGHT -  signLeftRect.h) / 2;
             SDL_RenderCopy(rend, signLeft, NULL, &signLeftRect);
         
           
        }else if(sign == 1){
            // Derecha
             signRightRect.x = (WINDOW_WIDTH -  signRightRect.w) +15;
             signRightRect.y =(WINDOW_HEIGHT -   signRightRect.h) / 2;
             SDL_RenderCopy(rend, signRight, NULL, & signRightRect);
            
            
        }else if(sign == 2){
            // Arriba
             signUpRect.x = (WINDOW_WIDTH -  signUpRect.w) / 2;
             signUpRect.y =-30;
             SDL_RenderCopy(rend, signUp, NULL, &signUpRect);
            
        }else if(sign == 3){
            // Abajo
            signDownRect.x = (WINDOW_WIDTH -   signDownRect.w) / 2;
            signDownRect.y =(WINDOW_HEIGHT -    signDownRect.h)+35;
            SDL_RenderCopy(rend, signDown, NULL, & signDownRect);
        
        }
        sign = -1;

        // Renderiza los tesoros / trampas
        if(roomCofferType == 0 && !isCofferOpened){
            SDL_RenderCopy(rend, closedTreasure, NULL, &closedTreasureRect);
        } else if(roomCofferType == 0 && isCofferOpened){
            SDL_RenderCopy(rend, openedTreasure, NULL, &openedTreasureRect);
        }
        if(roomCofferType == 1 && !isCofferOpened){
            SDL_RenderCopy(rend, closedTreasure, NULL, &closedTreasureRect);
        } else if(roomCofferType == 1 && isCofferOpened){
            SDL_RenderCopy(rend, openedTreasure, NULL, &openedTreasureRect);
        }

        //Renderiza los mensajes de cofres
        if (treasureMessage>0){
            SDL_RenderCopy(rend, treasureDialog, NULL, &treasureDialogRect);
            treasureMessage--;
        }
        if (trapMessage>0){
            SDL_RenderCopy(rend, trapDialog, NULL, &trapDialogRect);
            treasureMessage--;
        }
                                


        // Renderiza los monstruos
        if(idMonster >= 0){
            SDL_RenderCopy(rend, monster, NULL, &monsterRect);
        }

        // Renderiza el heroe
        SDL_RenderCopy(rend, heroe, NULL, &heroeRect);
      
        //Renderiza el ataque del heroe
        if (heroAttack>0){
            SDL_RenderCopy(rend, powAttack, NULL, &powAttackRect);
            heroAttack--;
        }

        //Renderiza el daño al heroe - Falta hacer trigger que setea heroDamage positivo
        if (heroDamage>0){
            SDL_RenderCopy(rend, ouchDamage, NULL, &ouchDamageRect);
            heroDamage--;
        }

        //Rederiza las vidas
        for(int j=0; j<heroStruct.life; j++){
            SDL_RenderCopy(rend, heart, NULL, &lives[j]);
        }

        //Rederiza los puntos de ataque
        for(int j=0; j<heroStruct.attack; j++){
            SDL_RenderCopy(rend, sword, NULL, &attacks[j]);
        }

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);
 
        // calculates to 60 fps
        SDL_Delay(1000 / 60);


    }

    free(matrix -> data);
    free(matrix);
    free(monsterList);
    free(rooms);

    // destroy textures
    SDL_DestroyTexture(heroe);
    SDL_DestroyTexture(roomTexture);
    SDL_DestroyTexture(trapDialog);
    SDL_DestroyTexture(treasureDialog);
    SDL_DestroyTexture(monster);
    SDL_DestroyTexture(doorUp);
    SDL_DestroyTexture(doorDown);
    SDL_DestroyTexture(doorLeft);
    SDL_DestroyTexture(doorRight);
    SDL_DestroyTexture(signUp);
    SDL_DestroyTexture(signDown);
    SDL_DestroyTexture(signLeft);
    SDL_DestroyTexture(signRight);
    SDL_DestroyTexture(openedTreasure);
    SDL_DestroyTexture(closedTreasure);
    SDL_DestroyTexture(closedTrap);
    SDL_DestroyTexture(powAttack);
    SDL_DestroyTexture(ouchDamage);
    SDL_DestroyTexture(heart);
    SDL_DestroyTexture(sword);

    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}