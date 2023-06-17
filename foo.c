#include <stdio.h>
#include <pthread.h>

#define NUM 40
#define NUM_THREAD 2

/* スレッド実行に必要なデータを格納する構造体 */
struct data {
    int start;
    int num;
    int* result;
};

void *func(void *arg);


/* 関数func：スレッドでやること */
/* 引数arg：スレッド（仕事）を行う上で必要な情報 */
void *func(void *arg){
    int i;
    struct data *pd = (struct data *)arg;

    /* argで指定された情報に基づいて処理 */
    for(i = pd->start; i < pd->start + pd->num; i++){
        pd->result[i] = i * i * i * i;
    }
    return NULL;
}

int main(void){
    /* 0からNUM-1をカウントする変数 */
    int i;

    /* 結果を格納する配列 */
    int r[NUM] = {0};

    /* スレッドを格納する配列 */
    pthread_t t[NUM_THREAD];
    
    /* スレッドを実行する上で必要な情報を格納する配列 */
    struct data d[NUM_THREAD];

    /* 1つ目のスレッドを行う上で必要な情報を格納 */
    d[0].start = 0; /* 計算開始する数 */
    d[0].num = NUM / 2; /* 計算を行う回数 */
    d[0].result = r; /* 計算結果を格納するアドレス */

    /* 1つ目のスレッドを作成 */
    pthread_create(&t[0], NULL, func, &d[0]);

    /* 2つ目のスレッドを行う上で必要な情報を格納 */
    d[1].start = NUM / 2; /* 計算開始する数 */
    d[1].num = NUM / 2; /* 計算を行う回数 */
    d[1].result = r; /* 計算結果を格納するアドレス */

    /* 2つ目のスレッドを作成 */
    pthread_create(&t[1], NULL, func, &d[1]);

    /* スレッドの終了を待機 */
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);

    for(i=0;i<NUM;i++)
    printf("%d", r[i]);
    return 0;
}