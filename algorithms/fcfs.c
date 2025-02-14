#include "scheduling.h"
#include <stdio.h>
#include <stdlib.h>

// int compareArrivalTime(const void* a, const void* b) {
//     Process* processA = (Process*)a;
//     Process* processB = (Process*)b;
//     return processA->at - processB->at;
// }

void fcfs(Process processes[], int n, ProcessResult results[], GrantChartNode** grantChartHead) {
    Queue* queue = createQueue();
    int current_time = 0;
    int completed = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;


    qsort(processes, n, sizeof(Process), compareArrivalTime);

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