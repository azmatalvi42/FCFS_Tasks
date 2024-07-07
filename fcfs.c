#include <stdio.h>
#define MAX_PROCESSES 50

// Define a struct to represent a process
typedef struct
{
    int process_id;          // Process ID
    int arrival;             // Arrival time of the process
    int burst;               // Burst time (execution time) of the process
} Process;

int main()
{
    FILE *file;
    // Open the file
    file = fopen("sample_in_schedule.txt", "r");
    if (file == NULL)
    {
        
        printf("Error opening file!\n");
        return 1;
    }

    // Create array to store processes read from the file
    Process processes[MAX_PROCESSES];
    int process_count = 0;

    // Read the processes into the array of structs
    // format X (process_id), Y (arrival_time), Z (burst_time)
    while (fscanf(file, "%d,%d,%d",&processes[process_count].process_id, &processes[process_count].arrival, &processes[process_count].burst) == 3)
    {
        process_count++;
    }
    // Close the file after reading
    fclose(file);

    // Variables to keep track of total times
    int current_time = 0;
    int total_turnaround = 0;
    int total_waiting = 0;

    // Print the titles for output
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    

    // Calculate and print completion, turnaround, and waiting times
    for (int i = 0; i < process_count; i++)
    {
        current_time += processes[i].burst;
        int turnaround = current_time- processes[i].arrival;
        int waiting = turnaround - processes[i].burst;
        total_turnaround += turnaround;
        total_waiting += waiting;

        // Print the details of the current process
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival, processes[i].burst, current_time, turnaround, waiting);
    }

    // Calculate average waiting and turnaround times
    double average_waiting = (double)total_waiting / process_count;
    double average_turnaround = (double)total_turnaround / process_count;

    // Print the averages
    
    printf("Average Waiting Time: %.2f\n", average_waiting);
    printf("Average Turnaround Time: %.2f\n", average_turnaround);

    return 0;
}

