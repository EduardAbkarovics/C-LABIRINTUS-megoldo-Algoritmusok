#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;

int ablak(){
    // SDL inicializálása
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Ablak létrehozása
    SDL_Window *window = SDL_CreateWindow("Example: 0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Renderer létrehozása
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Háttér szín beállítása fehérre
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); // Képernyő törlése
    SDL_RenderPresent(renderer); // Kép megjelenítése

    // Eseményfigyelés loop
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;  // Kilépés, ha az ablakot bezárják
            }
        }
    }

    // Erőforrások felszabadítása
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
int grid(){
  std::vector<std::vector<int>> racs(30, std::vector<int>(30,1));
  return 0;
}


int main(){
  ablak();
  grid();
  return 0;
}
