#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5

typedef int filosofo_t;
typedef struct node node_t;
typedef struct node {
  filosofo_t filosofo;
  struct node *next;
} node_t;
typedef struct queue {
  node_t *head;
  node_t *tail;
} queue_t;

int garfos[5] = {0, 0, 0, 0, 0};           // 0 = Livre, 1 = Ocupado
int filosofos_estado[5] = {0, 0, 0, 0, 0}; // 0 = Pensando, 1 = Comendo
int filosofos_signals[5] = {0, 0, 0, 0, 0};
queue_t *queue;
pthread_mutex_t mutex;
pthread_mutex_t mutex_signal;

int mod(int a, int b) { return (a % b + b) % b; }

void queue_print(queue_t *queue);
void queue_free(queue_t *queue);
void enqueue(queue_t *queue, filosofo_t filosofo);
filosofo_t dequeue(queue_t *queue);
queue_t *create_queue();

int filosofo_pode_comer(filosofo_t filosofo) {
  int x = garfos[mod(filosofo, NUM_FILOSOFOS)] == 0 &&
          garfos[mod(filosofo + 1, NUM_FILOSOFOS)] == 0;
  return x;
}

int filosofo_is_pensando(filosofo_t filosofo) {
  int x = filosofos_estado[filosofo] == 0;
  return x;
}

void filosofo_comendo(filosofo_t filosofo, int comendo) {
  garfos[mod(filosofo, NUM_FILOSOFOS)] = comendo;
  garfos[mod(filosofo + 1, NUM_FILOSOFOS)] = comendo;
  filosofos_estado[filosofo] = comendo;
}

int read_signal(filosofo_t filosofo) {
  int x = 0;
  while (x == 0) {
    pthread_mutex_lock(&mutex_signal);
    x = filosofos_signals[filosofo];
    if (x != 0) {
      filosofos_signals[filosofo] = 0;
    }
    pthread_mutex_unlock(&mutex_signal);
  }
  return x;
}

void *filosofo(void *arg) {
  int id = *(int *)arg;
  while (1) {
    // Pensando
    printf("[%d]: Filosofo pensando\n", id);
    sleep(rand() % 10 + 1); // Simula o tempo pensando

    // Tentando pegar os garfos
    pthread_mutex_lock(&mutex);
    if (filosofo_pode_comer(id)) {
      printf("[%d]: Filosofo comendo\n", id);
      filosofo_comendo(id, 1);
      pthread_mutex_unlock(&mutex);
    } else {
      enqueue(queue, id);
      printf("[%d]: Adicionado na fila filosofo com fome\n", id);
      pthread_mutex_unlock(&mutex);
      read_signal(id);
      printf("[%d]: Sinal recebido\n", id);
      printf("[%d]: Filosofo comendo\n", id);
    }

    // liberando garfos
    sleep(rand() % 10 + 1);

    pthread_mutex_lock(&mutex);
    filosofo_comendo(id, 0);
    pthread_mutex_unlock(&mutex);
  }
}

int main() {
  pthread_mutex_init(&mutex, NULL);

  queue = create_queue();

  // Create 5 threads
  pthread_t threads[NUM_FILOSOFOS];
  int filosofos_ids[NUM_FILOSOFOS];

  for (int i = 0; i < NUM_FILOSOFOS; i++) {
    filosofos_ids[i] = i;
    if (pthread_create(&threads[i], NULL, filosofo, &filosofos_ids[i])) {
      perror("Failed to create thread");
      return 1;
    }
  }

  int t = 0;
  int start = time(NULL);
  while (t < start + 1000) {
    sleep(2); // espera para testar fila

    pthread_mutex_lock(&mutex);

    node_t *before = NULL;
    node_t *curr = queue->head;
    while (curr != NULL) {
      filosofo_t filosofo = curr->filosofo;
      if (filosofo_pode_comer(filosofo)) {
        printf("[MAIN]: Filosofo %d na fila vai comer\n", filosofo);
        filosofo_comendo(filosofo, 1);

        // Remove
        if (before == NULL) {
          curr = curr->next;
          dequeue(queue);
        } else if (curr == queue->tail) {
          queue->tail = before;
          curr = curr->next;
        } else {
          node_t *temp = curr;
          curr = curr->next;
          before->next = curr;
          free(temp);
        }

        // send signal for filosofo thread
        pthread_mutex_lock(&mutex_signal);
        printf("[MAIN]: Enviado sinal para %d\n", filosofo);
        filosofos_signals[filosofo] = 1;
        pthread_mutex_unlock(&mutex_signal);
      } else {
        printf("[MAIN]: Filosofo %d na fila NÃO pode comer\n", filosofo);
        curr = curr->next;
      }

    }

    pthread_mutex_unlock(&mutex);

    t = time(NULL);
  }

  for (int i = 0; i < NUM_FILOSOFOS; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("Failed to join thread");
      return 1;
    }
  }

  return 0;
}

node_t *create_node(filosofo_t filosofo) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->filosofo = filosofo;
  node->next = NULL;
  return node;
}

queue_t *create_queue() {
  queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
  queue->head = NULL;
  queue->tail = NULL;
  return queue;
}

filosofo_t dequeue(queue_t *queue) {
  if (queue->head == NULL) {
    return -1; // Queue is empty
  }
  node_t *temp = queue->head;
  filosofo_t filosofo = temp->filosofo;
  queue->head = queue->head->next;
  if (queue->head == NULL) {
    queue->tail = NULL;
  }
  free(temp);
  return filosofo;
}

void enqueue(queue_t *queue, filosofo_t filosofo) {
  node_t *node = create_node(filosofo);
  if (queue->head == NULL) {
    queue->head = node;
    queue->tail = node;
  } else {
    queue->tail->next = node;
    queue->tail = node;
  }
}

void queue_print(queue_t *queue) {
  node_t *current = queue->head;
  while (current != NULL) {
    printf("%d ", current->filosofo);
    current = current->next;
  }
  printf("\n");
}

void queue_free(queue_t *queue) {
  node_t *current = queue->head;
  while (current != NULL) {
    node_t *temp = current;
    current = current->next;
    free(temp);
  }
  free(queue);
}
