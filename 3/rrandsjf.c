#include <stdio.h>

int choice, num_processes;
int is_finished[10], proc_id[10], arrivalTime[10], burst[10], wait[10], turnaround[10];
int remaining_time[10], time = 0;
float total_waiting_time = 0, total_turnaround_time = 0;

void getInput()
{
    printf("\nEnter number of processes: ");
    scanf("%d", &num_processes);
    for (int i = 0; i < num_processes; i++)
    {
        proc_id[i] = i;
        printf("\nEnter Burst Time for Process %d: ", proc_id[i]);
        scanf("%d", &burst[i]);
        remaining_time[i] = burst[i];
        printf("Enter arrivalTime Time for Process %d: ", proc_id[i]);
        scanf("%d", &arrivalTime[i]);
    }
}

void showMenu()
{
    printf("\n***** MENU *****\n1. Round Robin\n2. SJF Preemptive\n3. Exit\nChoice: ");
    scanf("%d", &choice);
}

void displayResults()
{
    printf("\nProcess\tA.T.\tB.T.\tW.T.\tT.A.T.");
    for (int i = 0; i < num_processes; i++)
    {
        printf("\nP%d\t%d\t%d\t%d\t%d", proc_id[i], arrivalTime[i], burst[i], wait[i], turnaround[i]);
    }
    printf("\n\nAverage Waiting Time: %.2f", total_waiting_time / num_processes);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time / num_processes);
}

void swap(int i, int j)
{
    int temp;
    temp = burst[i];
    burst[i] = burst[j];
    burst[j] = temp;
    temp = remaining_time[i];
    remaining_time[i] = remaining_time[j];
    remaining_time[j] = temp;
    temp = arrivalTime[i];
    arrivalTime[i] = arrivalTime[j];
    arrivalTime[j] = temp;
    temp = proc_id[i];
    proc_id[i] = proc_id[j];
    proc_id[j] = temp;
}

void roundRobin()
{
    int time_quantum, active_processes = num_processes;
    getInput();
    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    for (int currentProcess = 0; active_processes > 0;)
    {
        if (!is_finished[currentProcess] && arrivalTime[currentProcess] <= time)
        {
            if (remaining_time[currentProcess] <= time_quantum)
            {
                time += remaining_time[currentProcess];
                wait[currentProcess] = time - burst[currentProcess] - arrivalTime[currentProcess];
                turnaround[currentProcess] = wait[currentProcess] + burst[currentProcess];
                total_waiting_time += wait[currentProcess];
                total_turnaround_time += turnaround[currentProcess];
                remaining_time[currentProcess] = 0;
                is_finished[currentProcess] = 1;
                active_processes--;
                printf("P%d ", proc_id[currentProcess]);
            }
            else
            {
                remaining_time[currentProcess] -= time_quantum;
                time += time_quantum;
                printf("P%d ", proc_id[currentProcess]);
            }
        }
        currentProcess = (currentProcess + 1) % num_processes;
    }
    displayResults();
}

void sortProcesses()
{
    for (int i = 0; i < num_processes - 1; i++)
    {
        for (int j = i + 1; j < num_processes; j++)
        {
            if (remaining_time[i] > remaining_time[j])
            {
                swap(i, j);
            }
        }
    }
}

void sjfPreemptive()
{
    int active_processes = num_processes;
    getInput();
    while (active_processes > 0)
    {
        sortProcesses();
        for (int i = 0; i < num_processes; i++)
        {
            if (!is_finished[i] && arrivalTime[i] <= time)
            {
                printf("P%d ", proc_id[i]);
                time++;
                remaining_time[i]--;
                if (remaining_time[i] == 0)
                {
                    is_finished[i] = 1;
                    active_processes--;
                    turnaround[i] = time - arrivalTime[i];
                    wait[i] = turnaround[i] - burst[i];
                    total_waiting_time += wait[i];
                    total_turnaround_time += turnaround[i];
                }
                break;
            }
        }
    }
    displxayResults();
}

int main()
{
    while (1)
    {
        showMenu();
        switch (choice)
        {
        case 1:
            roundRobin();
            break;
        case 2:
            sjfPreemptive();
            break;
        case 3:
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
