#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("File Type     : Regular File\n");
    } else if (S_ISDIR(mode)) {
        printf("File Type     : Directory\n");
    } else if (S_ISLNK(mode)) {
        printf("File Type     : Symbolic Link\n");
    } else {
        printf("File Type     : Other\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];
    struct stat sb;

    // Sử dụng lstat để hỗ trợ symbolic links
    if (lstat(filepath, &sb) == -1) {
        perror("Error using lstat");
        return 1;
    }

    // In đường dẫn
    printf("File Path     : %s\n", filepath);

    // In loại tệp
    print_file_type(sb.st_mode);

    // In kích thước
    printf("Size          : %lld bytes\n", (long long)sb.st_size);

    // In thời gian chỉnh sửa cuối
    char timebuf[100];
    struct tm *timeinfo = localtime(&sb.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last Modified : %s\n", timebuf);

    return 0;
}
