// scheduling.c

#include <stdio.h>
#include "scheduling.h"
#include <stdlib.h>

int compareArrivalTime(const void* a, const void* b) {
    Process* processA = (Process*)a;
    Process* processB = (Process*)b;
    return processA->at - processB->at;
}


void printProcessResults(Process processes[], ProcessResult results[], int n) {
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].at, processes[i].bt, results[i].ct, results[i].tat, results[i].wt);
    }
}


