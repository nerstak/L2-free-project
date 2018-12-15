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

extern Notification* init_Notification();
extern NotificationQueue* initQueue_Notification();
extern void clean_Notification(Notification** p);
extern void cleanQueue_Notification(NotificationQueue** p);
extern void enQueue_Notification(NotificationQueue* q, Notification* p);
extern NotificationQueueNode* deQueue_Notification(NotificationQueue* q);
extern void popQueue_Notification(NotificationQueue* q);
extern bool isEmptyQueue_Notification(NotificationQueue* q);

#endif //FREE_PROJECT_ENGINE_GAME_NOTIFICATION_H
