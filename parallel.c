
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include "eisl.h"

void print_ascii(char *str) {
	int i;
    for (i = 0; i < strlen(str); i++) {
        printf("0x%02X ", (unsigned char)str[i]);
    }
    printf("\n");
}


// Thread for parent receiver
void *preceiver(void *arg)
{
	int n, m, i;
	char buffer[BUFSIZE],sub_buffer[BUFSIZE];

	n = *(int *) arg;

    while (1) {

	if (receiver_exit_flag)
	    break;

	// read message from parent
	memset(buffer, 0, sizeof(buffer));
	reread:
	memset(sub_buffer, 0, sizeof(sub_buffer));
    m = read(child_sockfd[n], sub_buffer, sizeof(sub_buffer));
    if (m < 0) {
	exception(SYSTEM_ERR, make_str("receive from child"), make_int(n),
		  0);
    }

	//print_ascii(sub_buffer);printf("m=%d",m);fflush(stdout);
	strcat(buffer,sub_buffer);

	// normal message  0x16 is at m-1
	if(sub_buffer[m-1] != 0x16)
		goto reread;

	//print_ascii(buffer); 
	
	i = strlen(buffer);
	buffer[i] = 0;
	strcpy(parent_buffer[n],buffer); 
    }

    pthread_exit(NULL);
}

// Thread for child receiver
void *creceiver(void *arg)
{
    int n, m, i, j;
	char buffer[BUFSIZE],sub_buffer[BUFSIZE];

	if (!connect_flag) {
	//wait conneting
	listen(parent_sockfd[0], 5);
	parent_len = sizeof(parent_addr);
	connect_flag = 1;

	// connection from parent
	parent_sockfd[1] =
	    accept(parent_sockfd[0], (struct sockaddr *) &parent_addr,
		   &parent_len);
	if (parent_sockfd[1] < 0) {
	    exception(SYSTEM_ERR, make_str("*creceiver"), NIL, 0);
	}
    }

    
    while (1) {

	if (receiver_exit_flag)
	    break;

	
	// read message from parent
	memset(buffer, 0, sizeof(buffer));
	reread:
	memset(sub_buffer, 0, sizeof(sub_buffer));
	n = read(parent_sockfd[1], sub_buffer, sizeof(sub_buffer));
	if (n < 0) {
	    error(SYSTEM_ERR, "*creceiver", NIL, 0);
	}

	strcat(buffer,sub_buffer);
	if(sub_buffer[n-1] != 0x16)
		goto reread;

	pthread_mutex_lock(&mutex2);

	
	j = 0;
	
	
	m = strlen(buffer);

	for (i = 0; i < m-1; i++) {
		if(buffer[i] == 0x11){
			memset(child_buffer,0,sizeof(child_buffer));
			strcpy(child_buffer,"fail.");
			child_buffer_pos = 0;
			child_buffer_end = 5;
			exit_flag = 1;
			goto exit;
		}
	    else { 
			child_buffer[j] = buffer[i];
	    	j++;
		}
	}

	child_buffer_pos = 0;
	child_buffer_end = j;

	exit:
	printf("receive from parent %s\n",child_buffer);

	child_buffer_ready = 1;
	pthread_cond_signal(&md_cond);
	pthread_mutex_unlock(&mutex2);

	
    }

    pthread_exit(NULL);
}


void init_preceiver(int n)
{	
	int i;
    // create parent receiver thread 
	for(i=0;i<n;i++){
		int *arg = malloc(sizeof(int));
        *arg = i;
    	pthread_create(&preceiver_thread[i], NULL, preceiver, arg);
	}

}

void init_creceiver(void)
{
    // create child receiver thread 
    pthread_create(&creceiver_thread, NULL, creceiver, NULL);

}