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
        // Tiến trình con kết thúc ngay
        printf("Con (PID: %d) kết thúc.\n", getpid());
        exit(0);
    } else {
        // Tiến trình cha không gọi wait(), chỉ ngủ
        printf("Cha (PID: %d) ngủ 30 giây...\n", getpid());
        sleep(30);
        printf("Cha kết thúc.\n");
    }

    return 0;
}
