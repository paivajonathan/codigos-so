#include <stdio.h>

#define MAX_FRAMES 3

typedef struct {
    int pageNumber;
    int referenceBit;
} Page;

Page frames[MAX_FRAMES];

void initialize_frames() {
    for (int i = 0; i < MAX_FRAMES; ++i) {
        frames[i].pageNumber = -1;
        frames[i].referenceBit = 0;
    }
}

void display_frames() {
    for (int i = 0; i < MAX_FRAMES; ++i) {
        if (frames[i].pageNumber != -1) {
            printf("{%d: (%d)} ", frames[i].pageNumber, frames[i].referenceBit);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

int is_page_in_frames(int pageNumber) {
    for (int i = 0; i < MAX_FRAMES; ++i) {
        if (frames[i].pageNumber == pageNumber) {
            return 1;
        }
    }
    return 0;
}

void second_chance(int pageNumber) {
    int i = 0;
    while (1) {
        if (frames[i].pageNumber == -1) {
            frames[i].pageNumber = pageNumber;
            frames[i].referenceBit = 1;
            return;
        
        } 
        
        {4 (0), 5 (0), -1 (0)}
        
    }

    /*if (frames[i].referenceBit == 0) {
            frames[i].pageNumber = pageNumber;
            frames[i].referenceBit = 1;
            return;
        } else {
            frames[i].referenceBit = 0;
        }
        i = (i + 1) % MAX_FRAMES;*/
}

void replace_page(int pageNumber) {
    if (is_page_in_frames(pageNumber)) {
        printf("Page %d is already in memory.\n", pageNumber);
    } else {
        printf("Page %d is not in memory. Page replacement needed.\n", pageNumber);
        second_chance(pageNumber);
    }
}

int main() {
    initialize_frames();

    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int numPages = sizeof(pages) / sizeof(pages[0]);

    for (int i = 0; i < numPages; ++i) {
        printf("Page request: %d\n", pages[i]);
        replace_page(pages[i]);
        display_frames();
        printf("\n");
    }

    return 0;
}
