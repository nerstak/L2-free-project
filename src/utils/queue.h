#ifndef FREE_PROJECT_UTILS_QUEUE_H
#define FREE_PROJECT_UTILS_QUEUE_H

#include "treemap.h"

typedef struct QueueNode {
    TreeMapNode* data;

    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

extern Queue* init_Queue();
extern void clean_Queue(Queue** myQueue);
extern QueueNode* init_QueueNode(TreeMapNode* myTreeMapNode);
extern void enQueue_Queue(Queue* myQueue, TreeMapNode* myNode);
extern TreeMapNode* deQueue_Queue(Queue* myQueue);
extern bool isEmpty_Queue(Queue* myQueue);

#endif //FREE_PROJECT_UTILS_QUEUE_H
