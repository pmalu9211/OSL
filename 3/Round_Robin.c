#include <stdio.h>

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int burst_time[], int arrival_time[], int waiting_time[], int quantum)
{
  int remaining_time[n];
  for (int i = 0; i < n; i++)
    remaining_time[i] = burst_time[i]; // Initialize remaining times with burst times

  int time = 0;      // Current time
  int completed = 0; // Count of completed processes

  while (completed < n)
  {
    int done = 1; // Flag to check if any process ran in this cycle

    for (int i = 0; i < n; i++)
    {
      // Check if the process has arrived and is yet to complete
      if (arrival_time[i] <= time && remaining_time[i] > 0)
      {
        done = 0; // Process ran in this cycle

        // If remaining time is less than or equal to quantum, finish it
        if (remaining_time[i] <= quantum)
        {
          time += remaining_time[i];
          waiting_time[i] = time - arrival_time[i] - burst_time[i];
          remaining_time[i] = 0; // Process is complete
          completed++;           // Increase count of completed processes
        }
        else // Execute for a quantum time slice
        {
          time += quantum;
          remaining_time[i] -= quantum;
        }
      }
    }

    // If no process was executed, increment time to when the next process arrives
    if (done)
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
void findAvgTime(int processes[], int n, int burst_time[], int arrival_time[], int quantum)
{
  int waiting_time[n], turn_around_time[n];
  int total_waiting_time = 0, total_turn_around_time = 0;

  // Calculate waiting time for all processes
  findWaitingTime(processes, n, burst_time, arrival_time, waiting_time, quantum);

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
  int n, quantum;
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

  printf("Enter the time quantum: ");
  scanf("%d", &quantum);

  findAvgTime(processes, n, burst_time, arrival_time, quantum);
  return 0;
}
