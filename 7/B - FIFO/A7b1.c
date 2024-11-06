// User1: Sender and Receiver Process

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define N 100 // Maximum buffer size for input/output

int main()
{
    int fd_send, fd_receive; // File descriptors for FIFO pipes used for sending and receiving data

    // Paths for the two named FIFO pipes
    char *fifo1 = "fifo1"; // FIFO used for sending data to User2
    char *fifo2 = "fifo2"; // FIFO used for receiving data from User2

    // Create the FIFOs if they don't already exist
    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    char input[N], output[N]; // Buffers for input (sending) and output (receiving)

    while (1)
    {
        // Step 1: Open fifo1 in write-only mode to send user input to User2
        fd_send = open(fifo1, O_WRONLY);
        printf("fileDescription : fd_send : %d", fd_send);

        // Prompt for user input and write it to fifo1
        printf("\nEnter a sentence: ");
        fgets(input, N, stdin);                   // Read input from the user
        write(fd_send, input, strlen(input) + 1); // Send input to User2
        close(fd_send);                           // Close the pipe after writing

        // Step 2: Open fifo2 in read-only mode to receive processed data from User2
        fd_receive = open(fifo2, O_RDONLY);
        printf("fileDescription : fd_send : %d", fd_receive);

        // Read processed output from fifo2 and display it
        read(fd_receive, output, sizeof(output));
        printf("Processed Output from User2: %s\n", output);
        close(fd_receive); // Close the pipe after reading
    }

    return 0;
}
