#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

long long number_of_threads, size, size_per_thread;
char *input;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long long sum[10];

void *Thread_sum(void *th){
	long long thread_num = *(long long *)th;
	//printf("%lld\n", thread_num);
	long long position = size_per_thread * thread_num;
	for(long long i = 0; i < size_per_thread; i++){
		int temp = input[position + i] - '0';
		pthread_mutex_lock(&mutex);
		sum[temp]++;
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

int main(){
	printf("0616223\n");

	scanf("%lld", &number_of_threads);
	scanf("%lld", &size);

	for(long long i = 0; i < 10; i++){
		sum[i] = 0;
	}

	size_per_thread = size / number_of_threads;
	input = (char *)malloc(size * sizeof(char));
	scanf("%s", input);

	long long thread;
	pthread_t *thread_handles;

	thread_handles = (pthread_t *)malloc(number_of_threads * sizeof(pthread_t));
	//pthread_mutex_init(&mutex, NULL);

	for(thread = 0; thread < number_of_threads; thread++){
		long long *tmp = (long long *)malloc(sizeof(long long));
		*tmp = thread;
		pthread_create(&thread_handles[thread], NULL, Thread_sum, tmp);
	}

	long long position = size_per_thread * thread;
	for(long long i = 0; i < size-position; i++){
		int temp = input[position + i] - '0';
		pthread_mutex_lock(&mutex);
		sum[temp]++;
		pthread_mutex_unlock(&mutex);
	}

	for(thread = 0; thread < number_of_threads; thread++){
		pthread_join(thread_handles[thread], NULL);
	}

	for(long long i = 0; i < 10; i++){
		printf("The total number of %lld : %lld\n", i, sum[i]);
	}
	pthread_mutex_destroy(&mutex);

	return 0;
}