#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hPipe;
    char buffer[100];
    
    // Create a named pipe
    hPipe = CreateNamedPipe(
        TEXT("\\\\.\\pipe\\MyNamedPipe"),   // Pipe name
        PIPE_ACCESS_OUTBOUND,                // Write access
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // Message type pipe
        1,                                   // Max. instances
        1024,                                // Output buffer size
        1024,                                // Input buffer size
        0,                                   // Client time-out
        NULL);                               // Default security attributes

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Error creating named pipe: %d\n", GetLastError());
        return 1;
    }

    printf("Waiting for a client to connect...\n");
    if (ConnectNamedPipe(hPipe, NULL) == FALSE) {
        printf("Error connecting to named pipe: %d\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Client connected. Enter a message to send: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Write to the pipe
    DWORD bytesWritten;
    if (!WriteFile(hPipe, buffer, strlen(buffer) + 1, &bytesWritten, NULL)) {
        printf("Error writing to pipe: %d\n", GetLastError());
    } else {
        printf("Message sent: %s\n", buffer);
    }

    CloseHandle(hPipe);
    return 0;
}

