#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL_mixer.h>

#include "main.h"
#include "config.h"

/**
 * Check if a specific value is attributed to an action
 * @param keys a pointer to a referenceKey Object
 * @param newKey an int that will be checked
 * @return an int (0: is not attributed, 1: is attributed)
 */
static int isKeyAttributed(referenceKey* keys, int newKey);

extern void setVolume(Engine* engine, char* type, int newVolume) {
    if(newVolume < 0) {
        newVolume = 0;
    } else if (newVolume > 100) {
        newVolume = 100;
    }
    if(strcmp(type,"music") == 0) {
        Mix_VolumeMusic(newVolume/100 * 128);
        engine->volumeMusic = newVolume;
    } else if(strcmp(type, "sfx") == 0) {
        engine->volumeSFX = newVolume;
        Mix_Volume(-1, newVolume/100 * 128);
    }
}

extern void readConfig(Engine* engine) {
    FILE* cfgFile;
    cfgFile = fopen("config/options.txt","r");

    if(cfgFile == NULL) {
        //TODO: Reset cfg
    } else {
        fscanf(cfgFile,"FPS=%d\n",&(engine->fps->maxFps));
        fscanf(cfgFile,"SFX=%d\n",&(engine->volumeSFX));
        fscanf(cfgFile,"MUSIC=%d\n",&(engine->volumeMusic));
        fscanf(cfgFile,"UP=%d\n",&(engine->keys->UP));
        fscanf(cfgFile,"DOWN=%d\n",&(engine->keys->DOWN));
        fscanf(cfgFile,"LEFT=%d\n",&(engine->keys->LEFT));
        fscanf(cfgFile,"RIGHT=%d\n",&(engine->keys->RIGHT));
        fscanf(cfgFile,"INVENTORY=%d\n",&(engine->keys->INVENTORY));
        fscanf(cfgFile,"UP_ATTACK=%d\n",&(engine->keys->UP_ATTACK));
        fscanf(cfgFile,"DOWN_ATTACK=%d\n",&(engine->keys->DOWN_ATTACK));
        fscanf(cfgFile,"LEFT_ATTACK=%d\n",&(engine->keys->LEFT_ATTACK));
        fscanf(cfgFile,"RIGHT_ATTACK=%d\n",&(engine->keys->RIGHT_ATTACK));
        fscanf(cfgFile,"SELECT=%d\n",&(engine->keys->SELECT));

        fclose(cfgFile);

        setMaxFps_Fps(engine->fps,true,engine->fps->maxFps);
        setVolume(engine,"sfx",engine->volumeSFX);
        setVolume(engine,"music",engine->volumeMusic);
    }
}

extern void writeConfig(Engine* engine) {
    FILE* cfgFile;
    cfgFile = fopen("config/options.txt","w+");

    if(cfgFile) {
        fprintf(cfgFile,"FPS=%d\n",engine->fps->maxFps);
        fprintf(cfgFile,"SFX=%d\n",engine->volumeSFX);
        fprintf(cfgFile,"MUSIC=%d\n",engine->volumeMusic);
        fprintf(cfgFile,"UP=%d\n",engine->keys->UP);
        fprintf(cfgFile,"DOWN=%d\n",engine->keys->DOWN);
        fprintf(cfgFile,"LEFT=%d\n",engine->keys->LEFT);
        fprintf(cfgFile,"RIGHT=%d\n",engine->keys->RIGHT);
        fprintf(cfgFile,"INVENTORY=%d\n",engine->keys->INVENTORY);
        fprintf(cfgFile,"UP_ATTACK=%d\n",engine->keys->UP_ATTACK);
        fprintf(cfgFile,"DOWN_ATTACK=%d\n",engine->keys->DOWN_ATTACK);
        fprintf(cfgFile,"LEFT_ATTACK=%d\n",engine->keys->LEFT_ATTACK);
        fprintf(cfgFile,"RIGHT_ATTACK=%d\n",engine->keys->RIGHT_ATTACK);
        fprintf(cfgFile,"SELECT=%d\n",engine->keys->SELECT);

        fclose(cfgFile);
    }
}

extern int findKeyID(referenceKey* keys, int id) {
    switch(id) {
        case 0: {
            //Up
            return keys->UP;
        }
        case 1: {
            //Up Attack
            return keys->UP_ATTACK;
        }
        case 2: {
            //Down
            return keys->DOWN;
        }
        case 3: {
            //Down Attack
            return keys->DOWN_ATTACK;
        }
        case 4: {
            //Left
            return keys->LEFT;
        }
        case 5: {
            //Left Attack
            return keys->LEFT_ATTACK;
        }
        case 6: {
            //Right
            return keys->RIGHT;
        }
        case 7: {
            //Right Attack
            return keys->RIGHT_ATTACK;
        }
        case 8: {
            //Inventory
            return keys->INVENTORY;
        }
        case 9: {
            //Select
            return keys->SELECT;
        }
        default: {
            return -1;
        }
    }
}

extern void alterKeyID(referenceKey* keys, int id, int newKey) {
    if (!isKeyAttributed(keys, newKey)) {
        switch (id) {
            case 0: {
                //Up
                keys->UP = newKey;
                break;
            }
            case 1: {
                //Up Attack
                keys->UP_ATTACK = newKey;
                break;
            }
            case 2: {
                //Down
                keys->DOWN = newKey;
                break;
            }
            case 3: {
                //Down Attack
                keys->DOWN_ATTACK = newKey;
                break;
            }
            case 4: {
                //Left
                keys->LEFT = newKey;
                break;
            }
            case 5: {
                //Left Attack
                keys->LEFT_ATTACK = newKey;
                break;
            }
            case 6: {
                //Right
                keys->RIGHT = newKey;
                break;
            }
            case 7: {
                //Right Attack
                keys->RIGHT_ATTACK = newKey;
                break;
            }
            case 8: {
                //Inventory
                keys->INVENTORY = newKey;
                break;
            }
            case 9: {
                //Select
                keys->SELECT = newKey;
                break;
            }
            default: {
                break;
            }
        }
    }
}

static int isKeyAttributed(referenceKey* keys, int newKey) {
    if(keys->SELECT == newKey
    || keys->INVENTORY == newKey
    || keys->RIGHT_ATTACK == newKey
    || keys->LEFT_ATTACK == newKey
    || keys->DOWN_ATTACK == newKey
    || keys->UP_ATTACK == newKey
    || keys->LEFT == newKey
    || keys->RIGHT == newKey
    || keys->DOWN == newKey
    || keys->UP == newKey) {
        return 1;
    }
    return 0;
}