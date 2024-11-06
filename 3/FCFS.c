#include <stdio.h>

// Function to swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes by arrival time
void sortByArrivalTime(int processes[], int n, int burst_time[], int arrival_time[])
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arrival_time[j] > arrival_time[j + 1])
            {
                swap(&arrival_time[j], &arrival_time[j + 1]);
                swap(&burst_time[j], &burst_time[j + 1]);
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int burst_time[], int arrival_time[], int waiting_time[])
{
    int time_of_starting_execution[n];
    time_of_starting_execution[0] = arrival_time[0]; // Start at the first process arrival time
    waiting_time[0] = 0;                             // First process has no waiting time

    // Calculate service time and waiting time for each process
    for (int i = 1; i < n; i++)
    {
        // Service time is the time when the previous process completes
        time_of_starting_execution[i] = time_of_starting_execution[i - 1] + burst_time[i - 1];

        // Waiting time = Service time - Arrival time
        waiting_time[i] = time_of_starting_execution[i] - arrival_time[i];

        // If waiting time is negative, set it to zero
        if (waiting_time[i] < 0)
        {
            waiting_time[i] = 0;
            time_of_starting_execution[i] = arrival_time[i]; // Reset service time if idle until arrival
        }
    }
}

// Function to calculate turn-around time
void findTurnAroundTime(int processes[], int n, int burst_time[], int waiting_time[], int turn_around_time[])
{
    // Calculating turn-around time by adding burst_time and waiting_time
    for (int i = 0; i < n; i++)
    {
        turn_around_time[i] = burst_time[i] + waiting_time[i];
    }
}

// Function to calculate average time
void findAvgTime(int processes[], int n, int burst_time[], int arrival_time[])
{
    int waiting_time[n], turn_around_time[n];
    int total_waiting_time = 0, total_turn_around_time = 0;

    // Sort processes by arrival time
    sortByArrivalTime(processes, n, burst_time, arrival_time);

    // Calculate waiting time for all processes
    findWaitingTime(processes, n, burst_time, arrival_time, waiting_time);

    // Calculate turn-around time for all processes
    findTurnAroundTime(processes, n, burst_time, waiting_time, turn_around_time);

    // Display processes along with all details
    printf("Processes   Arrival Time   Burst Time   Waiting Time   Turn Around Time\n");

    // Calculate total waiting time and total turn-around time
    for (int i = 0; i < n; i++)
    {
        total_waiting_time += waiting_time[i];
        total_turn_around_time += turn_around_time[i];
        printf("    %d ", processes[i]);
        printf("\t\t%d ", arrival_time[i]);
        printf("\t\t%d ", burst_time[i]);
        printf("\t\t%d", waiting_time[i]);
        printf("\t\t%d\n", turn_around_time[i]);
    }

    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turn_around_time = (float)total_turn_around_time / n;

    printf("Average Waiting Time = %f\n", avg_waiting_time);
    printf("Average Turn Around Time = %f\n", avg_turn_around_time);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];
    int arrival_time[n];

    // Assign process IDs and input burst and arrival times
    for (int i = 0; i < n; i++)
    {
        processes[i] = i + 1; // Process ID starts from 1
        printf("Enter the arrival time for process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    findAvgTime(processes, n, burst_time, arrival_time);
    return 0;
}
