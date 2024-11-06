#include <stdio.h>
#include <stdlib.h>

// Function to perform binary search
int binary_search(int *arr, int size, int target)
{
	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		// Calculate middle point
		int mid = (left + right) / 2;

		// If element is found at middle point
		if (arr[mid] == target)
			return 1; // Found

		// If element is greater than mid, ignore left half
		if (arr[mid] < target)
			left = mid + 1;

		// If element is smaller than mid, ignore right half
		else
			right = mid - 1;
	}

	return 0; // Not found
}

int main(int argc, char *argv[])
{

	int size = argc; // argc is the size of the arguments array
	int arr[size];	 // the final array after connversion of string to ints
	for (int i = 0; i < size; i++)
	{
		arr[i] = atoi(argv[i]); // conveting strings to int
	}
	printf("What is the number you want to search : ");
	int target;
	scanf("%d", &target);
	if (binary_search(arr, size, target))
	{
		printf("Target found");
	}
	else
	{
		printf("target not found");
	}
	return 0;
	// int arr[15];	 // Array to store numbers
	// int target;		 // Number to search for
	// int size = argc; // Size of array (excluding program name)
	// printf("argc = %d\n", argc);

	// // Convert command line arguments to integers
	// for (int i = 0; i < size; i++)
	// {
	// 	printf("argv[%d] = %s\n", i, argv[i]);
	// 	arr[i] = atoi(argv[i]);
	// }

	// // Get number to search
	// printf("\nEnter number to search: ");
	// scanf("%d", &target);

	// // Perform binary search
	// if (binary_search(arr, size, target))
	// 	printf("\nNumber found!\n");
	// else
	// 	printf("\nNumber not found!\n");

	// return 0;
}