// Flow of the code
//  Input:

// Take inputs for number of processes (np), resources (nr), Allocation matrix, Max matrix, and Available resources.
// Display Data:

// Display the Allocation, Max, and Available matrices.
// Calculate Need:

// Compute the Need matrix as Need[i][j] = Max[i][j] - Allocation[i][j].
// Run Banker's Algorithm:

// Check if each process can complete with available resources.
// If a process can complete, mark it done, add to safe sequence, and release its resources.
// Repeat until all processes complete (safe) or no further progress (deadlock).
// Output:

// Display the safe sequence if the system is safe, or report deadlock if not.

#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int max[MAX_PROCESSES][MAX_RESOURCES], allocation[MAX_PROCESSES][MAX_RESOURCES], need[MAX_PROCESSES][MAX_RESOURCES];
int avail[MAX_RESOURCES];
int np, nr;

void read_matrix(int matrix[MAX_PROCESSES][MAX_RESOURCES])
{
    for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            scanf("%d", &matrix[i][j]);
}

void display_matrix(int matrix[MAX_PROCESSES][MAX_RESOURCES], const char *label)
{
    printf("\n%s:\n", label);
    for (int i = 0; i < np; i++)
    {
        printf(" P%d\t", i);
        for (int j = 0; j < nr; j++)
            printf(" %d", matrix[i][j]);
        printf("\n");
    }
}

void calculate_need()
{
    for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

void banker()
{
    int finish[MAX_PROCESSES] = {0}, safe_seq[MAX_PROCESSES], k = 0;
    int deadlock = 0;

    for (int i = 0; i < np; i++)
    {
        int can_allocate = 1;
        if (!finish[i])
        {
            for (int j = 0; j < nr; j++)
                if (need[i][j] > avail[j])
                {
                    can_allocate = 0;
                    break;
                }
            if (can_allocate)
            {
                finish[i] = 1;
                safe_seq[k++] = i;
                for (int j = 0; j < nr; j++)
                    avail[j] += allocation[i][j];
                i = -1; // Restart process check
            }
        }
    }

    for (int i = 0; i < np; i++)
    {
        if (!finish[i])
        {
            printf("\nThe system is in deadlock.\n");
            deadlock = 1;
            break;
        }
    }

    if (!deadlock)
    {
        printf("\nThe system is in a safe state!\nSafe sequence: ");
        for (int i = 0; i < np; i++)
            printf("P%d ", safe_seq[i]);
        printf("\n");
    }
}

int main()
{
    printf("\nEnter number of processes: ");
    scanf("%d", &np);
    printf("Enter number of resources: ");
    scanf("%d", &nr);

    printf("Enter Allocation matrix:\n");
    read_matrix(allocation);
    printf("Enter Max matrix:\n");
    read_matrix(max);
    printf("Enter Available resources: ");
    for (int j = 0; j < nr; j++)
        scanf("%d", &avail[j]);

    printf("\n****** Entered Data ******\n");
    display_matrix(allocation, "Allocation");
    display_matrix(max, "Max");
    printf("\nAvailable resources:\n");
    for (int i = 0; i < nr; i++)
        printf(" %d", avail[i]);
    printf("\n");

    calculate_need();
    display_matrix(need, "Need");

    banker();
    return 0;
}
