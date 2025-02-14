#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduling.h"

void loadProcessesFromFile(const char* filename, Process** processes, int* n) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    int capacity = 10;
    *processes = (Process*)malloc(capacity * sizeof(Process));
    *n = 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int pid, at, bt;

        if (sscanf(line, "%d %d %d", &pid, &at, &bt) != 3) {
            fprintf(stderr, "Invalid line format: %s", line);
            _Exit(EXIT_FAILURE);
        }

        if (at < 0 || bt < 0) {
            fprintf(stderr, "Invalid process times (arrival/burst cannot be negative): %s", line);
            _Exit(EXIT_FAILURE);
        }

        (*processes)[*n].pid = pid;
        (*processes)[*n].at = at;
        (*processes)[*n].bt = bt;
        (*n)++;

        if (*n >= capacity) {
            capacity *= 2;
            *processes = (Process*)realloc(*processes, capacity * sizeof(Process));
            if (!*processes) {
                perror("Failed to reallocate memory");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);
}


void printAverageTimes(ProcessResult results[], int n) {
    double totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        totalTAT += results[i].tat;
        totalWT += results[i].wt;
    }
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time: %.2f\n", totalWT / n);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <inputfile> -s|-f\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    int runSJF = 0, runFCFS = 0;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0) {
            runSJF = 1;
        } else if (strcmp(argv[i], "-f") == 0) {
            runFCFS = 1;
        }
    }

    if (!runSJF && !runFCFS) {
        fprintf(stderr, "Specify at least one algorithm: -s for SJF, -f for FCFS\n");
        return EXIT_FAILURE;
    }

    Process* processes;
    int n;
    loadProcessesFromFile(filename, &processes, &n);

    if (runSJF) {
        ProcessResult results[n];
        GrantChartNode* grantChartHead = NULL;
        sjf(processes, n, results, &grantChartHead);
        printf("SJF Grant Chart:\n");
        printGrantChart(grantChartHead);
        printf("SJF Results:\n");
        printProcessResults(processes, results, n);
        printAverageTimes(results, n);
    }

    if (runFCFS) {
        ProcessResult results[n];
        GrantChartNode* grantChartHead = NULL;
        fcfs_stack(processes, n, results, &grantChartHead);
        printf("FCFS Grant Chart:\n");
        printGrantChart(grantChartHead);
        printf("FCFS Results:\n");
        printProcessResults(processes, results, n);        
        printAverageTimes(results, n);
    }

    if (runSJF && runFCFS) {
        ProcessResult sjfResults[n], fcfsResults[n];
        GrantChartNode* sjfGrantChartHead = NULL;
        GrantChartNode* fcfsGrantChartHead = NULL;

        sjf(processes, n, sjfResults, &sjfGrantChartHead);
        fcfs(processes, n, fcfsResults, &fcfsGrantChartHead);

        double sjfTotalTAT = 0, sjfTotalWT = 0;
        double fcfsTotalTAT = 0, fcfsTotalWT = 0;

        for (int i = 0; i < n; i++) {
            sjfTotalTAT += sjfResults[i].tat;
            sjfTotalWT += sjfResults[i].wt;
            fcfsTotalTAT += fcfsResults[i].tat;
            fcfsTotalWT += fcfsResults[i].wt;
        }

        double sjfAvgTAT = sjfTotalTAT / n;
        double sjfAvgWT = sjfTotalWT / n;
        double fcfsAvgTAT = fcfsTotalTAT / n;
        double fcfsAvgWT = fcfsTotalWT / n;

        printf("Comparison of Average Times:\n");
        printf("SJF - Average Turnaround Time: %.2f, Average Waiting Time: %.2f\n", sjfAvgTAT, sjfAvgWT);
        printf("FCFS - Average Turnaround Time: %.2f, Average Waiting Time: %.2f\n", fcfsAvgTAT, fcfsAvgWT);
    }

    free(processes);
    return 0;
}