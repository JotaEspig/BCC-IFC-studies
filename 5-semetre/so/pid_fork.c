#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t pid = fork(); // Create a child process

  if (pid == 0) {
    printf("Child process: PID = %d\n", getpid());
  } else {
    printf("Parent process: PID = %d\n", getpid());
  }

  return 0;
}
