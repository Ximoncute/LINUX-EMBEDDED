#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Tiến trình con: in PPID nhiều lần
        for (int i = 0; i < 5; i++) {
            printf("Con (PID: %d) - Cha (PPID): %d\n", getpid(), getppid());
            sleep(2);
        }
    } else {
        // Tiến trình cha thoát ngay
        printf("Cha (PID: %d) thoát ngay.\n", getpid());
        exit(0);
    }

    return 0;
}
