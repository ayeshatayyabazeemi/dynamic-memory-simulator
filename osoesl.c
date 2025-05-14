#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int pid;
    int arrival_time;
    int size;
    int end_time;
    int allocated; // 0: not allocated, 1: allocated, 2: finished
} Process;

typedef struct Block {
    int start;
    int size;
    int free; // 1: free, 0: occupied
    int pid;  // If occupied, which process
    struct Block* next;
} Block;

Block* memory = NULL;
int total_memory = 0;

// Create new memory block
Block* create_block(int start, int size, int free, int pid) {
    Block* block = (Block*)malloc(sizeof(Block));
    block->start = start;
    block->size = size;
    block->free = free;
    block->pid = pid;
    block->next = NULL;
    return block;
}

// Merge adjacent free blocks
void merge_free_blocks() {
    Block* current = memory;
    while (current != NULL && current->next != NULL) {
        if (current->free && current->next->free) {
            current->size += current->next->size;
            Block* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

// Allocate process to memory
int allocate_process(Process* process) {
    Block* current = memory;
    while (current != NULL) {
        if (current->free && current->size >= process->size) {
            if (current->size == process->size) {
                current->free = 0;
                current->pid = process->pid;
            } else {
                Block* new_block = create_block(current->start + process->size, current->size - process->size, 1, -1);
                new_block->next = current->next;
                current->next = new_block;
                current->size = process->size;
                current->free = 0;
                current->pid = process->pid;
            }
            process->allocated = 1;
            printf("Allocated Process %d at time %d\n", process->pid, process->arrival_time);
            return 1;
        }
        current = current->next;
    }
    printf("Failed to allocate Process %d at time %d (Not enough memory)\n", process->pid, process->arrival_time);
    return 0;
}

// Deallocate memory of a process
void deallocate_process(Process* process, int current_time) {
    Block* current = memory;
    while (current != NULL) {
        if (!current->free && current->pid == process->pid) {
            current->free = 1;
            current->pid = -1;
            printf("Deallocated Process %d at time %d\n", process->pid, current_time);
            merge_free_blocks();
            break;
        }
        current = current->next;
    }
}

// Display current memory state
void display_memory_state(int time) {
    printf("\nMemory State at time %d:\n", time);
    Block* current = memory;
    while (current != NULL) {
        if (current->free)
            printf("[Free Block] Start: %dMB, Size: %dMB\n", current->start, current->size);
        else
            printf("[Process %d] Start: %dMB, Size: %dMB\n", current->pid, current->start, current->size);
        current = current->next;
    }
    printf("--------------------------------------\n");
}

int main() {
    printf("Welcome to Dynamic Memory Management Simulation\n");
    printf("Enter total size of Main Memory (in MB): ");
    scanf("%d", &total_memory);

    memory = create_block(0, total_memory, 1, -1);

    Process* processes = NULL;
    int process_count = 0;
    int total_size = 0;
    int max_size = 0;
    int min_size = 1000000; // Large initial value

    printf("Enter process details (arrival_time size end_time), enter -1 to stop:\n");

    while (1) {
        int arrival, size, end;
        printf("Process %d: ", process_count + 1);
        scanf("%d", &arrival);
        if (arrival == -1) break;
        scanf("%d%d", &size, &end);

        processes = realloc(processes, (process_count + 1) * sizeof(Process));
        processes[process_count].pid = process_count + 1;
        processes[process_count].arrival_time = arrival;
        processes[process_count].size = size;
        processes[process_count].end_time = end;
        processes[process_count].allocated = 0;

        // Track max and min process sizes entered by the user
        total_size += size;
        if (size > max_size) max_size = size;
        if (size < min_size) min_size = size;

        process_count++;
    }

    int current_time = 0;
    int finished = 0;

    while (finished < process_count) {
        int memory_changed = 0;

        // Allocate newly arrived processes
        for (int i = 0; i < process_count; i++) {
            if (processes[i].arrival_time == current_time && processes[i].allocated == 0) {
                if (allocate_process(&processes[i])) {
                    memory_changed = 1;
                }
            }
        }

        // Deallocate finished processes
        for (int i = 0; i < process_count; i++) {
            if (processes[i].end_time == current_time && processes[i].allocated == 1) {
                deallocate_process(&processes[i], current_time);
                processes[i].allocated = 2; // Mark as finished
                finished++;
                memory_changed = 1;
            }
        }

        // Retry allocating failed processes
        for (int i = 0; i < process_count; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].allocated == 0) {
                if (allocate_process(&processes[i])) {
                    memory_changed = 1;
                }
            }
        }

        if (memory_changed) {
            display_memory_state(current_time);
        }

        current_time++;

        if (current_time > 10000) {
            printf("Simulation stopped due to time limit.\n");
            break;
        }
    }

    printf("Simulation Complete!\n");

    printf("\n--- Process Size Statistics ---\n");
    printf("Max Process Size Entered: %dMB\n", max_size);
    printf("Min Process Size Entered: %dMB\n", min_size);
    if (process_count > 0) {
        double avg_size = (double)total_size / process_count;
        printf("Average Process Size Entered: %.2fMB\n", avg_size);
    }

    // Free memory
    while (memory != NULL) {
        Block* temp = memory;
        memory = memory->next;
        free(temp);
    }
    free(processes);
    return 0;
}
