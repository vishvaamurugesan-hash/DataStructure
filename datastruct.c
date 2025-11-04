#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define NAME_LEN 50

// Task structure
typedef struct {
    char name[NAME_LEN];
    int deadline; // Smaller deadline = higher priority (sooner task)
} Task;

// Heap (priority queue)
Task heap[MAX_TASKS];
int heapSize = 0;

// Function to swap two tasks
void swap(Task *a, Task *b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

// Insert task into min-heap
void insertTask(char *name, int deadline) {
    if (heapSize >= MAX_TASKS) {
        printf("Heap is full. Cannot add more tasks.\n");
        return;
    }

    Task newTask;
    strcpy(newTask.name, name);
    newTask.deadline = deadline;

    heap[heapSize] = newTask;
    int i = heapSize;
    heapSize++;

    // Heapify Up
    while (i > 0 && heap[(i - 1) / 2].deadline > heap[i].deadline) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    printf("✅ Task '%s' added successfully!\n", name);
}

// Extract (remove) the most urgent task (earliest deadline)
void removeNextTask() {
    if (heapSize <= 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("⏰ Next Task: %s (Deadline: %d)\n", heap[0].name, heap[0].deadline);

    heap[0] = heap[heapSize - 1];
    heapSize--;

    // Heapify Down
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heapSize && heap[left].deadline < heap[smallest].deadline)
            smallest = left;
        if (right < heapSize && heap[right].deadline < heap[smallest].deadline)
            smallest = right;

        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

// Display all tasks in heap order
void displayTasks() {
    if (heapSize == 0) {
        printf("No tasks scheduled.\n");
        return;
    }

    printf("\n📋 Task List (by priority):\n");
    printf("--------------------------------------\n");
    for (int i = 0; i < heapSize; i++) {
        printf("%d. %s (Deadline: %d)\n", i + 1, heap[i].name, heap[i].deadline);
    }
    printf("--------------------------------------\n");
}

int main() {
    int choice;
    char name[NAME_LEN];
    int deadline;

    printf("========================================\n");
    printf("   🕒 TASK REMINDER & SCHEDULER SYSTEM  \n");
    printf("   Using Heap / Priority Queue in C     \n");
    printf("========================================\n");

    while (1) {
        printf("\n1. Add Task\n2. View All Tasks\n3. Remove Next Task\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // to clear newline after number input

        switch (choice) {
            case 1:
                printf("Enter task name: ");
                fgets(name, NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0'; // remove newline
                printf("Enter deadline (e.g., time in minutes or priority number): ");
                scanf("%d", &deadline);
                insertTask(name, deadline);
                break;

            case 2:
                displayTasks();
                break;

            case 3:
                removeNextTask();
                break;

            case 4:
                printf("Exiting... Stay organized and healthy! 💪\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
