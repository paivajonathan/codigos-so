#include <stdio.h>

#define MAX_PAGES 10

typedef struct {
    int page_number;
    int reference_bit;
} Page;

Page memory[MAX_PAGES];

void initialize_memory() {
    for (int i = 0; i < MAX_PAGES; i++) {
        memory[i].page_number = -1;  // Indica que a página não está ocupada
        memory[i].reference_bit = 0; // Inicializa o bit de referência como 0
    }
}

int second_chance() {
    while (1) {
        for (int i = 0; i < MAX_PAGES; i++) {
            if (memory[i].page_number == -1 || memory[i].reference_bit == 0) {
                return i; // Encontrou uma página para substituir
            } else {
                memory[i].reference_bit = 0; // Zera o bit de referência
            }
        }
    }
}

void append_page(int page_number) {
    int pageIndexToReplace = second_chance();
    memory[pageIndexToReplace].page_number = page_number;
}

void print_memory() {
    for (int i = 0; i < MAX_PAGES; i++) {
        if (memory[i].page_number != -1) {
            printf("Page %d (Ref: %d)\n", memory[i].page_number, memory[i].reference_bit);
        } else {
            printf("Empty\n");
        }
    }
    printf("\n");
}

int main() {
    initialize_memory();

    // Simula a referência a algumas páginas
    append_page(10);
    append_page(20);
    // replace_page(2, 3);

    // printf("Memória Inicial:\n");
    // print_memory();

    // // Simula a necessidade de substituir uma página
    // int pageIndexToReplace = second_chance();
    // replace_page(pageIndexToReplace, 4);

    // printf("Memória Após Substituição:\n");
    // print_memory();

    print_memory();

    return 0;
}
