#include <CUnit/Basic.h>
#include "../algorithms/scheduling.h"

void test_fcfs() {
    // Test data
    Process processes[] = {
        {1, 0, 4},  // PID 1, arrival time 0, burst time 4
        {2, 1, 3},  // PID 2, arrival time 1, burst time 3
        {3, 2, 1},  // PID 3, arrival time 2, burst time 1
    };
    int n = 3;
    
    ProcessResult results[n];
    GrantChartNode* grantChartHead = NULL;
    
    // Run FCFS algorithm
    fcfs(processes, n, results, &grantChartHead);
    
    // Verify results
    CU_ASSERT_EQUAL(results[0].pid, 1);
    CU_ASSERT_EQUAL(results[0].ct, 4);   // Completion time
    CU_ASSERT_EQUAL(results[0].tat, 4);  // Turnaround time
    CU_ASSERT_EQUAL(results[0].wt, 0);   // Waiting time
    
    CU_ASSERT_EQUAL(results[1].pid, 2);
    CU_ASSERT_EQUAL(results[1].ct, 7);   
    CU_ASSERT_EQUAL(results[1].tat, 6);  
    CU_ASSERT_EQUAL(results[1].wt, 3);   
    
    CU_ASSERT_EQUAL(results[2].pid, 3);
    CU_ASSERT_EQUAL(results[2].ct, 8);   
    CU_ASSERT_EQUAL(results[2].tat, 6);  
    CU_ASSERT_EQUAL(results[2].wt, 5);   
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("FCFS_Test_Suite", 0, 0);
    CU_add_test(suite, "test_fcfs", test_fcfs);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return CU_get_error();
}