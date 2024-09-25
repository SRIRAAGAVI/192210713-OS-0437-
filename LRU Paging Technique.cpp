#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 50

void simulateLRU(int pages[], int n, int frames) {
    int pageFrame[frames];
    int pageFaults = 0;
    int pageHits = 0; // Counter for page hits
    int lastUsed[MAX_PAGES]; // To track the last used time of pages

    // Initialize page frames and last used time
    for (int i = 0; i < frames; i++) {
        pageFrame[i] = -1; // Empty frame
        lastUsed[i] = -1; // Initialize last used time
    }

    for (int i = 0; i < n; i++) {
        int currentPage = pages[i];
        int found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < frames; j++) {
            if (pageFrame[j] == currentPage) {
                found = 1; // Page is found in frame
                pageHits++; // Increment page hits
                lastUsed[j] = i; // Update last used time
                break;
            }
        }

        // If not in frame, a page fault occurs
        if (!found) {
            pageFaults++;

            // Find an empty frame
            int emptyFrame = -1;
            for (int j = 0; j < frames; j++) {
                if (pageFrame[j] == -1) {
                    emptyFrame = j;
                    break;
                }
            }

            // If there is an empty frame, add the page
            if (emptyFrame != -1) {
                pageFrame[emptyFrame] = currentPage;
                lastUsed[emptyFrame] = i; // Mark last used time
            } else {
                // If all frames are full, find the least recently used page
                int lruIndex = 0; // Assume first frame is LRU
                for (int j = 1; j < frames; j++) {
                    if (lastUsed[pageFrame[j]] < lastUsed[pageFrame[lruIndex]]) {
                        lruIndex = j; // Update LRU index
                    }
                }
                // Replace the least recently used page
                pageFrame[lruIndex] = currentPage; // Replace with the new page
                lastUsed[lruIndex] = i; // Update last used time
            }
        }

        // Print the current state of frames
        printf("Frames: ");
        for (int j = 0; j < frames; j++) {
            if (pageFrame[j] != -1) {
                printf("%d ", pageFrame[j]);
            }
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
}

int main() {
    int pages[MAX_PAGES];
    int n, frames;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    simulateLRU(pages, n, frames);

    return 0;
}
