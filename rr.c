#include<stdio.h>

int main()
{
    int process_count, current_process, total_processes, current_time, remaining_processes, process_executed_flag = 0, time_quantum;
    int total_waiting_time = 0, total_turnaround_time = 0;
    int arrival_time[10], burst_time[10], remaining_time[10];
    int completion_time[10];
    int idle_time = 0, last_execution_time = 0;

    printf("Enter Total Number of Processes:	");
    scanf("%d", &total_processes);
    
    remaining_processes = total_processes;

    for(process_count = 0; process_count < total_processes; process_count++)
    {
        printf("Enter Arrival Time and Burst Time for Process %d: ", process_count + 1);
        scanf("%d %d", &arrival_time[process_count], &burst_time[process_count]);
        remaining_time[process_count] = burst_time[process_count];
    }

    printf("Enter Time Quantum:	");
    scanf("%d", &time_quantum);

    printf("\n\nProcess\t| Turnaround Time \t| Waiting Time\n\n");

    for(current_time = 0, current_process = 0; remaining_processes != 0; )
    {
        if(remaining_time[current_process] <= time_quantum && remaining_time[current_process] > 0)
        {
            // Calculate idle time if necessary
            if (current_time < arrival_time[current_process]) {
                idle_time += arrival_time[current_process] - current_time;
                current_time = arrival_time[current_process];
            }

            current_time += remaining_time[current_process];
            remaining_time[current_process] = 0;
            process_executed_flag = 1;
        }
        else if(remaining_time[current_process] > 0)
        {
            // Calculate idle time if necessary
            if (current_time < arrival_time[current_process]) {
                idle_time += arrival_time[current_process] - current_time;
                current_time = arrival_time[current_process];
            }

            remaining_time[current_process] -= time_quantum;
            current_time += time_quantum;
        }

        if(remaining_time[current_process] == 0 && process_executed_flag == 1)
        {
            remaining_processes--;
            completion_time[current_process] = current_time;
            printf("P[%d]\t|\t%d\t\t|\t%d\n", current_process + 1, current_time - arrival_time[current_process], current_time - arrival_time[current_process] - burst_time[current_process]);
            total_waiting_time += current_time - arrival_time[current_process] - burst_time[current_process];
            total_turnaround_time += current_time - arrival_time[current_process];
            process_executed_flag = 0;
        }

        if(current_process == total_processes - 1)
            current_process = 0;
        else if(arrival_time[current_process + 1] <= current_time)
            current_process++;
        else
            current_process = 0;
    }

    int scheduling_length = completion_time[0];
    for (int i = 1; i < total_processes; i++) {
        if (completion_time[i] > scheduling_length)
            scheduling_length = completion_time[i];
    }
    scheduling_length -= arrival_time[0];

    double throughput = (double) total_processes / scheduling_length;

    printf("\nAverage Waiting Time = %.2f\n", total_waiting_time * 1.0 / total_processes);
    printf("Average Turnaround Time = %.2f\n", total_turnaround_time * 1.0 / total_processes);
    printf("Scheduling Length = %d\n", scheduling_length);
    printf("Throughput = %.2f processes/unit time\n", throughput);
    printf("Idle Time = %d\n", idle_time);

    return 0;
}
