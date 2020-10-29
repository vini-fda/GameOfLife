#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "GOL.h"

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
    SDL_Texture *bitmapTex = NULL;
    int w = 512;
    int h = 512;
    /*get pixels from GOL*/
    world_state wrld;
    wrld.cells = NULL;
    wrld.w = w;
    wrld.h = h;
    initialize_world(&wrld);
    //int k = wrld.cells[0];
    //First condition
    if (init(&ctx)) {
        bitmapTex = SDL_CreateTexture(ctx.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h);
        if(bitmapTex == NULL) {
            printf("Error: texture could not be created. Full SDL error: %s\n", SDL_GetError());
        }
        uint32_t* pixels = NULL;
        int pitch;

//        if(result != 0)
//            printf("Error locking texture. Full SDl Error: %s\n", SDL_GetError());
//        //Start render
          SDL_PixelFormat* rgba8888 = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
          uint32_t p;
          int row_len = pitch / sizeof(uint32_t);
//        printf("pitch: %d, row_len: %d, size: %d\n", pitch, row_len, sizeof(uint32_t));
//        printf("bytes per pixel: %d\n", rgba8888->BytesPerPixel);
//        //TODO:Clean up main()
//        for (int y = 0; y < h; y++) {
//            for (int x = 0; x < w; x++) {
//                p = 255*wrld.cells[x + y*w];
//                pixels[x + y*w] = SDL_MapRGBA(rgba8888, p, p, p, 255);
//            }
//        }
//        //End render
//        SDL_UnlockTexture(bitmapTex);
//        SDL_FreeFormat(rgba8888);
        //int result;
        //Main loop
        while (!ctx.quit) {
            while (SDL_PollEvent(&ctx.e) != 0) {
                if (ctx.e.type == SDL_QUIT)
                    ctx.quit = true;
            }
            update_world(&wrld);
            SDL_LockTexture(bitmapTex, NULL, (void**) &pixels, &pitch);
            //Start render
            //TODO:GPU acceleration
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    p = 255*get_cell_value(x, y, &wrld);
                    pixels[x + y*w] = SDL_MapRGBA(rgba8888, p, p, p, 255);
                }
            }
            //End render
            SDL_UnlockTexture(bitmapTex);


            SDL_RenderClear(ctx.renderer);
            SDL_RenderCopy(ctx.renderer, bitmapTex, NULL, NULL);
            SDL_RenderPresent(ctx.renderer);

            SDL_Delay(100);
        }
        //Wait before exit
        SDL_Delay(10);
        SDL_FreeFormat(rgba8888);
    }

    //Clean up and quit SDL subsystems
    cleanup_world(&wrld);
    cleanup(&ctx);
    SDL_Quit();

    return 0;
}
