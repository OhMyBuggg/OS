#include <bits/stdc++.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
using namespace std;

int main(){
	pid_t pid;
	int status;
	
	cout << "Main Process ID : " << getpid() << endl;
	if((pid=fork()) == 0){
		cout << "Fork 1. I'm the child " << getpid() << ", myparent is " << getppid() << endl;
		if((pid=fork())==0){
			cout << "Fork 2. I'm the child " << getpid() << ", myparent is " << getppid() << endl;
			if((pid=fork())==0){
				cout << "Fork 3. I'm the child " << getpid() << ", myparent is " << getppid() << endl;
			}else{
				while(wait(&status) != pid);
			}
		}else if((pid=fork())==0){
			cout << "Fork 2. I'm the child " << getpid() << ", myparent is " << getppid() << endl;
			if((pid=fork())==0){
				cout << "Fork 3. I'm the child " << getpid() << ", myparent is " << getppid() << endl;
			}else{
				while(wait(&status) != pid);
			}
		}else{
			while(wait(&status) != pid);
		}
	}else{
		while(wait(&status) != pid);
	}
}