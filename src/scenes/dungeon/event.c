#include "event.h"
#include "../../utils/enhancedSwitch.h"

extern void eventProcess_Scene_dungeon(SDL_Event event, Engine* engine, Data* data) {
    float Vchange = 2 * getTicks_Timer(data->Isaac->movement->timeSince) * (float) 0.06;
    if(Vchange>300) {
        Vchange=0;
    }

    if(data->Isaac->combat->animationStep>450)
    {
        data->Isaac->combat->animationStep=0;
        data->Isaac->movement->direction=data->dungeonScene->askCombat;
        stop_Timer(data->Isaac->combat->timeSince);
        data->dungeonScene->askCombat = -1;
    }

    Uint8 *keystate = SDL_GetKeyState(NULL);

    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                int input = event.key.keysym.sym;
                SWITCH(input)
                    CASE(SDLK_ESCAPE)
                        data->stop = 0;
                    BREAK

                    CASE(engine->keys->LEFT_ATTACK)
                        if (data->dungeonScene->askCombat == -1) {
                            data->dungeonScene->askCombat=3;
                        }
                    BREAK

                    CASE(engine->keys->RIGHT_ATTACK)
                        if (data->dungeonScene->askCombat == -1) {
                            data->dungeonScene->askCombat = 2;
                        }
                    BREAK

                    CASE(engine->keys->UP_ATTACK)
                        if (data->dungeonScene->askCombat == -1) {
                            data->dungeonScene->askCombat = 1;
                        }
                    BREAK

                    CASE(engine->keys->DOWN_ATTACK)
                        if (data->dungeonScene->askCombat == -1) {
                            data->dungeonScene->askCombat = 0;
                        }
                    BREAK
                    ENDSWITCH

                break;
            }

            case SDL_QUIT: {
                data->stop = 0;
                break;
            }

            default: {
                break;
            }
        }
    }

    if(keystate[engine->keys->UP] || keystate[engine->keys->LEFT] || keystate[engine->keys->DOWN] || keystate[engine->keys->RIGHT]) {
        if(keystate[engine->keys->UP]) {
            data->Isaac->movement->velocity->y -= Vchange;
        }
        if(keystate[engine->keys->LEFT]) {
            data->Isaac->movement->velocity->x-=Vchange;
        }
        if(keystate[engine->keys->DOWN]) {
            data->Isaac->movement->velocity->y += Vchange;
        }
        if(keystate[engine->keys->RIGHT]) {
            data->Isaac->movement->velocity->x+=Vchange;
        }
    }
}
