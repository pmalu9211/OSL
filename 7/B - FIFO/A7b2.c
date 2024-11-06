// User2: Processor and Responder Process

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define N 100 // Maximum buffer size for received and processed data

int main()
{
    int fd_receive, fd_send; // File descriptors for FIFO pipes used for receiving and sending data
    FILE *file;              // File pointer for saving processed results

    // Paths for the two named FIFO pipes
    char *fifo1 = "fifo1"; // FIFO used for receiving data from User1
    char *fifo2 = "fifo2"; // FIFO used for sending data back to User1

    // Create the FIFOs if they don't already exist
    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    char received[N], processed[N]; // Buffers for received input and processed output

    while (1)
    {
        // Step 1: Open fifo1 in read-only mode to receive data from User1
        fd_receive = open(fifo1, O_RDONLY);
        read(fd_receive, received, N); // Read data from User1
        close(fd_receive);             // Close the pipe after reading

        printf("Received from User1: %s\n", received);

        // Step 2: Count characters, words, and sentences in the received input
        int characters = 0, words = 0, sentences = 0;
        for (int i = 0; received[i] != '\0'; i++)
        {
            characters++; // Count every character
            if (received[i] == ' ')
                words++; // Count spaces to estimate word count
            if (received[i] == '.')
                sentences++; // Count periods for sentence count
        }

        // Prepare the result string with calculated counts
        snprintf(processed, N, "Characters: %d\tWords: %d\tSentences: %d",
                 characters, words + 1, sentences); // Add 1 to word count to account for the last word

        // Step 3: Save results to a text file for persistence
        file = fopen("result.txt", "w");
        fprintf(file, "%s", processed); // Write processed counts to file
        fclose(file);                   // Close file after writing

        // Step 4: Read the result from the file and send back via fifo2
        file = fopen("result.txt", "r");
        fread(processed, sizeof(char), N, file); // Load processed data from file
        fclose(file);                            // Close file after reading

        // Step 5: Send the processed data back to User1 through fifo2
        fd_send = open(fifo2, O_WRONLY);
        write(fd_send, processed, strlen(processed) + 1); // Send processed data
        close(fd_send);                                   // Close the pipe after writing
    }

    return 0;
}
