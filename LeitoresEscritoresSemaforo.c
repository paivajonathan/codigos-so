#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_LEITORES 3
#define NUM_ESCRITORES 2

int dados_compartilhados = 0;
sem_t mutex, leitores_sem;

// Função do leitor
void *leitor(void *arg) {
    int identificador = *((int *)arg);

    // Garante que os leitores esperem até que todos os escritores tenham terminado
    sem_wait(&leitores_sem);
    sem_post(&leitores_sem);

    // Início da seção crítica para leitura
    sem_wait(&mutex);
    printf("Leitor %d está lendo: %d\n", identificador, dados_compartilhados);
    sem_post(&mutex);
    // Fim da seção crítica para leitura

    sleep(1);

    pthread_exit(NULL);
}

// Função do escritor
void *escritor(void *arg) {
    int identificador = *((int *)arg);

    // Início da seção crítica para escrita
    sem_wait(&mutex);
    dados_compartilhados++;
    printf("Escritor %d está escrevendo: %d\n", identificador, dados_compartilhados);
    sem_post(&mutex);
    // Fim da seção crítica para escrita

    sleep(1);

    pthread_exit(NULL);
}

int main() {
    pthread_t leitores[NUM_LEITORES], escritores[NUM_ESCRITORES];
    int i;

    // Inicialização dos semáforos
    sem_init(&mutex, 0, 1);
    sem_init(&leitores_sem, 0, 1);

    // Criação das threads de leitores
    for (i = 0; i < NUM_LEITORES; i++) {
        pthread_create(&leitores[i], NULL, leitor, (void *)&i);
    }

    // Criação das threads de escritores
    for (i = 0; i < NUM_ESCRITORES; i++) {
        pthread_create(&escritores[i], NULL, escritor, (void *)&i);
    }

    // Aguarda as threads de leitores terminarem
    for (i = 0; i < NUM_LEITORES; i++) {
        pthread_join(leitores[i], NULL);
    }

    // Aguarda as threads de escritores terminarem
    for (i = 0; i < NUM_ESCRITORES; i++) {
        pthread_join(escritores[i], NULL);
    }

    // Destroi os semáforos
    sem_destroy(&mutex);
    sem_destroy(&leitores_sem);

    return 0;
}
