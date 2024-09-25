#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 50

void simulateOptimal(int pages[], int n, int frames) {
    int pageFrame[frames];
    int pageFaults = 0;
    int pageHits = 0; // Counter for page hits

    // Initialize page frames
    for (int i = 0; i < frames; i++) {
        pageFrame[i] = -1; // Empty frame
    }

    for (int i = 0; i < n; i++) {
        int currentPage = pages[i];
        int found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < frames; j++) {
            if (pageFrame[j] == currentPage) {
                found = 1; // Page is found in frame
                pageHits++; // Increment page hits
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
            } else {
                // If all frames are full, find the optimal page to replace
                int farthest = -1;
                int lruIndex = 0; // Initialize index to replace

                for (int j = 0; j < frames; j++) {
                    int k;
                    // Find when the current page frame will be used again
                    for (k = i + 1; k < n; k++) {
                        if (pageFrame[j] == pages[k]) {
                            break;
                        }
                    }
                    // If the page is not found, replace it
                    if (k == n) {
                        lruIndex = j;
                        break;
                    }
                    // If it is found, check how far in the future it is used
                    if (k > farthest) {
                        farthest = k;
                        lruIndex = j; // Update the index to replace
                    }
                }

                // Replace the selected page
                pageFrame[lruIndex] = currentPage; // Replace with the new page
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

    simulateOptimal(pages, n, frames);

    return 0;
}
