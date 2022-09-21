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
    // for(int i = 0; i < matrixSize; i++){
    //     printf("POS:\tx = %d y = %d\n N1:\tx = %d y = %d\n N2:\tx = %d y = %d\n N3:\tx = %d y = %d\n COFFER TYPE:\t %d\n ROOM TYPE:\t%d\n\n", rooms[i] -> pos[0], rooms[i] -> pos[1], rooms[i] -> neighbour1[0], rooms[i] -> neighbour1[1], rooms[i] -> neighbour2[0], rooms[i] -> neighbour2[1], rooms[i] -> neighbour3[0], rooms[i] -> neighbour3[1], rooms[i] -> cofferType, rooms[i] -> type);
    // }
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

    // creates a surface to load an image into the main memory
    surface = IMG_Load("Images/background.jpg");
    SDL_Texture* background = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
 
    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect dest;
 
    // connects our texture with dest to control position
    SDL_QueryTexture(heroe, NULL, NULL, &dest.w, &dest.h);
 
    // adjust height and width of our image box.
    dest.w /= 8;
    dest.h /= 8;
 
    // sets initial x-position of object
    dest.x = (WINDOW_SIZE - dest.w) / 2;
 
    // sets initial y-position of object
    dest.y = (WINDOW_SIZE - dest.h) / 2;
 
    // controls animation loop
    int close = 0;
 
    // speed of box
    int speed = 30;
 
    // animation loop
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
                    dest.y -= speed;
                    break;
                case SDL_SCANCODE_A:
                    dest.x -= speed;
                    break;
                case SDL_SCANCODE_S:
                    dest.y += speed;
                    break;
                case SDL_SCANCODE_D:
                    dest.x += speed;
                    break;
                default:
                    break;
                }
            }
        }
 
        // right boundary
        if (dest.x + dest.w > WINDOW_SIZE)
            dest.x = WINDOW_SIZE - dest.w;
 
        // left boundary
        if (dest.x < 0)
            dest.x = 0;
 
        // bottom boundary
        if (dest.y + dest.h > WINDOW_SIZE)
            dest.y = WINDOW_SIZE - dest.h;
 
        // upper boundary
        if (dest.y < 0)
            dest.y = 0;
 
        // clears the screen
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, background, NULL, NULL);
        SDL_RenderCopy(rend, heroe, NULL, &dest);
        
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);
 
        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
 
    // destroy textures
    SDL_DestroyTexture(heroe);
    SDL_DestroyTexture(background);
 
    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}