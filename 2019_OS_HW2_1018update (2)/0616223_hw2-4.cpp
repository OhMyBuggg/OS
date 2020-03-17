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

struct processNode2
{
	int id;
	int burst;
	int prior;
};

bool compare(processNode &node1, processNode &node2){
	return node1.arrival < node2.arrival;
}

bool compare2(processNode2 &node1, processNode2 &node2){
	return node1.prior < node2.prior;
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
	int burstAll = 0;
	vector<processNode2> lowQueue;
	int minArr = 1000;
	int burstQuantum;

	for(int i=0; i<processNum; i++){
		cin >> arrivalTime[i];
	}
	for(int i=0; i<processNum; i++){
		cin >> burstTime[i];
	}
	for(int i=0; i<processNum; i++){
		cin >> prior[i];
	}
	cin >> burstQuantum;
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

	for(int i=0; i<processNum; i++){
		process[i].arrival -= minArr;
	}

	sort(process.begin(), process.end(), compare);
	int schedule[burstAll];
	int fill = 0;

	for(int i=0; i<burstAll; i++){
		schedule[i] = -1;
	}

	for(int i=0; i<processNum; i++){
		if(process[i].burst > burstQuantum){
			for(int j=0; j<burstQuantum; j++){
				schedule[fill] = process[i].id;
				fill++;
			}
		}else{
			for(int j=0; j<process[i].burst; j++){
				schedule[fill] = process[i].id;
				fill++;
			}
		}
	}

	for(int i=0; i<processNum; i++){
		if(process[i].burst > burstQuantum){
			processNode2 temp;
			temp.id = process[i].id;
			temp.burst = process[i].burst- burstQuantum;
			temp.prior = process[i].priority;
			lowQueue.push_back(temp);
		}
	}

	sort(lowQueue.begin(), lowQueue.end(), compare2);
	for(int i=0; i<lowQueue.size(); i++){
		for(int j=0; j<lowQueue[i].burst; j++){
			schedule[fill] = lowQueue[i].id;
			fill++;
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

	sort(process.begin(), process.end(), compare3);


	for(int i=0; i<processNum; i++){
		cout << process[i].waitTime << " " << process[i].turnaroundTime << endl;
	}
	cout << waitSum << endl;
	cout << turnaroundSum << endl;

	return 0;
}