#include "scheduling.h"
#include <stdio.h>
#include <stdlib.h>

void rr(Process processes[], int n, int quantum, ProcessResult results[], GrantChartNode** grantChartHead) {
    int time = 0;
    int remaining_bt[n];
    Queue* queue = createQueue();
    int completed = 0;

    // Initialize remaining burst times and results
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = processes[i].bt;
        results[i].pid = processes[i].pid;
        results[i].ct = 0;
        results[i].tat = 0;
        results[i].wt = 0;
    }

    // Enqueue processes that have arrived at time 0
    for (int i = 0; i < n; i++) {
        if (processes[i].at == 0) {
            enqueue(queue, processes[i]);
        }
    }

    while (completed < n) {
        if (!isQueueEmpty(queue)) {
            Process current_process = dequeue(queue);
            int pid = current_process.pid;
            int index = -1;

            // Find the index of the current process
            for (int i = 0; i < n; i++) {
                if (processes[i].pid == pid) {
                    index = i;
                    break;
                }
            }

            int exec_time = (remaining_bt[index] > quantum) ? quantum : remaining_bt[index];
            remaining_bt[index] -= exec_time;
            time += exec_time;

            // Append to GrantChart
            appendGrantChartNode(grantChartHead, pid, time - exec_time, time);

            // Enqueue new processes that have arrived during the execution
            for (int i = 0; i < n; i++) {
                if (processes[i].at > time - exec_time && processes[i].at <= time) {
                    enqueue(queue, processes[i]);
                }
            }

            // If the process is not finished, enqueue it again
            if (remaining_bt[index] > 0) {
                enqueue(queue, current_process);
            } else {
                // Process is finished
                results[index].ct = time;
                results[index].tat = results[index].ct - processes[index].at;
                results[index].wt = results[index].tat - processes[index].bt;
                completed++;
            }
        } else {
            time++;
            // Enqueue new processes that have arrived at the new time
            for (int i = 0; i < n; i++) {
                if (processes[i].at == time) {
                    enqueue(queue, processes[i]);
                }
            }
        }
    }
}