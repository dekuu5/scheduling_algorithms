#include "../algorithms/scheduling.h"
#include <stdlib.h>
void test_fcfs() {
    // Test data
    Process processes[] = {
        {4, 9, 9},
        {3, 7, 1},
        {1, 0, 1},
        {2, 1, 9},
        {8, 1, 2},
        {99, 1, 3},
        {44, 1, 4},
        
          
    };
    int n = 7;
    
    ProcessResult results[n];
    GrantChartNode* grantChartHead = NULL;
    
    // Run FCFS algorithm
    fcfs(processes, n, results, &grantChartHead);

    // Verify results
    printGrantChart(grantChartHead);
    printProcessResults(processes,results, n);

}

int main() {
    test_fcfs();
    return 0;
}