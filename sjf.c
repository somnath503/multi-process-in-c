#include <stdio.h>

typedef struct {
    int burst_time;
    int arrival_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    char process_id[12];  // Increased size to 12 to handle larger process IDs like "P1000000000"
} Process;

// Function to calculate times for each process
void calculate_times(Process processes[], int n) {
    int start_time = 0;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    // Sorting processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Print header for process details
    printf("\n%-12s%-16s%-16s%-20s%-20s%-20s\n", "Process ID", "Arrival Time", "Burst Time", "Completion Time", "Turnaround Time", "Waiting Time");

    // Calculate and print times for each process
    for (int i = 0; i < n; i++) {
        // If CPU is idle before the current process starts
        if (processes[i].arrival_time > start_time) {
            printf("Idle         %-16d%-16d%-20d%-20d%-20d\n", start_time, processes[i].arrival_time, 0, 0, 0);
            start_time = processes[i].arrival_time; // Set start time to process arrival time
        }

        // Process runs and completes
        processes[i].completion_time = start_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        // Add to total times
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;

        // Print process information
        printf("%-12s%-16d%-16d%-20d%-20d%-20d\n", processes[i].process_id,
            processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time,
            processes[i].turnaround_time, processes[i].waiting_time);

        // Update start time for next process
        start_time = processes[i].completion_time;
    }

    // Calculate and print average times
    double avg_turnaround_time = (double)total_turnaround_time / n;
    double avg_waiting_time = (double)total_waiting_time / n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);

    // Print the Gantt Chart for processes
    printf("\nGantt Chart:\n");
    printf("Time: ");
    for (int i = 0; i < n; i++) {
        printf("%-5d", processes[i].completion_time); // Print end time of each process
    }
    printf("\n");

    printf("Process ID: ");
    for (int i = 0; i < n; i++) {
        printf("%-5s", processes[i].process_id); // Print process ID
    }
    printf("\n");
}

// Function to print scheduling metrics (length, throughput, CPU idleness)
void print_metrics(Process processes[], int n) {
    int total_burst_time = 0;
    int total_idle_time = 0;
    int scheduling_length;

    // Calculate total burst time
    for (int i = 0; i < n; i++) {
        total_burst_time += processes[i].burst_time;
    }

    // Calculate total idle time
    for (int i = 1; i < n; i++) {
        // Calculate idle time between processes
        if (processes[i].arrival_time > processes[i - 1].completion_time) {
            total_idle_time += processes[i].arrival_time - processes[i - 1].completion_time;
        }
    }

    // Scheduling length is the time taken from the first process arrival to the last process completion
    scheduling_length = processes[n - 1].completion_time - processes[0].arrival_time;
    double cpu_idleness = ((double)total_idle_time / scheduling_length) * 100;
    double throughput = (double)n / scheduling_length;

    // Print scheduling metrics
    printf("\nScheduling Metrics:\n");
    printf("Scheduling Length: %-10d\n", scheduling_length);
    printf("Throughput: %-10.2f processes/unit time\n", throughput);
    printf("CPU Idleness: %-10.2f%%\n", cpu_idleness);
}

int main() {
    int n;

    // Taking input for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Taking input for each process's arrival time and burst time
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        snprintf(processes[i].process_id, sizeof(processes[i].process_id), "P%d", i + 1);  // Assign process ID
    }

    // Calculate and print the times for each process
    calculate_times(processes, n);

    // Print scheduling metrics
    print_metrics(processes, n);

    return 0;
}
