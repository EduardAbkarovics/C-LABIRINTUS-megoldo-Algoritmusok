#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <SDL2/SDL_ttf.h>

// Globális valtozok
int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
SDL_Color white = {255, 255, 255, 255};


bool init() {
    // SDL inicializálása
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    // SDL_ttf inicializálása
    if (TTF_Init() == -1) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        return false;
    }

    // Ablak létrehozása
    window = SDL_CreateWindow("Labirintus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return false;
    }

    // Renderer létrehozása
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return false;
    }

    // fontok
    font = TTF_OpenFont("/usr/share/fonts/TTF/JetBrainsMono-Light.ttf", 24);
    if (font == NULL) {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

// Erőforrások felszabadítása kilépés előtt
void cleanUp() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main() {
    if (!init()) {
        printf("Hiba az inicializálás során!\n");
        return 1;
    }

    // fo esemeny ciklus
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        // Események kezelése
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true; // Kilépés, ha az ablakot bezárják
            }
        }

        // Képernyő törlése és háttér beállítása
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fekete háttér
        SDL_RenderClear(renderer);

        // A rács kirajzolása
        std::vector<std::vector<int>> racs(30, std::vector<int>(30, 1));
        int cellSize = 20;

        for (int row = 0; row < 30; row++) {
            for (int col = 0; col < 30; col++) {
                // Szám kirajzolasa
                std::string text = std::to_string(racs[row][col]);
                SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), white);
                if (surface == NULL) continue;
                
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture == NULL) {
                    SDL_FreeSurface(surface);
                    continue;
                }

                SDL_Rect dest = {
                    col * cellSize + 4,
                    row * cellSize + 4,
                    surface->w,
                    surface->h
                };

                SDL_RenderCopy(renderer, texture, NULL, &dest);
                SDL_FreeSurface(surface);
                SDL_DestroyTexture(texture);
            }
        }

        // Keperny frisitese
        SDL_RenderPresent(renderer);
    }

    // Erőforrások felszabaditasa
    cleanUp();

    return 0;
}
