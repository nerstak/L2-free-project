#include "notification.h"

extern Notification* init_Notification() {
    Notification* p = NULL;
    p = malloc(1 * sizeof(Notification));

    if (p == NULL) {
        // TODO: printf error
        exit(EXIT_FAILURE);
    }

    p->icon = NULL;
    p->text[0] = '\0';
    p->timer = init_Timer();

    return p;
}

extern NotificationQueue* initQueue_Notification() {
    NotificationQueue* q = NULL;
    q = malloc(1 * sizeof(NotificationQueue));

    if (q == NULL) {
        // TODO: printf error
        exit(EXIT_FAILURE);
    }

    q->front = NULL;
    q->rear = NULL;

    return q;
}

extern void clean_Notification(Notification** p) {
    if ((*p) != NULL) {
        clean_Timer(&((*p)->timer));

        free((*p));
        (*p) = NULL;
    }
}

extern void cleanQueue_Notification(NotificationQueue** p) {
    if ((*p) != NULL) {
        if ((*p)->rear == NULL) {
            free(*p);
            (*p) = NULL;
        } else {
            NotificationQueueNode* temp = NULL;
            while ((*p)->rear != NULL) {
                temp = (*p)->front;
                (*p)->front = (*p)->front->next;

                clean_Notification(&(temp->data));
                free(temp);

                if ((*p)->front == NULL) {
                    (*p)->rear = NULL;
                }
            }

            free((*p));
            (*p) = NULL;
        }
    }
}

extern void enQueue_Notification(NotificationQueue* q, Notification* p) {
    NotificationQueueNode* temp = NULL;
    temp = malloc(1 * sizeof(NotificationQueueNode));

    if (temp == NULL) {
        // TODO: Printf error
        exit(EXIT_FAILURE);
    }

    temp->data = p;
    temp->next = NULL;

    if (q->rear == NULL) {
        q->front = temp;
        q->rear = temp;

        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

extern NotificationQueueNode* deQueue_Notification(NotificationQueue* q) {
    if (q->front == NULL) {
        return NULL;
    }

    return q->front;
}

extern void popQueue_Notification(NotificationQueue* q) {
    if (q->front == NULL) {
        return;
    }

    NotificationQueueNode* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    clean_Notification(&(temp->data));
    free(temp);
}

extern bool isEmptyQueue_Notification(NotificationQueue* q) {
    if (q->rear == NULL) {
        return true;
    } else {
        return false;
    }
}
