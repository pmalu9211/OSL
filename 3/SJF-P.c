#include <stdio.h>
#include <limits.h>

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int burst_time[], int arrival_time[], int waiting_time[])
{
    // initialize array to keep track of remaining time for each process
    // then calculate the process with the minimum time required
    //      at every second and update it's values
    // increase time everytime and if the process is complete mark it as
    //      done
    // edege casese, if no process yet arrived, time ++
    // check if the process has arrived arrival_time[j] <= time
    //
    int remaining_time[n];
    for (int i = 0; i < n; i++)
        remaining_time[i] = burst_time[i]; // Initialize remaining times with burst times

    int complete = 0, time = 0, min_burst = INT_MAX;
    int shortest = 0, finish_time;
    int found = 0;

    // Loop until all processes are completed
    while (complete != n)
    {
        // Find process with the minimum remaining time among the arrived processes
        for (int j = 0; j < n; j++)
        {
            if (arrival_time[j] <= time && remaining_time[j] < min_burst && remaining_time[j] > 0)
            {
                min_burst = remaining_time[j];
                shortest = j;
                found = 1;
            }
        }

        if (!found) // No process found, increment time
        {
            time++;
            continue;
        }

        // Reduce remaining time of the shortest process
        remaining_time[shortest]--;

        // Update minimum burst time
        min_burst = remaining_time[shortest];
        if (min_burst == 0)
            min_burst = INT_MAX;

        // If a process gets fully executed
        if (remaining_time[shortest] == 0)
        {
            complete++;
            found = 0;

            // Find finish time of current process
            finish_time = time + 1;

            // Calculate waiting time
            waiting_time[shortest] = finish_time - burst_time[shortest] - arrival_time[shortest];

            // If waiting time is negative, set it to zero
            if (waiting_time[shortest] < 0)
                waiting_time[shortest] = 0;
        }
        time++;
    }
}

// Function to calculate turn-around time
void findTurnAroundTime(int processes[], int n, int burst_time[], int waiting_time[], int turn_around_time[])
{
    for (int i = 0; i < n; i++)
        turn_around_time[i] = burst_time[i] + waiting_time[i];
}

// Function to calculate average time
void findAvgTime(int processes[], int n, int burst_time[], int arrival_time[])
{
    int waiting_time[n], turn_around_time[n];
    int total_waiting_time = 0, total_turn_around_time = 0;

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
