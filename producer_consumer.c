#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

int data = 0;                 // Dữ liệu được chia sẻ
bool data_ready = false;     // Cờ báo dữ liệu sẵn sàng

pthread_mutex_t lock;
pthread_cond_t cond;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        // Tạo dữ liệu ngẫu nhiên
        int value = rand() % 100;

        pthread_mutex_lock(&lock);

        // Đặt dữ liệu và bật cờ
        data = value;
        data_ready = true;
        printf("[Producer] Sản xuất: %d\n", data);

        // Báo hiệu cho consumer
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&lock);
        sleep(1); // Mô phỏng thời gian sản xuất
    }

    pthread_exit(NULL);
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&lock);

        // Chờ đến khi data_ready == true
        while (!data_ready) {
            pthread_cond_wait(&cond, &lock);
        }

        // Đọc và xử lý dữ liệu
        printf("[Consumer] Tiêu thụ: %d\n", data);

        // Đặt lại cờ
        data_ready = false;

        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t t_producer, t_consumer;

    // Khởi tạo mutex và condition variable
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    // Tạo luồng producer và consumer
    pthread_create(&t_producer, NULL, producer, NULL);
    pthread_create(&t_consumer, NULL, consumer, NULL);

    // Chờ cả hai luồng kết thúc
    pthread_join(t_producer, NULL);
    pthread_join(t_consumer, NULL);

    // Hủy tài nguyên
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    printf("Kết thúc chương trình.\n");
    return 0;
}
