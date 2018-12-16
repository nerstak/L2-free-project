#include "sound.h"

static void add_AudioElement(SoundCollector* p, AudioElement* e);
static void remove_AudioElement(SoundCollector* p, AudioElement* e);

static AudioElement* isLoaded_SoundCollector(SoundCollector* p, const char name[]);

static void add_AudioElement(SoundCollector* p, AudioElement* e) {
    // Is our list of images empty ?
    if (p->audioElements == NULL) {
        // We write directly to the pointer
        p->audioElements = e;
        p->size += 1;
    } else {
        // We find the last element of the list
        AudioElement* temp = NULL;
        temp = p->audioElements;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        // We add our element
        temp->next = e;
        p->size += 1;
    }
}

static void remove_AudioElement(SoundCollector* p, AudioElement* e) {
    AudioElement* temp = p->audioElements;
    AudioElement* previous = p->audioElements;

    // Is the element we want to remove the first one ?
    if (e->music != NULL
        && temp->music != NULL
        && strcmp(temp->music->name, e->music->name) == 0) {
        // We rewrite the head of our list
        p->audioElements = temp->next;
        p->size -= 1;

        // Don't forget to free the music and the memory :D
        Mix_FreeMusic(temp->music->src);
        free(temp->music);
        free(temp);
    } else if (e->sound != NULL && temp->sound != NULL && strcmp(temp->sound->name, e->sound->name) == 0) {
        // We rewrite the head of our list
        p->audioElements = temp->next;
        p->size -= 1;

        // Don't forget to free the sound and the memory :D
        Mix_FreeChunk(temp->sound->src);
        free(temp->sound);
        free(temp);
    } else {
        // We find the position of the element we want to remove
        while (temp != NULL) {
            if (temp->music != NULL && e->music != NULL && strcmp(temp->music->name, e->music->name) == 0) {
                break;
            } else if (temp->sound != NULL && e->sound != NULL && strcmp(temp->sound->name, e->sound->name) == 0) {
                break;
            }

            previous = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            return;
        }

        // Relink our list
        previous->next = temp->next;

        if (temp->sound != NULL) {
            // Don't forget to free the surface and the memory :D
            Mix_FreeChunk(temp->sound->src);
            free(temp->sound);
        } else if (temp->music != NULL) {
            // Don't forget to free the surface and the memory :D
            Mix_FreeMusic(temp->music->src);
            free(temp->music);
        }

        free(temp);

        p->size -= 1;
    }
}

