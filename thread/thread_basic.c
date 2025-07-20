#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Hàm sẽ được các luồng chạy
void* thread_function(void* arg) {
    pthread_t tid = pthread_self(); // Lấy ID của luồng hiện tại
    printf("Thread với ID %lu đang chạy!\n", tid);
    sleep(1); // Mô phỏng luồng làm việc
    pthread_exit(NULL); // Kết thúc luồng
}

int main() {
    pthread_t thread1, thread2;

    // Tạo luồng 1
    if (pthread_create(&thread1, NULL, thread_function, NULL) != 0) {
        perror("Không thể tạo luồng 1");
        return 1;
    }

    // Tạo luồng 2
    if (pthread_create(&thread2, NULL, thread_function, NULL) != 0) {
        perror("Không thể tạo luồng 2");
        return 1;
    }

    // Đợi cả hai luồng kết thúc
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Luồng chính kết thúc sau khi hai luồng con kết thúc.\n");
    return 0;
}
