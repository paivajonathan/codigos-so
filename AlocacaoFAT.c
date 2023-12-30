#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLUSTER_SIZE 4096 //Define o tamanho do cluster
#define FAT_ENTRY_SIZE 4 
#define MAX_CLUSTERS 10 //Quantidade máxima de "clusters"

typedef struct {
    int value;
    int next_cluster;
} FatEntry;

FatEntry fat[MAX_CLUSTERS];

void initialize_fat() {
    // Inicializando o gerador de números aleatórios com base no tempo atual
    srand((unsigned int)time(NULL));

    // Inicializando a tabela FAT com uma cadeia contínua de clusters
    int i;
    for (i = 0; i < MAX_CLUSTERS - 1; i++) {
        fat[i].value = rand() % 100;  // Valor aleatório entre 0 e 99
        fat[i].next_cluster = i + 1;  // Próximo cluster na cadeia
    }

    // O último cluster na cadeia aponta para -1
    fat[MAX_CLUSTERS - 1].value = rand() % 100;
    fat[MAX_CLUSTERS - 1].next_cluster = -1;
}

int main() {
    initialize_fat();

    // Imprimindo a tabela FAT inicializada
    printf("Inicialização da tabela FAT:\n");
    int i;
    for (i = 0; i < MAX_CLUSTERS; i++) {
        printf("Cluster %d: Valor: %d, Próximo Cluster: %d\n", i, fat[i].value, fat[i].next_cluster);
    }
    printf("\n");

    return 0;
}