static AudioElement* isLoaded_SoundCollector(SoundCollector* p, const char name[]) {
    AudioElement* temp = p->audioElements;

    // We retrieve the existing AudioElement from our SoundCollector
    while (temp != NULL) {
        if (temp->music != NULL && strcmp(temp->music->name, name) == 0) {
            return temp;
        }

        if (temp->sound != NULL && strcmp(temp->sound->name, name) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    // Or we return NULL
    return NULL;
}

extern SoundCollector* init_SoundCollector() {
    // Initialization of a SoundCollector pointer
    SoundCollector* p = NULL;
    p = malloc(1 * sizeof(SoundCollector));

    // If we failed to allocate, exit the program
    if (p == NULL) {
        printf("An error occurred while initializing a SoundCollector object\n");
        exit(EXIT_FAILURE);
    }

    // Default value of our instance
    p->size = 0;
    p->audioElements = NULL;

    return p;
}

extern void clean_SoundCollector(SoundCollector** p) {
    // First we clean the audioElements SLL
    AudioElement* temp = (*p)->audioElements;
    AudioElement* next = NULL;

    while (temp != NULL) {
        next = temp->next;

        remove_AudioElement((*p), temp);

        temp = next;
    }

    // We free this SoundCollector
    free(*p);
    (*p) = NULL;
}


extern void load_SoundCollector(SoundCollector* p, const char path[], const char name[], int type) {
    // Is it already loaded ?
    if (isLoaded_SoundCollector(p, name) != NULL) {
        printf("An attempt to load a cached audio was blocked (%s)\n", name);

        return;
    }

    AudioElement* temp = NULL;
    temp = malloc(1 * sizeof(AudioElement));

    if (temp == NULL) {
        printf("An error occurred while allocating a AudioElement object\n");
        exit(EXIT_FAILURE);
    }

    temp->sound = NULL;
    temp->music = NULL;

    temp->next = NULL;

    if (type == SOUND) {
        temp->sound = malloc(1 * sizeof(Sound));

        if (temp->sound == NULL) {
            printf("An error occurred while allocation a Sound object\n");
            exit(EXIT_FAILURE);
        }

        strcpy(temp->sound->name, name);
        temp->sound->src = NULL;
        temp->sound->src = Mix_LoadWAV(path);

        if (temp->sound->src == NULL) {
            printf("%s", SDL_GetError());
            printf("An error occurred while loading a WAV file\n");
            exit(EXIT_FAILURE);
        }
    } else if (type == MUSIC) {
        temp->music = malloc(1 * sizeof(Music));

        if (temp->music == NULL) {
            printf("An error occurred while allocation a Sound object\n");
            exit(EXIT_FAILURE);
        }

        strcpy(temp->music->name, name);
        temp->music->src = NULL;
        temp->music->src = Mix_LoadMUS(path);

        if (temp->music->src == NULL) {
            printf("%s", SDL_GetError());
            printf("An error occurred while loading a WAV file\n");
            exit(EXIT_FAILURE);
        }
    } else {
        free(temp);
        printf("An error occured while loading a sound (unknown type)\n");

        return;
    }

    add_AudioElement(p, temp);
}

extern void loadList_SoundCollector(SoundCollector* p, Asset* assetsList) {
    Asset* temp = NULL;
    temp = assetsList;

    // We go through the list and call the exisiting function
    while (temp != NULL) {
        if (temp->type == SOUND || temp->type == MUSIC) {
            load_SoundCollector(p, temp->path, temp->name, temp->type);
        }

        temp = temp->next;
    }
}

extern void unload_SoundCollector(SoundCollector* p, const char name[], int type) {
    AudioElement e;

    if (type == SOUND) {
        e.sound = NULL;
        e.music = NULL;
        e.sound = malloc(1 * sizeof(Sound));

        if (e.sound == NULL) {
            printf("An error occurred while initializing a Sound object\n");
            exit(EXIT_FAILURE);
        }

        strcpy(e.sound->name, name);
    } else if (type == MUSIC) {
        e.sound = NULL;
        e.music = NULL;
        e.music = malloc(1 * sizeof(Music));

        if (e.music == NULL) {
            printf("An error occurred while initializing a Sound object\n");
            exit(EXIT_FAILURE);
        }

        strcpy(e.music->name, name);
    } else {
        printf("An error occurred while unloading a sound (unknown type)\n");

        return;
    }

    // We remove one AudioElement from our SoundCollector
    remove_AudioElement(p, &e);

    if (type == SOUND) {
        free(e.sound);
    } else if (type == MUSIC) {
        free(e.music);
    }
}

extern void unloadList_SoundCollector(SoundCollector* p, Asset* assetsList) {
    Asset* temp = NULL;
    temp = assetsList;

    // We go through the list and call the existing function
    while (temp != NULL) {
        if (temp->type == SOUND || temp->type == MUSIC) {
            unload_SoundCollector(p, temp->name, temp->type);
        }

        temp = temp->next;
    }
}

extern AudioElement* get_SoundCollector(SoundCollector* p, const char name[]) {
    AudioElement* temp = p->audioElements;

    // We retrieve the existing Image from our ImageCollector
    while (temp != NULL) {
        if (temp->music != NULL && strcmp(temp->music->name, name) == 0) {
            return temp;
        } else if (temp->sound != NULL && strcmp(temp->sound->name, name) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    // If we don't find it, we crash the program nicely to avoid a SegFault
    printf("Trying to load an unloaded AudioElement (%s)\n", name);
    exit(EXIT_FAILURE);

    return NULL;
}

extern int playMusic(SoundCollector* p, const char name[]) {
    AudioElement* current = get_SoundCollector(p, name);
    if(Mix_PlayingMusic() == 0) {
        stopMusic();
    }
    if(Mix_FadeInMusic(current->music->src, -1, 2000) != -1) {
        return 1;
    }
    return 0;
}

extern int playEffect(SoundCollector* p, const char name[], int nbTimes) {
    AudioElement* current = get_SoundCollector(p, name);

    return Mix_PlayChannel(-1, current->sound->src, nbTimes);
}

extern int stopMusic() {
    return Mix_FadeOutMusic(0);
}

extern int stopEffect(int channel) {
    return Mix_FadeOutChannel(channel, 0);
}