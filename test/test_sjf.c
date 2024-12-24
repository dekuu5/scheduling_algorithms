#include <stdio.h>
#include <assert.h>
#include "../algorithms/sjf.c"

void test_sjf() {
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

    sjf(processes, n, results, &grantChartHead);

    printGrantChart(grantChartHead);
    printProcessResults(processes, results, n);
    printf("All test cases passed!\n");
}

int main() {
    test_sjf();
    return 0;
}