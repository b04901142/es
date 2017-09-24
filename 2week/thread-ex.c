/* Includes */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <sys/syscall.h>
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
/* prototype for thread routine */
void print_message_function ( void *ptr, void *arg);
/* struct to hold data to be passed to a thread
this shows how multiple data items can be passed to a thread */
typedef struct str_thdata{
	int thread_no;
	char message[100];
} thdata;

pthread_t tid;

int main(){
	pthread_t thread1, thread2;  /* thread variables */
	thdata data1, data2;         /*structs to be passed to threads*/
	/* initialize data to pass to thread 1 */
	data1.thread_no = 1;
	strcpy(data1.message, "Hello!");
	/* initialize data to pass to thread 2 */
	data2.thread_no = 2;
	strcpy(data2.message, "Hi!");
	/* create threads 1 and 2 */
	pthread_create (&thread2, NULL, (void *) &print_message_function, (void *) &data2);
	tid=thread2;
	pthread_create (&thread1, NULL, (void *) &print_message_function, (void *) &data1);
	tid=thread1;
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	exit(0);    /* exit */
} /* main() */

/**
* print_message_function is used as the start routine for the t
hreads used
* it accepts a void pointer
**/
void print_message_function ( void *ptr, void *arg ){
	thdata *data;
	data = (thdata *) ptr;  /* type cast to a pointer to thdata */
	/* do the work */
   //pid_t = (pid_t)syscall(SYS_gettid);
	printf("Thread %d (thread id: %lu) says %s \n", data->thread_no, tid, data->message);
	printf("UID: %u\nPID: %u\nPPID: %u\nTID: %lu\n", geteuid(), getpid(), getppid(), syscall(SYS_gettid));
	sleep(10);
	pthread_exit(0); /* exit */
} /* print_message_function ( void *ptr ) */
