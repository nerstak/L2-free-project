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

/**
 * Create a Queue object
 * @return
 */
extern Queue* init_Queue();
/**
 * Clean a Queue object
 * @param myQueue a double pointer to a Queue object
 */
extern void clean_Queue(Queue** myQueue);
/**
 * Create a QueueNode object with given TreeMapNode
 * @param myTreeMapNode the pointer to a TreeMapNode object
 * @return a QueueNode object
 */
extern QueueNode* init_QueueNode(TreeMapNode* myTreeMapNode);
/**
 * Add a TreeMapNode object to a given Queue
 * @param myQueue the queue to update
 * @param myNode  the given TreeMapNode object to add
 */
extern void enQueue_Queue(Queue* myQueue, TreeMapNode* myNode);
/**
 * Remove a TreeMapNode object to a given Queue, and return it
 * @param myQueue the queue to update
 * @return a TreeMapNode object
 */
extern TreeMapNode* deQueue_Queue(Queue* myQueue);
/**
 * Verify if a Queue is empty
 * @param myQueue the queue to check
 * @return a boolean according to the result
 */
extern bool isEmpty_Queue(Queue* myQueue);

#endif //FREE_PROJECT_UTILS_QUEUE_H
