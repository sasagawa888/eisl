#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];

    perror("start asdf\n");
    while (1) {
        // 標準入力から1行読み取る
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }
        perror("inputed asdf\n");
        // 読み取ったデータを標準出力に書き出す
        if (printf("%s", buffer) < 0) {
            perror("printf");
            exit(EXIT_FAILURE);
        }
        fflush(stdout); // 標準出力をフラッシュする
        perror("outputed asdf\n");

        // パイプへの書き込みエラーチェック
        if (ferror(stdout)) {
            perror("write to pipe");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

