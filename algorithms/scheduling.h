// scheduling.h

#ifndef SCHEDULING_H
#define SCHEDULING_H

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
} Process;

typedef struct {
    int process_id;
    int waiting_time;
    int turnaround_time;
} ProcessResult;

// Function declarations
void fcfs(Process processes[], int n, ProcessResult results[]);
void sjf(Process processes[], int n, ProcessResult results[]);
void rr(Process processes[], int n, int quantum, ProcessResult results[]);

#endif // SCHEDULING_H
