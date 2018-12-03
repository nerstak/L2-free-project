#ifndef FREE_PROJECT_ENGINE_CONFIG_H
#define FREE_PROJECT_ENGINE_CONFIG_H

/**
 * Define the volume of the game
 * @param engine a pointer of Engine Object
 * @param type a string. Either "sfx", either "music"
 * @param newVolume an int corresponding to the new volume. From 0 to 100
 */
extern void setVolume(Engine* engine, char* type, int newVolume);


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

/**
 * Find the value of key asked with its ID (-1 if not found)
 * @param keys pointer to a referenceKey Object
 * @param id int. ID in the left to right, top to bottom order of settings screen
 * @return int corresponding to the key
 */
extern int findKeyID(referenceKey* keys, int id);

/**
 * Edit the value of key asked with its ID if not used
 * @param keys pointer to a referenceKey Object
 * @param id int. ID in the left to right, top to bottom order of settings screen
 * @param newKey int of the new value of the key (according to SDL values)
 */
extern void alterKeyID(referenceKey* keys, int id, int newKey);

#endif
