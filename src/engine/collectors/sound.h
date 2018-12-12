#ifndef FREE_PROJECT_ENGINE_COLLECTORS_SOUND_H
#define FREE_PROJECT_ENGINE_COLLECTORS_SOUND_H

#include <SDL/SDL_mixer.h>

#include "../asset.h"

enum audioType {SOUND = 0, MUSIC = 1};

typedef struct Music {
    char name[255];
    Mix_Music* src;
} Music;

typedef struct Sound {
    char name[255];
    Mix_Chunk* src;
} Sound;

typedef struct AudioElement {
    Music* music;
    Sound* sound;

    struct AudioElement* next;
} AudioElement;

typedef struct SoundCollector {
    size_t size;
    AudioElement* audioElements;
} SoundCollector;

extern SoundCollector* init_SoundCollector();
extern void clean_SoundCollector(SoundCollector** p);

extern void load_SoundCollector(SoundCollector* p, const char path[], const char name[], int type);
extern void loadList_SoundCollector(SoundCollector* p, Asset* assetsList);
extern void unload_SoundCollector(SoundCollector* p, const char name[], int type);
extern void unloadList_SoundCollector(SoundCollector* p, Asset* assetsList);

extern AudioElement* get_SoundCollector(SoundCollector* p, const char name[]);

extern int playMusic(SoundCollector* p, const char name[]);
extern int playEffect(SoundCollector* p, const char name[], int nbTimes);
extern int stopMusic();
extern int stopEffect(int channel);

#endif //FREE_PROJECT_ENGINE_COLLECTORS_SOUND_H
