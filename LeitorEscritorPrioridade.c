#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define NUM_LEITORES 3
#define NUM_ESCRITORES 2


int dados_compartilhados = 0;
sem_t mutex, leitores_sem, escritores_sem;
int leitores_ativos = 0;


void *leitor(void *arg) {
    int identificador = *((int *)arg);


    // Início da seção crítica para leitores
    sem_wait(&leitores_sem);
    leitores_ativos++;
    if (leitores_ativos == 1) {
        sem_wait(&escritores_sem); // Bloqueia escritores enquanto leitores ativos
    }
    sem_post(&leitores_sem);
    // Fim da seção crítica para leitores


    // Leitura
    printf("Leitor %d está lendo: %d\n", identificador, dados_compartilhados);
    sleep(1);


    // Início da seção crítica para leitores
    sem_wait(&leitores_sem);
    leitores_ativos--;
    if (leitores_ativos == 0) {
        sem_post(&escritores_sem); // Libera escritores quando não há leitores ativos
    }
    sem_post(&leitores_sem);
    // Fim da seção crítica para leitores


    pthread_exit(NULL);
}


void *escritor(void *arg) {
    int identificador = *((int *)arg);


    // Bloqueia leitores e escritores durante a escrita
    sem_wait(&escritores_sem);


    // Seção crítica para escrita
    dados_compartilhados++;
    printf("Escritor %d está escrevendo: %d\n", identificador, dados_compartilhados);
    sleep(1);


    // Libera leitores e escritores após escrita
    sem_post(&escritores_sem);


    pthread_exit(NULL);
}


int main() {
    pthread_t leitores[NUM_LEITORES], escritores[NUM_ESCRITORES];
    int i;


    // Inicialização dos semáforos
    sem_init(&mutex, 0, 1);
    sem_init(&leitores_sem, 0, 1);
    sem_init(&escritores_sem, 0, 1);


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
    sem_destroy(&escritores_sem);


    return 0;
}