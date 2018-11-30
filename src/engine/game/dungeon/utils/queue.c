#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

extern Queue* init_Queue() {
    // Initialization of a Queue pointer
    Queue* myQueue = NULL;
    myQueue = malloc(1 * sizeof(Queue));

    // If we failed to allocate, exit the program
    if (myQueue == NULL) {
        printf("An error occured while initializing a Queue object");
        exit(EXIT_FAILURE);
    }

    myQueue->front = NULL;
    myQueue->rear = NULL;

    return myQueue;
}

extern void clean_Queue(Queue** myQueue) {
    if ((*myQueue)->rear == NULL) {
        free(*myQueue);
        (*myQueue) = NULL;
    } else {
        QueueNode* temp = NULL;
        while ((*myQueue)->rear != NULL) {
            temp = (*myQueue)->front;
            (*myQueue)->front = (*myQueue)->front->next;

            free(temp);

            if ((*myQueue)->front == NULL) {
                (*myQueue)->rear = NULL;
            }
        }

        free((*myQueue));
        (*myQueue) = NULL;
    }
}

extern QueueNode* init_QueueNode(TreeMapNode* myTreeMapNode) {
    // Initialization of a Queue pointer
    QueueNode* myNode = NULL;
    myNode = malloc(1 * sizeof(QueueNode));

    // If we failed to allocate, exit the program
    if (myNode == NULL) {
        printf("An error occured while initializing a QueueNode object");
        exit(EXIT_FAILURE);
    }

    myNode->data = myTreeMapNode;

    return myNode;
}

extern void enQueue_Queue(Queue* myQueue, TreeMapNode* myNode) {
    QueueNode* temp = init_QueueNode(myNode);

    if (myQueue->rear == NULL) {
        myQueue->front = temp;
        myQueue->rear = temp;

        return;
    }

    myQueue->rear->next = temp;
    myQueue->rear = temp;
}

extern TreeMapNode* deQueue_Queue(Queue* myQueue) {
    if (myQueue->front == NULL) {
        return NULL;
    }

    QueueNode* temp = myQueue->front;
    myQueue->front = myQueue->front->next;

    if (myQueue->front == NULL) {
        myQueue->rear = NULL;
    }

    TreeMapNode* returned = temp->data;
    free(temp);

    return returned;
}

extern bool isEmpty_Queue(Queue* myQueue) {
    if (myQueue->rear == NULL) {
        return true;
    } else {
        return false;
    }
}