#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 5
int occupied_frames = 0;
int page_faults = 0;

typedef struct {
    int page_number;
    bool reference_bit;  // Bit de referência para o algoritmo de segunda chance
} Page;

Page frames[MAX_FRAMES];

// Inicializa os frames da memória
void initialize_frames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i].page_number = -1;  // Página inválida inicialmente
        frames[i].reference_bit = false;  // Inicia o bit de referência como false
    }
}

// Exibe o estado atual dos frames
void display_frames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i].page_number != -1) {
            printf("{%d: (%d)} ", frames[i].page_number, frames[i].reference_bit);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

// Verifica se a página já está na memória
bool is_page_in_frames(int page_number) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i].page_number == page_number) {
            frames[i].reference_bit = true;  // Marca a página como referenciada
            return true;
        }
    }
    return false;
}

// Implementa o algoritmo de segunda chance para substituição de página
void second_chance(int page_number) {
    if (occupied_frames < MAX_FRAMES) {
        for (int i = 0; i < MAX_FRAMES; i++) {
            if (frames[i].page_number == -1) {
                frames[i].page_number = page_number;
                frames[i].reference_bit = false;  // Inicia o bit de referência como false
                occupied_frames++;
                return;
            }
        }
    } else {
        int i = 0;
        while (true) {
            if (!frames[i].reference_bit) {
                frames[i].page_number = page_number;
                frames[i].reference_bit = false;  // Inicia o bit de referência como false
                return;
            } else {
                frames[i].reference_bit = false;
            }
            i = (i + 1) % MAX_FRAMES;  // Incrementa o índice circularmente
        }
    }
}

// Substitui a página se necessário
void replace_page(int page_number) {
    if (is_page_in_frames(page_number)) {
        printf("Page %d is already in memory.\n", page_number);
    } else {
        printf("Page %d is not in memory. Page replacement needed.\n", page_number);
        second_chance(page_number);
        page_faults++;
    }
}

int main(void) {
    initialize_frames();

    int pages[] = {2, 1, 4, 6, 2, 2, 1, 7};
    int numPages = sizeof(pages) / sizeof(pages[0]);

    for (int i = 0; i < numPages; i++) {
        printf("Page request: %d\n", pages[i]);
        replace_page(pages[i]);
        display_frames();
        printf("\n");
    }

    printf("Total page faults: %d\n", page_faults);

    return 0;
}
