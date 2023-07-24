/*  idea memo */

int concurrent_flag;
int concurrent_exit_flag;

pthread_mutex_t mutex;
pthread_cond_t cond_gc;
pthread_t concurrent_thread;

void *concurrent(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond_gc, &mutex); 
        pthread_mutex_unlock(&mutex);
        if(concurrent_exit_flag)
            goto exit;
        concurrent_flag = 1;
        /* GCを実行するコードをここに追加 */
        concurrent_flag = 0;
    }

exit:
    pthread_exit(NULL);
}

void init_concurrent(void){
    pthread_create(&concurrent_thread, NULL, concurrent, NULL); 
}

void gbc_concurrent(void){
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&cond_gc);
    pthread_mutex_unlock(&mutex);
}

void exit_concurrent(void){
    pthread_mutex_lock(&mutex);
    concurrent_exit_flag = 1;
    pthread_cond_signal(&cond_gc); 
    pthread_mutex_unlock(&mutex);
}

