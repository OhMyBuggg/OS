#include<bits/stdc++.h>
using namespace std;

struct processNode
{
	int id;
	int arrival;
	int burst;
	int priority;
	int turnaroundTime;
	int waitTime;
	int terminateTime;
};

bool compare(processNode &node1, processNode &node2){
	return node1.priority < node2.priority;
}

bool compare2(processNode &node1, processNode &node2){
	return node1.id < node2.id;
}

int main(int argc, char *argv[]){

	int processNum;
	cin >> processNum;

	int arrivalTime[processNum];
	int burstTime[processNum];
	int prior[processNum];
	vector<processNode> process;
	int burstAll = 0;
	int minArr = 1000;

	for(int i=0; i<processNum; i++){
		cin >> arrivalTime[i];
	}
	for(int i=0; i<processNum; i++){
		cin >> burstTime[i];
	}
	for(int i=0; i<processNum; i++){
		cin >> prior[i];
	}
	for(int i=0; i<processNum; i++){
		processNode temp;
		temp.id = i;
		temp.arrival = arrivalTime[i];
		temp.burst = burstTime[i];
		temp.priority = prior[i];
		temp.turnaroundTime = 0;
		temp.waitTime = 0;
		temp.terminateTime = 0;
		process.push_back(temp);
		burstAll += burstTime[i];
		if(arrivalTime[i] < minArr){
			minArr = arrivalTime[i];
		}
	}

	sort(process.begin(), process.end(), compare);
	for(int i=0; i<processNum; i++){
		process[i].arrival -= minArr;
	}

	int schedule[burstAll];

	for(int i=0; i<burstAll; i++){
		schedule[i] = -1;
	}

	for(int i=0; i<processNum; i++){
		for(int j=process[i].arrival, k=0; j<process[i].arrival + process[i].burst + k; j++){
			if(schedule[j] != -1){
				k++;
			}else{
				schedule[j] = process[i].id;
			}
		}
	}

	for(int i=0; i<processNum; i++){ //id
		for(int j=burstAll - 1; j >= 0; j--){ //index
			if(schedule[j] == process[i].id){
				process[i].terminateTime = j+1;
				break;
			}
		}
	}

	int waitSum = 0;
	int turnaroundSum = 0;

	for(int i=0; i<processNum; i++){
		process[i].turnaroundTime = process[i].terminateTime - process[i].arrival;
		turnaroundSum += process[i].turnaroundTime;
	}
	for(int i=0; i<processNum; i++){
		process[i].waitTime = process[i].terminateTime - process[i].arrival - process[i].burst;
		waitSum += process[i].waitTime;
	}

	sort(process.begin(), process.end(), compare2);

	for(int i=0; i<processNum; i++){
		cout << process[i].waitTime << " " << process[i].turnaroundTime << endl;
	}
	cout << waitSum << endl;
	cout << turnaroundSum << endl;

	return 0;
}