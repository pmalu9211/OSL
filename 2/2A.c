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
    printf("Start\n");
  printf("Current pid %d \n",getpid());
  pid = fork();
  sleep(6);
  if (pid == 0)
  {
    printf("\n I am in child...%d", getpid());
    printf("\n My parent's Id is...%d", getppid());
    sleep(5);
  }
  else
  {
      sleep(10);
    printf("\n I am in Parent...%d", getpid());
    printf("\n Insertion Sorting the array");
    wait(NULL);
    sleep(5);
    exit(0);
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
