#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to sort array using bubble sort
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

int main()
{
	int arr[15];	// Array to store numbers
	int n;			// Size of array
	char *args[16]; // Array for command line arguments (size + 1 for NULL)
	char str[10];	// Temporary string for number conversion

	// Get array size from user
	printf("\nEnter the size of array: ");
	scanf("%d", &n);

	// Get array elements from user
	printf("Enter the elements: ");
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	// Print parent process ID
	printf("\nParent process ID: %d\n", getpid());

	// Sort the array
	printf("\nSorting array...\n");
	bubble_sort(arr, n);

	// Create child process
	int pid = fork();

	if (pid == 0) // Child process
	{
		// convert the array to string
		for (int i = 0; i < n; i++)
		{
			sprintf(str, "%d", arr[i]);
			args[i] = malloc(10);
			strcpy(args[i], str);
		}
		args[n] = NULL;
		for (int i = 0; i < n; i++)
		{
			printf("args : %s\n", args[i]);
		}
		// execve("./search", args, NULL);

		execve("./reverse", args, NULL);

		// last elemnt should be NULL
		// pass it to the execv

		// printf("\nChild process ID: %d\n", getpid());

		// // Convert integers to strings for execve
		// for (int i = 0; i < n; i++)
		// {
		// 	// Let's say arr[0] = 123

		// 	// Step 1: sprintf
		// 	sprintf(str, "%d", arr[i]);
		// 	// str now contains: {'1', '2', '3', '\0'}

		// 	// Step 2: malloc
		// 	args[i] = malloc(10);
		// 	// Allocates 10 bytes: [  |  |  |  |  |  |  |  |  |  ]

		// 	// Step 3: strcpy
		// 	strcpy(args[i], str);
		// 	// args[0] now points to: ['1', '2', '3', '\0', |  |  |  |  |  |  ]
		// }
		// args[n] = NULL; // NULL terminate the arguments array

		// // Execute the search program
		// printf("\nExecuting search program...\n");
		// execve("./search", args, NULL);
	}
	else if (pid > 0) // Parent process
	{
		printf("\nParent waiting for child...\n");
		wait(NULL); // Wait for child to complete
		printf("\nParent process completed\n");
	}

	return 0;
}