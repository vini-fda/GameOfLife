#include <SDL2/SDL.h>
#include <stdio.h>

typedef int bool;
#define true 1
#define false 0

//Screen dimension constants
const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;

typedef struct context context;
struct context {
    SDL_Window *window;

    bool quit;
    SDL_Event e;

    SDL_Renderer *renderer;
};

/* This function initializes the context ctx
 * and returns whether it was successful in doing so */
bool init(context* ctx) {
    //Variable to say if the application should exit(false by default)
    ctx->quit = false;

    //Initialize video subsystem
    //(there are other subsystems too, check out the SDL docs)
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        //TODO:FIX MEMORY LEAK WITH SDL_INIT()
        //might be unsolvable, though, and it is a minor problem(for now)
        printf("Error initializing SDL! Full error: %s\n", SDL_GetError());
        return false;
    } else {
        //Create window
        ctx->window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        //Create renderer
        ctx->renderer = SDL_CreateRenderer(ctx->window, -1, SDL_RENDERER_PRESENTVSYNC);
        if (ctx->renderer == NULL) {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            return false;
        }
        //Set render background to black
        SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    }
    return true;
}

bool cleanup(context* ctx) {
    //Destroy renderer
    SDL_DestroyRenderer(ctx->renderer);
    ctx->renderer = NULL;

    //Destroy window
    SDL_DestroyWindow(ctx->window);
    ctx->window = NULL;
}

int main(int argc, char *args[]) {
    /*  Init variables  */
    context ctx;

    //First condition
    if (init(&ctx)) {
        //Main loop
        while (!ctx.quit) {
            while (SDL_PollEvent(&ctx.e) != 0) {
                if (ctx.e.type == SDL_QUIT)
                    ctx.quit = true;
            }
            SDL_RenderClear(ctx.renderer);
            SDL_RenderPresent(ctx.renderer);
        }
        //Wait before exit
        SDL_Delay(10);
    }

    //Clean up and quit SDL subsystems
    cleanup(&ctx);
    SDL_Quit();

    return 0;
}
