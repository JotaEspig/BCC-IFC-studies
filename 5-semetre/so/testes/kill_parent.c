#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <unistd.h>

void handle_signal(int sig) {
  if (sig == SIGHUP) {
    printf("[Filho] Recebeu SIGHUP, o pai morreu!\n");
  }
}

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    perror("fork falhou");
    return 1;
  }

  if (pid == 0) { // Processo filho
    // Configura o sinal SIGHUP para ser enviado ao filho quando o pai morrer
    prctl(PR_SET_PDEATHSIG, SIGHUP);
    // Configura o manipulador de sinal
    signal(SIGHUP, handle_signal);

    printf("[Filho] PID: %d, PPID (pai): %d\n", getpid(), getppid());

    pause();

    printf("[Filho] Novo PPID: %d\n", getppid());
    sleep(100);
    exit(0);
  } else { // Processo pai
    printf("[Pai] PID: %d, Criou filho PID: %d\n", getpid(), pid);

    pause();

    printf("[Pai] Bye bye\n");
    exit(0);
  }

  return 0;
}
