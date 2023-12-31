#include <stdio.h>

#define MAX_FRAMES 3

typedef struct {
    int page_number;
    int reference_bit;
} Page;

Page frames[MAX_FRAMES];

void initialize_frames() {
    for (int i = 0; i < MAX_FRAMES; ++i) {
        frames[i].page_number = -1;
        frames[i].reference_bit = 0;
    }
}

void display_frames() {
    for (int i = 0; i < MAX_FRAMES; ++i) {
        if (frames[i].page_number != -1) {
            printf("{%d: (%d)} ", frames[i].page_number, frames[i].reference_bit);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

int is_page_in_frames(int page_number) {
    for (int i = 0; i < MAX_FRAMES; ++i) {
        if (frames[i].page_number == page_number) {
            return 1;
        }
    }
    return 0;
}

void second_chance(int page_number) {
    int i = 0;
    while (1) {
        if (frames[i].reference_bit == 0) {
            frames[i].page_number = page_number;
            frames[i].reference_bit = 1;
            return;
        } else {
            frames[i].reference_bit = 0;
        }
        i = (i + 1) % MAX_FRAMES;
    }
}

void replace_page(int page_number) {
    if (is_page_in_frames(page_number)) {
        printf("Page %d is already in memory.\n", page_number);
    } else {
        printf("Page %d is not in memory. Page replacement needed.\n", page_number);
        second_chance(page_number);
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
