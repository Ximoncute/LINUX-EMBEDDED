#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

int shared_data = 0;  // Tài nguyên chia sẻ

pthread_rwlock_t rwlock;

void* reader(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < 3; i++) {
        pthread_rwlock_rdlock(&rwlock); // Khóa đọc
        printf("[Reader %d] Đọc giá trị: %d\n", id, shared_data);
        pthread_rwlock_unlock(&rwlock); // Mở khóa
        usleep(100000); // nghỉ 100ms
    }
    pthread_exit(NULL);
}

void* writer(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < 3; i++) {
        pthread_rwlock_wrlock(&rwlock); // Khóa ghi (độc quyền)
        shared_data++;
        printf(">>> [Writer %d] Ghi +1 → Giá trị mới: %d\n", id, shared_data);
        pthread_rwlock_unlock(&rwlock);
        usleep(200000); // nghỉ 200ms
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Khởi tạo read-write lock
    pthread_rwlock_init(&rwlock, NULL);

    // Tạo các reader
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Tạo các writer
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Chờ các luồng reader hoàn thành
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Chờ các luồng writer hoàn thành
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    printf("Kết thúc chương trình.\n");
    return 0;
}
