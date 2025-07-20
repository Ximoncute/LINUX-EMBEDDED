#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid, wpid;
    int status;

    pid = fork(); // Tạo tiến trình con

    if (pid < 0) {
        // fork() thất bại
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Đây là tiến trình con
        printf("Tiến trình con:\n");
        printf("  PID của tiến trình con: %d\n", getpid());
        printf("  PID của tiến trình cha: %d\n", getppid());
        exit(10); // Kết thúc với mã thoát 10
    } else {
        // Đây là tiến trình cha
        printf("Tiến trình cha:\n");
        printf("  PID của tiến trình cha: %d\n", getpid());
        printf("  PID của tiến trình con: %d\n", pid);

        wpid = wait(&status); // Chờ tiến trình con kết thúc

        if (WIFEXITED(status)) {
            printf("Tiến trình con (PID %d) đã kết thúc với mã thoát: %d\n", wpid, WEXITSTATUS(status));
        } else {
            printf("Tiến trình con không kết thúc bình thường.\n");
        }
    }

    return 0;
}
