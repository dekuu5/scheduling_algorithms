#include "scheduling.h"
#include <stdlib.h>

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, Process process) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->process = process;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

Process dequeue(Queue* queue) {
    if (queue->front == NULL) {
        Process emptyProcess = {0};
        return emptyProcess;
    }
    QueueNode* temp = queue->front;
    Process process = temp->process;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return process;
}

int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}