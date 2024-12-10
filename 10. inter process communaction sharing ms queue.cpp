#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 1024

int main() {
    HANDLE hPipe;
    char message[BUFFER_SIZE];

    // Create a named pipe
    hPipe = CreateNamedPipe(
        "\\\\.\\pipe\\MessageQueue", // Pipe name
        PIPE_ACCESS_OUTBOUND,       // Outbound access only
        PIPE_TYPE_MESSAGE | PIPE_WAIT, // Message-type pipe and blocking mode
        1,                          // Max instances
        BUFFER_SIZE,                // Output buffer size
        BUFFER_SIZE,                // Input buffer size
        0,                          // Default timeout
        NULL);                      // Default security attributes

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Error creating named pipe. Error code: %lu\n", GetLastError());
        return 1;
    }

    printf("Waiting for the receiver to connect...\n");
    ConnectNamedPipe(hPipe, NULL); // Wait for the receiver to connect

    printf("Enter a message to send: ");
    fgets(message, BUFFER_SIZE, stdin);

    // Write the message to the pipe
    DWORD bytesWritten;
    if (!WriteFile(hPipe, message, strlen(message) + 1, &bytesWritten, NULL)) {
        printf("Error writing to the pipe. Error code: %lu\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Message sent successfully.\n");

    // Close the pipe
    CloseHandle(hPipe);
    return 0;
}

