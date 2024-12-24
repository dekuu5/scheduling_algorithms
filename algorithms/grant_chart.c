#include "scheduling.h"
#include <stdio.h>
#include <stdlib.h>


GrantChartNode* createGrantChartNode(int pid, int start_time, int end_time) {
    GrantChartNode* newNode = (GrantChartNode*)malloc(sizeof(GrantChartNode));
    newNode->pid = pid;
    newNode->start_time = start_time;
    newNode->end_time = end_time;
    newNode->next = NULL;
    return newNode;
}

void appendGrantChartNode(GrantChartNode** head, int pid, int start_time, int end_time) {
    GrantChartNode* newNode = createGrantChartNode(pid, start_time, end_time);
    if (*head == NULL) {
        *head = newNode;
    } else {
        GrantChartNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printGrantChart(GrantChartNode* head) {
    GrantChartNode* temp = head;
    while (temp != NULL) {
        printf("P%d [%d - %d] ", temp->pid, temp->start_time, temp->end_time);
        temp = temp->next;
    }
    printf("\n");
}