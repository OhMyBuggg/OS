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
};

bool compare(processNode &node1, processNode &node2){
	if(node1.arrival == node2.arrival){
		return node1.priority < node2.priority;
	}
	return node1.arrival < node2.arrival;
}

bool compare2(processNode &node1, processNode &node2){
	return node1.priority < node2.priority;
}

bool compare3(processNode &node1, processNode &node2){
	return node1.id < node2.id;
}
int main(int argc, char *argv[]){

	int processNum;
	cin >> processNum;

	int arrivalTime[processNum];
	int burstTime[processNum];
	int prior[processNum];
	vector<processNode> process;

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
		process.push_back(temp);
	}

	vector<processNode>::iterator it = process.begin();
	sort(it, it + processNum, compare);

	int terminateTime[processNum];
	terminateTime[0] = process[0].arrival + process[0].burst;
	for(int i=1; i<processNum; i++){
		int co = 0;
		for(int t=i; t<processNum; t++){
			if(process[t].arrival <= terminateTime[i-1]) co++;
		}
		if(co == 0){
			terminateTime[i] = process[i].arrival + process[i].burst;
		}else{
			sort(it+i, it+i+co, compare2);	//sort by priority
			terminateTime[i] = terminateTime[i-1] + process[i].burst;
		}
	}

	int waitSum = 0;
	int turnaroundSum = 0;

	for(int i=0; i<processNum; i++){
		process[i].turnaroundTime = terminateTime[i] - process[i].arrival;
		turnaroundSum += process[i].turnaroundTime;
	}
	for(int i=0; i<processNum; i++){
		process[i].waitTime = terminateTime[i] - process[i].arrival - process[i].burst;
		waitSum += process[i].waitTime;
	}

	sort(process.begin(), process.end(), compare3);

	for(int i=0; i<processNum; i++){
		cout << process[i].waitTime << " " << process[i].turnaroundTime << endl;
	}
	cout << waitSum << endl;
	cout << turnaroundSum << endl;

	return 0;
}