#include "scheduling.h"
#include <stdio.h>
#include <assert.h>


void test_rr() {
    Process processes[] = {
        {1, 0, 10},
        {2, 1, 4},
        {3, 2, 5},
        {4, 3, 3}
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    int quantum = 2;
    ProcessResult results[n];
    GrantChartNode* grantChartHead = NULL;

    rr(processes, n, quantum, results, &grantChartHead);

    printGrantChart(grantChartHead);
    printProcessResults(processes, results, n);
}

int main() {
    test_rr();
    printf("All tests passed!\n");
    return 0;
}