// scheduling.h

#ifndef SCHEDULING_H
#define SCHEDULING_H



typedef struct
{
    int pid;
    int at; //arrival time
    int bt; //burst time
} Process;

typedef struct {
    int pid;
    int ct; //completion time
    int tat; //turnaround time
    int wt; //waiting time

} ProcessResult;


// Linked list node for GrantChart
typedef struct GrantChartNode {
    int pid;
    int start_time;
    int end_time;
    struct GrantChartNode* next;
} GrantChartNode;

typedef struct QueueNode {
    Process process;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

typedef struct StackNode {
    Process process;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;



// Function declarations for Queue
Queue* createQueue();
void enqueue(Queue* queue, Process process);
Process dequeue(Queue* queue);
int isQueueEmpty(Queue* queue);

Stack *createStack();
void push(Stack *stack, Process process);
Process pop(Stack *stack);
int isStackEmpty(Stack *stack);

// Function declarations for GrantChart linked list
GrantChartNode* createGrantChartNode(int pid, int start_time, int end_time);
void appendGrantChartNode(GrantChartNode** head, int pid, int start_time, int end_time);
void printGrantChart(GrantChartNode* head);
void printProcessResults(Process processes[], ProcessResult results[], int n); // Function declarations
void fcfs(Process processes[], int n, ProcessResult results[], GrantChartNode** grantChartHead);
void sjf(Process processes[], int n, ProcessResult results[], GrantChartNode** grantChartHead);
void rr(Process processes[], int n, int quantum, ProcessResult results[], GrantChartNode** grantChartHead);
void fcfs_stack(Process processes[], int n, ProcessResult results[], GrantChartNode **grantChartHead);
int compareArrivalTime(const void *a, const void *b);

#endif // SCHEDULING_H
