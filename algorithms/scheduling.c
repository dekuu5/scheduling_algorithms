// scheduling.c

#include <stdio.h>
#include "scheduling.h"

void fcfs(Process processes[], int n, ProcessResult results[]) {
    int waiting_time = 0, turnaround_time = 0, completion_time = 0;

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            waiting_time += processes[i - 1].burst_time;
        }
        completion_time = waiting_time + processes[i].burst_time;
        turnaround_time = completion_time - processes[i].arrival_time;

        results[i].process_id = processes[i].process_id;
        results[i].waiting_time = waiting_time;
        results[i].turnaround_time = turnaround_time;
    }
}

void sjf(Process processes[], int n, ProcessResult results[]) {
    int visited[n], completed = 0, current_time = 0;
    for (int i = 0; i < n; i++) visited[i] = 0;

    while (completed < n) {
        int shortest = -1, min_burst_time = 1e9;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && processes[i].arrival_time <= current_time &&
                processes[i].burst_time < min_burst_time) {
                min_burst_time = processes[i].burst_time;
                shortest = i;
            }
        }

        if (shortest != -1) {
            visited[shortest] = 1;
            current_time += processes[shortest].burst_time;

            results[completed].process_id = processes[shortest].process_id;
            results[completed].waiting_time = current_time - processes[shortest].burst_time - processes[shortest].arrival_time;
            results[completed].turnaround_time = current_time - processes[shortest].arrival_time;

            completed++;
        } else {
            current_time++;
        }
    }
}


void rr(Process processes[], int n, int quantum, ProcessResult results[]) {
    int remaining_burst[n];
    int waiting_time[n];
    int turnaround_time[n];
    int completed = 0, current_time = 0;

    for (int i = 0; i < n; i++) remaining_burst[i] = processes[i].burst_time;

    while (completed < n) {
        int idle = 1;

        for (int i = 0; i < n; i++) {
            if (remaining_burst[i] > 0 && processes[i].arrival_time <= current_time) {
                idle = 0;
                if (remaining_burst[i] > quantum) {
                    current_time += quantum;
                    remaining_burst[i] -= quantum;
                } else {
                    current_time += remaining_burst[i];
                    waiting_time[i] = current_time - processes[i].arrival_time - processes[i].burst_time;
                    turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
                    remaining_burst[i] = 0;
                    completed++;
                }
            }
        }

        if (idle) current_time++;
    }

    for (int i = 0; i < n; i++) {
        results[i].process_id = processes[i].process_id;
        results[i].waiting_time = waiting_time[i];
        results[i].turnaround_time = turnaround_time[i];
    }
}

