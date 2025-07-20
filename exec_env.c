#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Thiết lập biến môi trường MY_COMMAND
    setenv("MY_COMMAND", "ls", 1);

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Tiến trình con

        // Đọc giá trị biến môi trường
        char *cmd = getenv("MY_COMMAND");

        if (cmd == NULL) {
            fprintf(stderr, "Không tìm thấy biến môi trường MY_COMMAND\n");
            exit(1);
        }

        printf("Tiến trình con sẽ thực thi lệnh: %s\n", cmd);

        // Thay thế tiến trình hiện tại bằng lệnh trong biến môi trường
        execlp(cmd, cmd, (char *)NULL);

        // Nếu execlp thất bại
        perror("execlp failed");
        exit(1);
    } else {
        // Tiến trình cha chờ tiến trình con kết thúc
        wait(NULL);
        printf("Tiến trình cha: Tiến trình con đã kết thúc.\n");
    }

    return 0;
}
