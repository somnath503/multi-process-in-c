#include<stdio.h>

struct process {
    int Id;
    int Arrival_Time;
    int Brust_Time;
    int Completion_Time;
    int Turn_Around_Time;
    int Waiting_Time;
};

void Find_Completion_Time(struct process proc[], int n) {
    // First process starts execution immediately after its arrival
    proc[0].Completion_Time = proc[0].Arrival_Time + proc[0].Brust_Time;

    // For the subsequent processes
    for (int i = 1; i < n; i++) {
        // If the next process arrives after the previous process completes, the CPU stays idle
        if (proc[i].Arrival_Time > proc[i - 1].Completion_Time) {
            proc[i].Completion_Time = proc[i].Arrival_Time + proc[i].Brust_Time;
        } else {
            proc[i].Completion_Time = proc[i - 1].Completion_Time + proc[i].Brust_Time;
        }
    }
}

void TAT_AND_WT(struct process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].Turn_Around_Time = proc[i].Completion_Time - proc[i].Arrival_Time;
        proc[i].Waiting_Time = proc[i].Turn_Around_Time - proc[i].Brust_Time;
    }
}

void Calculate_Scheduling_Length_and_Idleness(struct process proc[], int n, int *idle_time, float *L) {
    int max_completion_time = proc[0].Completion_Time;
    int min_arrival_time = proc[0].Arrival_Time;

    *idle_time = 0;

    // Find the max completion time and min arrival time, also calculate idle time
    for (int i = 0; i < n; i++) {
        if (proc[i].Completion_Time > max_completion_time) {
            max_completion_time = proc[i].Completion_Time;
        }
        if (proc[i].Arrival_Time < min_arrival_time) {
            min_arrival_time = proc[i].Arrival_Time;
        }

        // Check idle time between processes
        if (i > 0 && proc[i].Arrival_Time > proc[i - 1].Completion_Time) {
            *idle_time += proc[i].Arrival_Time - proc[i - 1].Completion_Time;
        }
    }

    // Calculate scheduling length
    *L = max_completion_time - min_arrival_time;

    // Handle CPU idle time at the start
    if (proc[0].Arrival_Time > 0) {
        *L = max_completion_time - proc[0].Arrival_Time;
    }
}

void Average_Time(struct process proc[], int n) {
    int Total_TAT = 0, Total_WT = 0;
    for (int i = 0; i < n; i++) {
        Total_TAT += proc[i].Turn_Around_Time;
        Total_WT += proc[i].Waiting_Time;
    }
    printf("\nAverage Turnaround Time: %.2f", (float)Total_TAT / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)Total_WT / n);
}

void Throughput_and_Idleness(int n, float L, int idle_time) {
    // Throughput
    float throughput = (float)n / L;
    printf("\nThroughput: %.2f", throughput);

    // Idle time percentage
    float idle_percentage = (float)idle_time / L * 100;
    printf("\nIdle Time Percentage: %.2f%%\n", idle_percentage);
}

void Display_process(struct process proc[], int n) {
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time");
    for (int i = 0; i < n; i++) {
        printf("\nP%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", proc[i].Id, proc[i].Arrival_Time, proc[i].Brust_Time, proc[i].Completion_Time, proc[i].Turn_Around_Time, proc[i].Waiting_Time);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process proc[n];

    // Input details for processes
    for (int i = 0; i < n; i++) {
        proc[i].Id = i + 1;
        printf("\nEnter the Arrival and Burst time for Process P%d: ", i + 1);
        scanf("%d %d", &proc[i].Arrival_Time, &proc[i].Brust_Time);
    }

    // Sort the processes by their arrival time (if not already sorted)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].Arrival_Time > proc[j].Arrival_Time) {
                struct process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    Find_Completion_Time(proc, n);
    TAT_AND_WT(proc, n);

    int idle_time = 0;
    float L = 0;
    Calculate_Scheduling_Length_and_Idleness(proc, n, &idle_time, &L);

    Display_process(proc, n);
    Average_Time(proc, n);
    Throughput_and_Idleness(n, L, idle_time);

    return 0;
}
