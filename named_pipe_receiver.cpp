#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hPipe;
    char buffer[100];
    
    // Open the named pipe
    hPipe = CreateFile(
        TEXT("\\\\.\\pipe\\MyNamedPipe"),   // Pipe name
        GENERIC_READ,                        // Read access
        0,                                   // No sharing
        NULL,                                // Default security attributes
        OPEN_EXISTING,                       // Opens existing pipe
        0,                                   // Default attributes
        NULL);                               // No template file

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Error opening named pipe: %d\n", GetLastError());
        return 1;
    }

    // Read from the pipe
    DWORD bytesRead;
    if (!ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL)) {
        printf("Error reading from pipe: %d\n", GetLastError());
    } else {
        printf("Received message: %s\n", buffer);
    }

    CloseHandle(hPipe);
    return 0;
}

