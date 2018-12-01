#ifndef FREE_PROJECT_ENGINE_CONFIG_H
#define FREE_PROJECT_ENGINE_CONFIG_H

/**
 * Define the volume of the game
 * @param type a string. Either "sfx", either "music"
 * @param newVolume an int corresponding to the new volume. From 0 to 100
 */
extern void setVolume(char* type, int newVolume);


/**
 * Read the config from a file
 * @param engine a pointer to an Engine Object
 */
extern void readConfig(Engine* engine);

/**
 * Write the config to a file
 * @param engine a pointer to an Engine Object
 */
extern void writeConfig(Engine* engine);

#endif
