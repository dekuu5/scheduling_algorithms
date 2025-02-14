#include "scheduling.h"
#include <stdio.h>
#include <stdlib.h>

void rr(Process processes[], int n, int quantum, ProcessResult results[], GrantChartNode** grantChartHead) {
    int currentTime = 0;
    int completed = 0;
    int* remainingBurstTime = (int*)malloc(n * sizeof(int));
    int* isCompleted = (int*)calloc(n, sizeof(int));
    Queue* queue = createQueue();

    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = processes[i].bt;
    }

    enqueue(queue, processes[0]);
    isCompleted[0] = 1;

    while (completed < n) {
        if (isQueueEmpty(queue)) {
            currentTime++;
            for (int i = 0; i < n; i++) {
                if (!isCompleted[i] && processes[i].at <= currentTime) {
                    enqueue(queue, processes[i]);
                    isCompleted[i] = 1;
                }
            }
            continue;
        }

        Process currentProcess = dequeue(queue);
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].pid == currentProcess.pid) {
                idx = i;
                break;
            }
        }

        if (remainingBurstTime[idx] > quantum) {
            currentTime += quantum;
            remainingBurstTime[idx] -= quantum;
            appendGrantChartNode(grantChartHead, currentProcess.pid, currentTime - quantum, currentTime);
        } else {
            currentTime += remainingBurstTime[idx];
            results[idx].pid = currentProcess.pid;
            results[idx].ct = currentTime;
            results[idx].tat = currentTime - processes[idx].at;
            results[idx].wt = results[idx].tat - processes[idx].bt;
            remainingBurstTime[idx] = 0;
            completed++;
            appendGrantChartNode(grantChartHead, currentProcess.pid, currentTime - remainingBurstTime[idx], currentTime);
        }

        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].at <= currentTime) {
                enqueue(queue, processes[i]);
                isCompleted[i] = 1;
            }
        }

        if (remainingBurstTime[idx] > 0) {
            enqueue(queue, currentProcess);
        }
    }

    free(remainingBurstTime);
    free(isCompleted);
}