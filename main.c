#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "logic.c"

#define WINDOW_SIZE 900

int main(int argc, char *argv[]){
    srand (time(NULL));

    int difficulty, matrixSize;
    struct Matrix* matrix;

    // Asks for the matrix size
    printf("Seleccione la dificultad:\n1-Facil\n2-Medio\n3-Dificil\n");
    scanf("%d", &difficulty);

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

    Rooms *rooms = malloc(sizeof(struct Rooms));
    createMap(matrix, rooms);
    
    // printMatrix(matrix);
    // int counter = 0;
    // for(int i = 0; i < matrixSize; i++) {
    //     for(int j = 0; j < matrixSize; j++) {
    //         if(matrix -> data[i*matrixSize + j] ==  1){
    //             counter++;
    //         }
    //     }
    // }
   // printf("TOTAL: %d\n", counter);
     for(int i = 0; i < matrixSize; i++){
        printf("POS:\tx = %d y = %d\n N1:\tx = %d y = %d\n N2:\tx = %d y = %d\n N3:\tx = %d y = %d\n COFFER TYPE:\t %d\n ROOM TYPE:\t%d\n\n", rooms[i] -> pos[0], rooms[i] -> pos[1], rooms[i] -> neighbour1[0], rooms[i] -> neighbour1[1], rooms[i] -> neighbour2[0], rooms[i] -> neighbour2[1], rooms[i] -> neighbour3[0], rooms[i] -> neighbour3[1], rooms[i] -> cofferType, rooms[i] -> type);
     }
   
    

    

    // return 0;
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE, WINDOW_SIZE, 0);
 
    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    // creates a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
 
    // creates heroe texture
    SDL_Surface* surface = IMG_Load("Images/heroe.png");
    SDL_Texture* heroe = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates background texture
    surface = IMG_Load("Images/background.jpg");
    SDL_Texture* background = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates trap dialog texture
    surface = IMG_Load("Images/trapDialog.jpg");
    SDL_Texture* trapDialog = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates treasure dialog texture
    surface = IMG_Load("Images/treasureDialog.jpg");
    SDL_Texture* treasureDialog = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // creates door1 texture
    surface = IMG_Load("Images/door.png");
    SDL_Texture* door1 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

     // creates door2 texture
    surface = IMG_Load("Images/door.png");
    SDL_Texture* door2 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

      // creates door3 texture
    surface = IMG_Load("Images/door.png");
    SDL_Texture* door3 = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
 
    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect heroeRect;
    SDL_Rect trapDialogRect;
    SDL_Rect treasureDialogRect;
    SDL_Rect door1Rect;
    SDL_Rect door2Rect;
    SDL_Rect door3Rect;
 
    // connects our texture with heroeRect to control position
    SDL_QueryTexture(heroe, NULL, NULL, &heroeRect.w, &heroeRect.h);
    SDL_QueryTexture(trapDialog, NULL, NULL, &trapDialogRect.w, &trapDialogRect.h);
    SDL_QueryTexture(treasureDialog, NULL, NULL, &treasureDialogRect.w, &treasureDialogRect.h);
    SDL_QueryTexture(door1, NULL, NULL, &door1Rect.w, &door1Rect.h);
    SDL_QueryTexture(door2, NULL, NULL, &door2Rect.w, &door2Rect.h);
    SDL_QueryTexture(door3, NULL, NULL, &door3Rect.w, &door3Rect.h);
 
    // adjust height and width of our image box.
    heroeRect.w /= 8;
    heroeRect.h /= 8;

    trapDialogRect.w /= 2;
    trapDialogRect.h /= 2;

    treasureDialogRect.w /= 2;
    treasureDialogRect.h /= 2;

    door1Rect.w /= 8;
    door1Rect.h /= 8;

    door2Rect.w /= 8;
    door2Rect.h /= 8;
 
    door3Rect.w /= 8;
    door3Rect.h /= 8;

    // sets initial x-position of object
    heroeRect.x = (WINDOW_SIZE - heroeRect.w) / 2;
    trapDialogRect.x = (WINDOW_SIZE - trapDialogRect.w) / 2;
    treasureDialogRect.x = (WINDOW_SIZE - treasureDialogRect.w) / 2;
    
    // sets initial y-position of object
    heroeRect.y = (WINDOW_SIZE - heroeRect.h) / 2;
    trapDialogRect.y = (WINDOW_SIZE - trapDialogRect.h) - 50;
    treasureDialogRect.y = (WINDOW_SIZE - treasureDialogRect.h) - 50;
   
 
    // controls animation loop
    int close = 0;
 
    // speed of box
    int speed = 30;

    // animation loop

    int index = indexCurrentRoom(rooms, matrixSize, rooms[0]->pos[0],rooms[0]->pos[1]);

        printf("ROOM:\tx = %d y = %d\n", rooms[index]->pos[0],rooms[index]->pos[1]);
        printf("N1:\tx = %d y = %d\n", rooms[index]->neighbour1[0],rooms[index]->neighbour1[1]);
        printf("N2:\tx = %d y = %d\n", rooms[index]->neighbour2[0],rooms[index]->neighbour2[1]);
        printf("N3:\tx = %d y = %d\n", rooms[index]->neighbour3[0],rooms[index]->neighbour3[1]);

    int n1 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour1[0],rooms[index]->neighbour1[1]);
    int n2 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour2[0],rooms[index]->neighbour2[1]);
    int n3 = locateNeighbor(rooms[index]->pos[0],rooms[index]->pos[1],rooms[index]->neighbour3[0],rooms[index]->neighbour3[1]);


    while (!close) {
        SDL_Event event;
 
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;
 
            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    heroeRect.y -= speed;
                    break;
                case SDL_SCANCODE_A:
                    heroeRect.x -= speed;
                    break;
                case SDL_SCANCODE_S:
                    heroeRect.y += speed;
                    break;
                case SDL_SCANCODE_D:
                    heroeRect.x += speed;
                    break;
                case SDL_SCANCODE_E:
                    SDL_RenderClear(rend);
                    SDL_RenderCopy(rend, background, NULL, NULL);
                    SDL_RenderCopy(rend, heroe, NULL, &heroeRect);
                    //SDL_RenderCopy(rend, treasureDialog, NULL, &treasureDialogRect);
                    SDL_RenderCopy(rend, trapDialog, NULL, &trapDialogRect);
                    SDL_RenderPresent(rend);
                    sleep(3);
                    break;
                default:
                    break;
                }
            }
        }

 
        // right boundary
        if (heroeRect.x + heroeRect.w > WINDOW_SIZE)
            heroeRect.x = WINDOW_SIZE - heroeRect.w;
 
        // left boundary
        if (heroeRect.x < 0)
            heroeRect.x = 0;
 
        // bottom boundary
        if (heroeRect.y + heroeRect.h > WINDOW_SIZE)
            heroeRect.y = WINDOW_SIZE - heroeRect.h;
 
        // upper boundary
        if (heroeRect.y < 0)
            heroeRect.y = 0;
 
         //clears the screen
        
        
         SDL_RenderClear(rend);
         SDL_RenderCopy(rend, background, NULL, NULL);
           
       
        if(n1 == 0){
            //printf ("vecino izquierdo\n");
             door1Rect.x = 0;
             door1Rect.y =(WINDOW_SIZE -  door1Rect.w) / 2;
              SDL_RenderCopy(rend, door1, NULL, &door1Rect);
            
           
        }else if(n1 == 1){
            //printf("vecino derecho\n"); 
             door1Rect.x = (WINDOW_SIZE -  door1Rect.w);
             door1Rect.y =(WINDOW_SIZE -  door1Rect.w) / 2;
             SDL_RenderCopy(rend, door1, NULL, &door1Rect);
            
            

        }else if(n1 == 2){
            //printf("vecino arriba\n"); 
             door1Rect.x = (WINDOW_SIZE -  door1Rect.w) / 2;
             door1Rect.y =0;
             SDL_RenderCopy(rend, door1, NULL, &door1Rect);
            
        }else if(n1 == 3){
            //printf("vecino abajo\n"); 
             door1Rect.x = (WINDOW_SIZE -  door1Rect.w) / 2;
             door1Rect.y =(WINDOW_SIZE -  door1Rect.w);
             SDL_RenderCopy(rend, door1, NULL, &door1Rect);
        
        }else{
            //printf("no es vecino \n"); 
        }


        if(n2 == 0){
            //printf ("vecino izquierdo\n");
             door2Rect.x = 0;
             door2Rect.y =(WINDOW_SIZE -  door2Rect.w) / 2;
              SDL_RenderCopy(rend, door2, NULL, &door2Rect);
            
           
        }else if(n2 == 1){
            //printf("vecino derecho\n"); 
             door2Rect.x = (WINDOW_SIZE -  door1Rect.w);
             door2Rect.y =(WINDOW_SIZE -  door1Rect.w) / 2;
             SDL_RenderCopy(rend, door2, NULL, &door2Rect);
            
            

        }else if(n2 == 2){
            //printf("vecino arriba\n"); 
             door2Rect.x = (WINDOW_SIZE -  door2Rect.w) / 2;
             door2Rect.y =0;
             SDL_RenderCopy(rend, door2, NULL, &door2Rect);
            
        }else if(n2 == 3){
            //printf("vecino abajo\n"); 
             door2Rect.x = (WINDOW_SIZE -  door2Rect.w) / 2;
             door2Rect.y =(WINDOW_SIZE -  door2Rect.w);
             SDL_RenderCopy(rend, door2, NULL, &door2Rect);
        
        }else{
            //printf("no es vecino \n"); 
        }

        if(n3 == 0){
            //printf ("vecino izquierdo\n");
             door3Rect.x = 0;
             door3Rect.y =(WINDOW_SIZE -  door3Rect.w) / 2;
              SDL_RenderCopy(rend, door3, NULL, &door3Rect);
            
           
        }else if(n3 == 1){
            //printf("vecino derecho\n"); 
             door3Rect.x = (WINDOW_SIZE -  door3Rect.w);
             door3Rect.y =(WINDOW_SIZE -  door3Rect.w) / 2;
             SDL_RenderCopy(rend, door3, NULL, &door3Rect);
            
            

        }else if(n3 == 2){
            //printf("vecino arriba\n"); 
             door3Rect.x = (WINDOW_SIZE -  door3Rect.w) / 2;
             door3Rect.y =0;
             SDL_RenderCopy(rend, door3, NULL, &door3Rect);
            
        }else if(n3 == 3){
            //printf("vecino abajo\n"); 
             door3Rect.x = (WINDOW_SIZE -  door3Rect.w) / 2;
             door3Rect.y =(WINDOW_SIZE -  door3Rect.w);
             SDL_RenderCopy(rend, door3, NULL, &door3Rect);
        
        }else{
            //printf("no es vecino \n"); 
        }
         SDL_RenderCopy(rend, heroe, NULL, &heroeRect);
      
      
      
        
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);
 
        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
 
    // destroy textures
    
    
    SDL_DestroyTexture(heroe);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(trapDialog);
    SDL_DestroyTexture(treasureDialog);
 
    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}