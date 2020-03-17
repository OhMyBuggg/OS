#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
double pi_estimate;
long long number_of_thread, number_of_tosses, number_in_circle, each_tosses;

void *Thread_sum(void *th){
		long long thread_num = *(long long *)th;
    long long toss, local_count;
    double distance_squared, x, y;
    unsigned int seed = time(NULL) + thread_num;

    local_count = 0;
    for (toss = 0; toss < each_tosses; toss++) {
        x = (2 * (double)rand_r(&seed) / RAND_MAX) - 1;
        y = (2 * (double)rand_r(&seed) / RAND_MAX) - 1;
        distance_squared = x*x + y*y;
        if (distance_squared <= 1){
            local_count++;
        }
    }
    pthread_mutex_lock(&mutex);
    number_in_circle += local_count;
    pthread_mutex_unlock(&mutex);
    printf("Thread %lld, There are %llu points in the circle\n", thread_num, local_count);

    return NULL;
}

int main(){
	printf("0616223\n");

	scanf("%lld", &number_of_thread);
	scanf("%lld", &number_of_tosses);

	long thread;
  pthread_t *thread_handles;

  thread_handles = (pthread_t*) malloc (number_of_thread*sizeof(pthread_t));
  //pthread_mutex_init(&mutex, NULL);
  number_in_circle = 0;
  each_tosses = number_of_tosses / number_of_thread;

  for(thread = 0; thread < number_of_thread; thread++){
  	long long *tmp = (long long *)malloc(sizeof(long long));
		*tmp = thread;
    pthread_create(&thread_handles[thread], NULL, Thread_sum, tmp);
  }

  for(thread = 0; thread < number_of_thread; thread++){
    pthread_join(thread_handles[thread], NULL);
  }

	pi_estimate = 4 * number_in_circle/(double)number_of_tosses;
	pthread_mutex_destroy(&mutex);

	printf("Pi: %lf\n",pi_estimate);
	return 0;
}
