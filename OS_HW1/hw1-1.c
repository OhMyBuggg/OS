#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80

void split(char *line, char *arg[]){
	while(*line != '\0'){
		while(*line == ' ' || *line == '\n'){
			*line++ = '\0';
		}
		*arg++ = line;
		while(*line != '\0' && *line != ' ' && *line != '\n'){
			line++;
		}
	}
	*arg = '\0';
}

void execute(char **arg, int background){
	pid_t pid, pr = 0;
	int status;

	pid = fork();
	if(pid < 0){
		exit(1);
	}else if(pid == 0){
		if(execvp(*arg, arg)<0){
			printf("%s\n", "wrong command");
			exit(1);
		}
	}else{
		if(background == 1){
			usleep(50000);
		}else{
			do{
				pr = waitpid(pid, &status, 0);
			} while(pr == 0);
		}
	}
}

int main(void)
{
	char *arg[MAX_LINE/2+1]; /*command line arguments*/
	int should_run = 1; /*flag to determine when to exit program*/
	char line[MAX_LINE];
	while(should_run){
		printf("osh>"); //is it ok to change TA's code??
		fflush(stdout);
		int background = 0;
		//len = read(0, arg, MAX_LINE);
		gets(line);
		int len = strlen(line);
		if(line[len-1] == '&') {
			background = 1;
			line[len-1] = '\0';
			line[len-2] = '\0';
		}
		split(line, arg);
		if(strcmp(arg[0], "exit") == 0){
			should_run = 0;
		}else{
			execute(arg, background);
		}
		/**
		* your code!
		* After reading user input, the step are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) if command included &, parent will not invoke wait()
		*/
	}

	return 0;
}

