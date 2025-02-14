#include "scheduling.h"
#include <stdio.h>
#include <stdlib.h>

int compareArrivalTimeDesc(const void* a, const void* b) {
    Process* processA = (Process*)a;
    Process* processB = (Process*)b;
    return processB->at - processA->at;
}

void fcfs_stack(Process processes[], int n, ProcessResult results[], GrantChartNode** grantChartHead) {
    Stack* stack = createStack();
    int current_time = 0;
    int completed = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    // Sort processes by arrival time in descending order
    qsort(processes, n, sizeof(Process), compareArrivalTimeDesc);


    for (int i = 0; i < n; i++)
    {
        push(stack ,processes[i]);
    }
    
    while (completed < n) {
        if (!isStackEmpty(stack)) {
            Process process = pop(stack);
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

    free(stack);
}