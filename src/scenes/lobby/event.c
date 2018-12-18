#include "event.h"
#include "../../engine/game/tutorial.h"
#include "../../utils/enhancedSwitch.h"

extern void eventProcess_Scene_lobby(SDL_Event event, Engine* engine, Data* data) {
    float Vchange = 2 * getTicks_Timer(data->Isaac->movement->timeSince) * (float) 0.06;
    if(Vchange>300) {
        Vchange=0;
    }

    if(data->Isaac->combat->animationStep>450)
    {
        data->Isaac->combat->animationStep=0;
        data->Isaac->movement->direction=data->lobby->askCombat;
        stop_Timer(data->Isaac->combat->timeSince);
        data->lobby->askCombat = -1;
    }

    Uint8 *keystate = SDL_GetKeyState(NULL);

        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    int input = event.key.keysym.sym;

                    if(data->lobby->tutorial == 0) {
                        // Key pressed
                        SWITCH(input)
                            CASE(engine->keys->INVENTORY)
                                data->lobby->askAction = INVENTORY;
                            BREAK

                            CASE(engine->keys->SELECT)
                                data->lobby->askAction = SELECT;
                            BREAK

                            CASE(engine->keys->LEFT_ATTACK)
                                if (data->lobby->askCombat == -1 && data->lobby->actionProcess == NONE) {
                                    data->lobby->askCombat = 3;
                                }

                                data->lobby->askAction = LEFT;
                            BREAK

                            CASE(engine->keys->RIGHT_ATTACK)
                                if (data->lobby->askCombat == -1 && data->lobby->actionProcess == NONE) {
                                    data->lobby->askCombat = 2;
                                }

                                data->lobby->askAction = RIGHT;
                            BREAK

                            CASE(engine->keys->SWITCH)
                                if(data->lobby->askCombat == -1 && data->lobby->actionProcess == NONE)
                                {
                                    data->Isaac->equipped= (data->Isaac->equipped+1)%2;
                                }
                            BREAK

                            CASE(engine->keys->UP_ATTACK)
                                if (data->lobby->askCombat == -1 && data->lobby->actionProcess == NONE) {
                                    data->lobby->askCombat = 1;
                                }
                            BREAK

                            CASE(engine->keys->DOWN_ATTACK)
                                if (data->lobby->askCombat == -1 && data->lobby->actionProcess == NONE) {
                                    data->lobby->askCombat = 0;
                                }
                            BREAK

                            CASE(SDLK_ESCAPE)
                                data->lobby->askAction = PAUSE;
                            BREAK
                        ENDSWITCH
                    }
                    
                    if (SDLK_ESCAPE == input) {
                        data->lobby->askAction = PAUSE;
                    }

                    break;
                }
                case SDL_QUIT: {
                    data->stop = 0;
                    break;
                }
                default:
                    break;
            }
        }

        if ((keystate[engine->keys->UP] || keystate[engine->keys->LEFT] || keystate[engine->keys->DOWN] ||
            keystate[engine->keys->RIGHT]) && data->lobby->tutorial == 0) {
            if (keystate[engine->keys->UP]) {
                data->Isaac->movement->velocity->y -= Vchange;
            }
            if (keystate[engine->keys->LEFT]) {
                data->Isaac->movement->velocity->x -= Vchange;
            }
            if (keystate[engine->keys->DOWN]) {
                data->Isaac->movement->velocity->y += Vchange;
            }
            if (keystate[engine->keys->RIGHT]) {
                data->Isaac->movement->velocity->x += Vchange;
            }
        }

        processTutorial(data, Vchange);
}
