#include "scheduling.h"
#include <stdio.h>

void fcfs(Process processes[], int n, ProcessResult results[], GrantChartNode** grantChartHead) {
    Queue* queue = createQueue();
    int current_time = 0;
    int completed = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].at > processes[j + 1].at) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (!visited[i] && processes[i].at <= current_time) {
                visited[i] = 1;
                enqueue(queue, processes[i]);
            }
        }
        // Print the queue
        QueueNode* temp = queue->front;
        printf("Queue: ");
        while (temp != NULL) {
            printf("P%d ", temp->process.pid);
            temp = temp->next;
        }
        printf("\n");

        if (!isQueueEmpty(queue)) {
            Process process = dequeue(queue);
            current_time += process.bt;

            results[completed].pid = process.pid;
            results[completed].ct = current_time;
            results[completed].tat = current_time - process.at;
            results[completed].wt = results[completed].tat - process.bt;

            appendGrantChartNode(grantChartHead, process.pid, current_time - process.bt, current_time);
            completed++;
        } else {
            current_time++;
        }
    }
}