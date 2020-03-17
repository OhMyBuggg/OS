#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <pthread.h>

using namespace std;

struct parameter{
	int *list;
	int start;
	int end;
};

struct parameter2{
	int *list;
	int start;
	int middle;
	int end;
};

/* function definitions */
void* sort(void* data)
{
	// Sorting algorithm can be brute‐force methods, e.g., bubble sort 
	struct parameter arg;
	arg = *(struct parameter *)data;
	int start = arg.start;
	int end = arg.end;
	for(int i=start; i<end; i++){
		for(int j=start; j<end-1; j++){
			if(arg.list[j] > arg.list[j+1]){
				int temp;
				temp = arg.list[j];
				arg.list[j] = arg.list[j+1];
				arg.list[j+1] = temp;
			}
		}
	}
	pthread_exit(NULL);
}

void* merge(void* data)
{
	// Sorting algorithm can be brute‐force methods, e.g., bubble sort 
	struct parameter2 arg;
	arg = *(struct parameter2 *)data;
	int start = arg.start;
	int middle = arg.middle;
	int end = arg.end;
	int temp1[middle-start];
	int temp2[end-middle];
	int total = end-start;
	int now1 = 0;
	int now2 = 0;
	int i;
	for(i=0; i<middle-start; i++){
		temp1[i] = arg.list[i+start];
		//cout << temp1[i] << endl;
	}
	for(i=0; i<end-middle; i++){
		temp2[i] = arg.list[i+middle];
		//cout << temp2[i] << endl;
	}
	for(i=0; i<total; i++){
		if(temp1[now1] < temp2[now2]){
			arg.list[i+start] = temp1[now1];
			//cout << "temp1[now1]: " << temp1[now1] << endl;
			now1++;
			if(now1 >= middle-start)break;
		}else{
			arg.list[i+start] = temp2[now2];
			//cout << "temp2[now2]: " << temp2[now2] << endl;
			now2++;
			if(now2 >= end-middle)break;
		}
	}
	i++;
	//cout << "partial done" << endl;
	if(i < total){
		if(now1 < middle-start){
			for(; i<total; i++){
				arg.list[i+start] = temp1[now1];
				//cout << "temp1[now1]: " << temp1[now1] << endl;
				now1++;
			}
		}else{
			for(; i<total; i++){
				arg.list[i+start] = temp2[now2];
				//cout << "temp2[now2]: " << temp2[now2] << endl;
				now2++;
			}
		}
	}

	pthread_exit(NULL);
}

int main (int argc, const char * argv[]) 
{
	int list[1000000];
	struct parameter arg[4];
	struct parameter2 arg2[3];
	int all = 0;
	/* Use STDIN (e.g. scanf, cin) to take the input */
	while(cin >> list[all++]);
	all--;
	int middle = all/2;
	int left = middle/2;
	int right = middle + (all-middle)/2;

	/* Do the sorting */
	pthread_t b1, b2, b3, b4;
	arg[0].start = 0;
	arg[0].end = left;
	arg[0].list = list;
	arg[1].start = left;
	arg[1].end = middle;
	arg[1].list = list;
	arg[2].start = middle;
	arg[2].end = right;
	arg[2].list = list;
	arg[3].start = right;
	arg[3].end = all;
	arg[3].list = list;
	pthread_create(&b1, NULL, sort, &(arg[0]));
	pthread_create(&b2, NULL, sort, &(arg[1]));
	pthread_create(&b3, NULL, sort, &(arg[2]));
	pthread_create(&b4, NULL, sort, &(arg[3]));

	pthread_join(b1, NULL);
	pthread_join(b2, NULL);
	pthread_join(b3, NULL);
	pthread_join(b4, NULL);
	/* Use STDOUT (e.g. printf, cout) to output the sorted array */
	pthread_t m1, m2, m3;
	arg2[0].start = 0;
	arg2[0].middle = left;
	arg2[0].end = middle;
	arg2[0].list = list;
	arg2[1].start = middle;
	arg2[1].middle = right;
	arg2[1].end = all;
	arg2[1].list = list;
	arg2[2].start = 0;
	arg2[2].middle = middle;
	arg2[2].end = all;
	arg2[2].list = list;
	pthread_create(&m1, NULL, merge, &(arg2[0]));
	pthread_create(&m2, NULL, merge, &(arg2[1]));

	pthread_join(m1, NULL);
	pthread_join(m2, NULL);

	pthread_create(&m3, NULL, merge, &(arg2[2]));
	pthread_join(m3, NULL);

	for(int i=0; i < all; i++){
		cout << list[i] << " ";
	}
	cout << endl;
	/*
		your code here
	*/
   return 0;
}

