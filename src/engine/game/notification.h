#ifndef FREE_PROJECT_ENGINE_GAME_NOTIFICATION_H
#define FREE_PROJECT_ENGINE_GAME_NOTIFICATION_H

#include <SDL/SDL.h>

#include "../timer.h"

typedef struct Notification {
    SDL_Surface* icon;
    SDL_Rect sprite;
    char text[255];

    Timer* timer;
} Notification;

typedef struct NotificationQueue {
    struct NotificationQueueNode* front;
    struct NotificationQueueNode* rear;
} NotificationQueue;

typedef struct NotificationQueueNode {
    struct Notification* data;
    struct NotificationQueueNode* next;
} NotificationQueueNode;

/**
 * Init a Notification Object
 * @return A pointer to a Notification Object
 */
extern Notification* init_Notification();
/**
 * Init a NotificationQueue Object
 * @return a pointer to a NotificationQueue Object
 */
extern NotificationQueue* initQueue_Notification();
/**
 * Free a Notification Object
 * @param p a double pointer to a Notification Object
 */
extern void clean_Notification(Notification** p);
/**
 * Free a NotificationQueue Object
 * @param p a double pointer to a NotificationQueue Object
 */
extern void cleanQueue_Notification(NotificationQueue** p);
/**
 * Add an Element to a NotificationQueue
 * @param q a pointer to a NotificationQueue Object
 * @param p a pointer to a Notification Object
 */
extern void enQueue_Notification(NotificationQueue* q, Notification* p);
/**
 * Get Front Element of a NotificationQueue
 * @param q a pointer to a NotificationQueue Object
 * @return a pointer to a NotificationQueueNode Object
 */
extern NotificationQueueNode* deQueue_Notification(NotificationQueue* q);
/**
 * Remove an element of a NotificationQueue
 * @param q a pointer to a NotificationQueue Object
 */
extern void popQueue_Notification(NotificationQueue* q);
/**
 * Check if a NotificationQueue is empty
 * @param q a pointer to a NotificationQueue Object
 * @return a bool
 */
extern bool isEmptyQueue_Notification(NotificationQueue* q);

#endif //FREE_PROJECT_ENGINE_GAME_NOTIFICATION_H
