#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

/* function definitions */
void sort(int list[]);
int all = 0;

int main (int argc, const char * argv[]) 
{
	int list[1000000];
	/* Use STDIN (e.g. scanf, cin) to take the input */
	while(cin >> list[all++]);
	all--;
	/* Do the sorting */
	sort(list);

	/* Use STDOUT (e.g. printf, cout) to output the sorted array */
	for(int i=0; i < all; i++){
		cout << list[i] << " ";
	}
	cout << endl;
	/*
		your code here
	*/
   return 0;
}

void sort(int list[])
{
	// Sorting algorithm can be brute‐force methods, e.g., bubble sort 
	for(int i=0; i<all; i++){
		for(int j=0; j<all-1; j++){
			if(list[j] > list[j+1]){
				int temp;
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}

