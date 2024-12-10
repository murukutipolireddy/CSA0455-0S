#include <stdio.h>
#include <windows.h>

#define SHM_SIZE 1024  // Shared memory size
#define SHM_NAME "SharedMemoryExample"

int main() {
    // Create a shared memory object
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use paging file
        NULL,                    // Default security
        PAGE_READWRITE,          // Read/write access
        0,                       // Maximum object size (high-order DWORD)
        SHM_SIZE,                // Maximum object size (low-order DWORD)
        SHM_NAME);               // Name of the mapping object

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%lu).\n", GetLastError());
        return 1;
    }

    // Map the shared memory object to the process's address space
    char *sharedMemory = (char *)MapViewOfFile(
        hMapFile,                // Handle to the map object
        FILE_MAP_ALL_ACCESS,     // Read/write access
        0, 0, SHM_SIZE);         // Offset and size of the view

    if (sharedMemory == NULL) {
        printf("Could not map view of file (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Write a message to the shared memory
    printf("Enter a message to write into shared memory: ");
    fgets(sharedMemory, SHM_SIZE, stdin);

    printf("Message written to shared memory.\n");

    // Unmap and close the shared memory
    UnmapViewOfFile(sharedMemory);
    CloseHandle(hMapFile);

    return 0;
}

