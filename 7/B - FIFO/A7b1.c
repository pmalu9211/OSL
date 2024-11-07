#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define N 100

int main()
{
    int fd_send, fd_receive;
    char *fifo1 = "fifo1";
    char *fifo2 = "fifo2";
    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);
    char input[N], output[N];
    while (1)
    {
        fd_send = open(fifo1, O_WRONLY);
        printf("fileDescription : fd_send : %d", fd_send);
        printf("\nEnter a sentence: ");
        fgets(input, N, stdin);
        write(fd_send, input, strlen(input) + 1);
        close(fd_send);
        fd_receive = open(fifo2, O_RDONLY);
        printf("fileDescription : fd_send : %d", fd_receive);
        read(fd_receive, output, sizeof(output));
        printf("Processed Output from User2: %s\n", output);
        close(fd_receive);
    }
    return 0;
}
