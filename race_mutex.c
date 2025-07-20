#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3
#define INCREMENTS 1000000

long long counter = 0; // Biến toàn cục được chia sẻ
pthread_mutex_t lock;  // Khai báo mutex

void* increment(void* arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&lock);     // Khóa mutex
        counter++;                     // Thao tác trên tài nguyên chia sẻ
        pthread_mutex_unlock(&lock);   // Mở khóa mutex
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Khởi tạo mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Không thể khởi tạo mutex");
        return 1;
    }

    // Tạo các luồng
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment, NULL) != 0) {
            perror("Lỗi tạo luồng");
            return 1;
        }
    }

    // Chờ các luồng hoàn thành
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Hủy mutex
    pthread_mutex_destroy(&lock);

    printf("Giá trị cuối cùng của counter: %lld\n", counter);
    return 0;
}
