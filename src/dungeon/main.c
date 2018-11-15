#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include <SDL/SDL.h>

#include "utils/treemap.h"

bool nextBool(double probability) {
    return rand() <  probability * ((double)RAND_MAX + 1.0);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* window = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (window == NULL) {
        fprintf(stderr, "Failed to load graphical view: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("FREE_PROJECT_DUNGEONS", NULL);
    int gameStop = 1;
    SDL_Event event;

    srand(time(NULL));
    int start = 1;

    while (gameStop) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    gameStop = 0;
                    break;
                }
            }
        }

        if (start == 1) {
            TreeMap* myTreeMap = init_TreeMap();

            Coord* coord1 = init_Coord(1, 0);
            Symbol* symbol1 = init_Symbol(1);
            Room* room1 = init_Room(coord1, NULL, symbol1, NULL);

            Coord* coord2 = init_Coord(0, 2);
            Symbol* symbol2 = init_Symbol(1);
            Room* room2 = init_Room(coord2, NULL, symbol2, NULL);

            Coord* coord3 = init_Coord(0, 3);
            Symbol* symbol3 = init_Symbol(1);
            Room* room3 = init_Room(coord3, NULL, symbol3, NULL);

            Coord* coord4 = init_Coord(-2, 3);
            Symbol* symbol4 = init_Symbol(1);
            Room* room4 = init_Room(coord4, NULL, symbol4, NULL);

            printf("%p\n", room1);

            put_TreeMap(&(myTreeMap->root), room1);
            put_TreeMap(&(myTreeMap->root), room2);
            put_TreeMap(&(myTreeMap->root), room3);
            put_TreeMap(&(myTreeMap->root), room4);
            //printf_TreeMap(myTreeMap->root);

            start = 0;
        }

        SDL_Flip(window);
        SDL_Delay(500);
    }

    SDL_Quit();

    return 0;
}