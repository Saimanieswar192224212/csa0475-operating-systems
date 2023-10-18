#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
typedef struct Process {
    int pid;            // Process ID
    int execution_time; // Execution time
} Process;

// Structure to represent a node in the priority queue
typedef struct PriorityQueueNode {
    Process process;
    struct PriorityQueueNode* next;
} PriorityQueueNode;

// Structure to represent a priority queue
typedef struct PriorityQueue {
    PriorityQueueNode* front;
} PriorityQueue;

// Function to create a new process
Process createProcess(int pid, int execution_time) {
    Process process;
    process.pid = pid;
    process.execution_time = execution_time;
    return process;
}

// Function to create a new priority queue node
PriorityQueueNode* createPriorityQueueNode(Process process) {
    PriorityQueueNode* newNode = (PriorityQueueNode*)malloc(sizeof(PriorityQueueNode));
    newNode->process = process;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a process into the priority queue
void insertProcess(PriorityQueue* queue, Process process) {
    PriorityQueueNode* newNode = createPriorityQueueNode(process);

    if (queue->front == NULL || process.execution_time < queue->front->process.execution_time) {
        newNode->next = queue->front;
        queue->front = newNode;
    } else {
        PriorityQueueNode* current = queue->front;

        while (current->next != NULL && process.execution_time >= current->next->process.execution_time) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to extract the process with the smallest execution time from the priority queue
Process extractMin(PriorityQueue* queue) {
    if (queue->front == NULL) {
        Process emptyProcess = createProcess(-1, -1); // Invalid process
        return emptyProcess;
    }

    Process minProcess = queue->front->process;
    PriorityQueueNode* temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    return minProcess;
}

// Function to execute the scheduling
void executeScheduling(Process processes[], int n) {
    PriorityQueue priorityQueue;
    priorityQueue.front = NULL;

    for (int i = 0; i < n; i++) {
        insertProcess(&priorityQueue, processes[i]);
    }

    printf("Scheduling Order:\n");
    while (priorityQueue.front != NULL) {
        Process nextProcess = extractMin(&priorityQueue);
        printf("Process %d (Execution Time: %d)\n", nextProcess.pid, nextProcess.execution_time);
    }
}

int main() {
    // Example processes with execution times
    Process processes[] = {
        createProcess(1, 10),
        createProcess(2, 5),
        createProcess(3, 8),
        createProcess(4, 3),
    };

    int numProcesses = sizeof(processes) / sizeof(processes[0]);

    executeScheduling(processes, numProcesses);

    return 0;
}
