#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define DISK_SIZE 200

// Calculate distances from head to each track
void calculateDistances(int *tracks, int *distances, int n, int head)
{
    for (int i = 0; i < n; i++)
        distances[i] = abs(head - tracks[i]);
}

// Find track with the minimum distance from head
int findClosestTrack(int *distances, int *accessed, int n)
{
    int minDist = __INT_MAX__, minIndex = -1;
    for (int i = 0; i < n; i++)
    {
        if (!accessed[i] && distances[i] < minDist)
        {
            minDist = distances[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void SSTF(int *tracks, int head, int n)
{
    int distances[n], accessed[n], seekSequence[n + 1], seekCount = 0;
    memset(accessed, 0, sizeof(accessed));

    for (int i = 0; i < n; i++)
    {
        seekSequence[i] = head;
        calculateDistances(tracks, distances, n, head);
        int closest = findClosestTrack(distances, accessed, n);
        accessed[closest] = 1;
        seekCount += distances[closest];
        head = tracks[closest];
    }
    seekSequence[n] = head;

    printf("Total seek operations: %d\nSeek sequence: ", seekCount);
    for (int i = 0; i <= n; i++)
        printf("%d ", seekSequence[i]);
    printf("\n");
}

void bubble_sort(int arr[], int n)
{
    // Outer loop for number of passes
    for (int i = 0; i < n - 1; i++)
    {
        // Inner loop for comparisons in each pass
        for (int j = 0; j < n - i - 1; j++)
        {
            // Compare adjacent elements
            if (arr[j] > arr[j + 1])
            {
                // Swap if they are in wrong order
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void SCAN(int *tracks, int head, int n, int direction)
{

    int left[n], right[n], l = 0, r = 0, seekSequence[n + 2], seekCount = 0;
    seekSequence[0] = head;

    for (int i = 0; i < n; i++)
    {
        if (tracks[i] < head)
        {
            left[l++] = tracks[i];
        }
        else
        {
            right[r++] = tracks[i];
        }
    }
    bubble_sort(left, l);
    bubble_sort(right, r);

    int idx = 1;
    if (direction == 0) // move left
    {
        for (int i = l - 1; i >= 0; i--)
        {
            seekCount += abs(left[i] - head);
            head = left[i];
            seekSequence[idx++] = head;
        }
        seekCount += abs(head - 0);
        head = 0;
        seekSequence[idx++] = 0;
        for (int i = 0; i < r; i++)
        {
            seekCount += abs(right[i] - head);
            head = right[i];
            seekSequence[idx++] = head;
        }
    }
    else
    {
        for (int i = 0; i < r; i++)
        {
            seekCount += abs(right[i] - head);
            head = right[i];
            seekSequence[idx++] = head;
        }
        seekCount += abs(head - DISK_SIZE + 1);
        head = DISK_SIZE - 1;
        seekSequence[idx++] = head;

        for (int i = l - 1; i >= 0; i--)
        {
            seekCount += abs(left[i] - head);
            head = left[i];
            seekSequence[idx++] = head;
        }
    }

    printf("Total seek operations: %d\nSeek sequence: ", seekCount);
    for (int i = 0; i < idx; i++)
        printf("%d ", seekSequence[i]);
    printf("\n");
}

void CLOOK(int *tracks, int head, int n)
{
    int left[n], right[n], l = 0, r = 0, seekSequence[n + 1], seekCount = 0;

    for (int i = 0; i < n; i++)
    {
        if (tracks[i] < head)
            left[l++] = tracks[i];
        else
            right[r++] = tracks[i];
    }
    bubble_sort(left, l);
    bubble_sort(right, r);
    seekSequence[0] = head;

    int idx = 1;
    for (int i = 0; i < r; i++)
    {
        seekCount += abs(right[i] - head);
        head = right[i];
        seekSequence[idx++] = head;
    }
    seekCount += abs(head - left[0]);
    head = left[0];
    for (int i = 0; i < l; i++)
    {
        seekCount += abs(left[i] - head);
        head = left[i];
        seekSequence[idx++] = head;
    }

    printf("Total seek operations: %d\nSeek sequence: ", seekCount);
    for (int i = 0; i < idx; i++)
        printf("%d ", seekSequence[i]);
    printf("\n");
}

int main()
{
    int n, head, choice, direction;
    printf("Enter number of tracks: ");
    scanf("%d", &n);
    int tracks[n];
    printf("Enter the tracks:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &tracks[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Choose the algorithm:\n1. SSTF\n2. SCAN\n3. CLOOK\n");
    scanf("%d", &choice);

    if (choice == 2)
    {
        printf("Enter direction (0 for left, 1 for right): ");
        scanf("%d", &direction);
    }

    switch (choice)
    {
    case 1:
        SSTF(tracks, head, n);
        break;
    case 2:
        SCAN(tracks, head, n, direction);
        break;
    case 3:
        CLOOK(tracks, head, n);
        break;
    default:
        printf("Invalid choice.\n");
    }

    return 0;
}

// int idx = 0;
// if (direction == 0)
// {
//     // Moving left first
//     // Go through all tracks on the left side of the initial head position
//     for (int i = l - 1; i >= 0; i--)
//     {
//         int track = left[i];
//         seekSequence[idx] = track;      // Add track to seek sequence
//         seekCount += abs(head - track); // Calculate distance from head to track
//         head = track;                   // Move head to this track
//         idx++;                          // Move to next position in the sequence
//     }

//     // After reaching the leftmost track, move to the end of the disk (DISK_SIZE - 1)
//     seekCount += abs(head - (DISK_SIZE - 1));
//     head = DISK_SIZE - 1; // Update head position to the end of the disk

//     // Now move right, servicing tracks on the right side
//     for (int i = 0; i < r; i++)
//     {
//         int track = right[i];
//         seekSequence[idx] = track;      // Add track to sequence
//         seekCount += abs(head - track); // Distance from head to track
//         head = track;                   // Move head to track
//         idx++;                          // Update sequence index
//     }
// }
// else
// {
//     // Moving right first
//     // Go through all tracks on the right side of the initial head position
//     for (int i = 0; i < r; i++)
//     {
//         int track = right[i];
//         seekSequence[idx] = track;      // Add track to sequence
//         seekCount += abs(head - track); // Calculate distance
//         head = track;                   // Move head to this track
//         idx++;                          // Next sequence position
//     }

//     // After reaching the rightmost track, move to the start of the disk (0)
//     seekCount += abs(head - 0);
//     head = 0; // Update head to the start of the disk

//     // Now move left, servicing tracks on the left side
//     for (int i = l - 1; i >= 0; i--)
//     {
//         int track = left[i];
//         seekSequence[idx] = track;      // Add track to sequence
//         seekCount += abs(head - track); // Calculate distance
//         head = track;                   // Move head to track
//         idx++;                          // Next in sequence
//     }
// }