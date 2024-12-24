#include <stdio.h>
#include "scheduling.h"
#include <stdlib.h>


int compareByBurstTime(const void* a, const void* b) {
    Process* p1 = (Process*)a;
    Process* p2 = (Process*)b;
    return p1->bt - p2->bt;
}

void sjf(Process processes[], int n, ProcessResult results[], GrantChartNode** grantChartHead) {
    int currentTime = 0;
    int completed = 0;
    int i;
    int* isCompleted = (int*)calloc(n, sizeof(int));

    qsort(processes, n, sizeof(Process), compareByBurstTime);

    while (completed != n) {
        int idx = -1;
        int min_bt = 1000000;

        for (i = 0; i < n; i++) {
            if (processes[i].at <= currentTime && !isCompleted[i]) {
                if (processes[i].bt < min_bt) {
                    min_bt = processes[i].bt;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            currentTime += processes[idx].bt;
            results[idx].pid = processes[idx].pid;
            results[idx].ct = currentTime;
            results[idx].tat = results[idx].ct - processes[idx].at;
            results[idx].wt = results[idx].tat - processes[idx].bt;
            isCompleted[idx] = 1;
            completed++;

            appendGrantChartNode(grantChartHead, processes[idx].pid, currentTime - processes[idx].bt, currentTime);
        } else {
            currentTime++;
        }
    }

    free(isCompleted);
}