#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX 20

void bubble_sort(int array[], int n);
void insertion_sort(int array[], int n);

int main()
{
  int pid;
  int i, arr_bubble[MAX], arr_ins[MAX];
  int num_bubble, num_ins;

  printf("\nENTER THE NUMBER OF ELEMENTS FOR bubble : \n");
  scanf("%d", &num_bubble);
  printf("\nENTER THE ELEMENTS : ");
  for (i = 0; i < num_bubble; i++)
    scanf("%d", &arr_bubble[i]);

  printf("\nENTER THE NUMBER OF ELEMENTS FOR Insertion : \n");
  scanf("%d", &num_ins);
  printf("\nENTER THE ELEMENTS : ");
  for (i = 0; i < num_ins; i++)
    scanf("%d", &arr_ins[i]);

  pid = fork();
  if (pid == 0)
  {
    printf("\n I am in child...%d", getpid());
    printf("\n My parent's Id is...%d", getppid());
    sleep(5);
    bubble_sort(arr_bubble, num_bubble);
    printf("\nAFTER PERFORMING THE BUBBLE SORT : \n");
    for (int i = 0; i < num_bubble; i++)
      printf("%d\t", arr_bubble[i]);
    printf("\n");
    printf("\nI (CHILD) COMPLETED MY EXECUTION.\n");
  }
  else
  {
    printf("\n My parent's Id is...%d", getppid());
    printf("\n I am in Parent...%d", getpid());
    printf("\n Insertion Sorting the array");
    insertion_sort(arr_ins, num_ins);
    printf("\nAFTER PERFORMING THE INSERTION SORT : \n");
    for (int i = 0; i < num_ins; i++)
      printf("%d\t", arr_ins[i]);
    printf("\n");
    printf("I Will be wating for my child to finish... \n");
    wait(NULL);
    exit(0);
    printf("\nCHILD COMPLETED ITS EXECUTION , NOW I (PARENT) AM FREE TO EXIT.\n");
  }
  return (0);
}

void bubble_sort(int array[], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (array[j] > array[j + 1])
      {
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

// Insertion Sort Function
void insertion_sort(int array[], int n)
{
  for (int i = 1; i < n; i++)
  {
    int key = array[i];
    int j = i - 1;
    while (j >= 0 && array[j] > key)
    {
      array[j + 1] = array[j];
      j--;
    }
    array[j + 1] = key;
  }
}
