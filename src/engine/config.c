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