// scheduling.c

#include <stdio.h>
#include "scheduling.h"
#include <stdlib.h>




void printProcessResults(Process processes[], ProcessResult results[], int n) {
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].at, processes[i].bt, results[i].ct, results[i].tat, results[i].wt);
    }
}


void rr(Process processes[], int n, int quantum, ProcessResult results[], GrantChartNode** grantChartHead) {
    // Round Robin (RR) scheduling algorithm implementation
}

