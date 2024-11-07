#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define N 100
int main()
{
    int fd_receive, fd_send;
    FILE *file;

    char *fifo1 = "fifo1";
    char *fifo2 = "fifo2";

    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    char received[N], processed[N];

    while (1)
    {
        fd_receive = open(fifo1, O_RDONLY);
        read(fd_receive, received, N);
        close(fd_receive);

        printf("Received from User1: %s\n", received);

        int characters = 0, words = 0, sentences = 0;
        for (int i = 0; received[i] != '\0'; i++)
        {
            characters++;
            if (received[i] == ' ')
                words++;
            if (received[i] == '.')
                sentences++;
        }

        sprintf(processed, "Characters: %d\tWords: %d\tSentences: %d",
                characters, words + 1, sentences);

        file = fopen("result.txt", "w");
        fprintf(file, "%s", processed);
        fclose(file);

        file = fopen("result.txt", "r");
        fread(processed, sizeof(char), N, file);
        fclose(file);

        fd_send = open(fifo2, O_WRONLY);
        write(fd_send, processed, strlen(processed) + 1);
        close(fd_send);
    }

    return 0;
}
