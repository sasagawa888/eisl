#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; /* this data is shared by the thread(s) */
void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
	int count, i;
	pthread_attr_t attr; 

	if (argc != 2) {
		fprintf(stderr,"usage: pthreads <integer value>\n");
		return -1;
	}

	count = atoi(argv[1]);

	if (count < 1) {
		fprintf(stderr,"%d must be>= 1\n", count);
		return -1;
	}

	pthread_attr_init(&attr);

	for(i=1;i<=count;i++){
		pthread_t thread;
		pthread_create(&thread,&attr,runner,(void*)i);
		pthread_join(thread,NULL);	
		printf("fib of %d is %d\n", i, sum);
	}	
}

void *runner(void *param)
{
	sum = fibonacci((int)param);
	pthread_exit(0);
}

int fibonacci (int x)
{
    if (x <= 1) {
        return 1;
    }
    return fibonacci(x-1) + fibonacci(x-2);
}