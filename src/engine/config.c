#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL_mixer.h>

#include "main.h"
#include "config.h"

extern void setVolume(char* type, int newVolume) {
    if(newVolume < 0) {
        newVolume = 0;
    } else if (newVolume > 100) {
        newVolume = 100;
    }
    if(strcmp(type,"music") == 0) {
        Mix_VolumeMusic(newVolume/100 * 128);
    } else if(strcmp(type, "sfx") == 0) {
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

        setVolume("sfx",engine->volumeSFX);
        setVolume("music",engine->volumeMusic);
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