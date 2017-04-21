#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>

int main(int argc, char **argv){
	
	if (argc < 2 || argc > 5){
		perror("Wrong number of arguments")
		exit(1);	
	}

	int status;
	int childpid1;
	int childpid2;
	int childpid3;
	int childpid4;
	
	char *args1[] = {NULL, NULL, NULL};
	char *args2[] = {NULL, NULL, NULL};
	char *args3[] = {NULL, NULL, NULL};
	char *args4[] = {NULL, NULL, NULL};
	char *args5[] = {NULL, NULL, NULL};

	int pipes1[2];
	int pipes2[2];
	int pipes3[2];
	int pipes4[2];
	pipe(pipes1);
	pipe(pipes2);
	pipe(pipes3);
	pipe(pipes4);
	
	if (argc > 4){
		int i = 0;
		stringstream inarg(argv[5]);
		while (inarg.good()){
			inarg >> args5[i];
			i++;	
		}
	}

	if (argc > 3){
		int i = 0;
		stringstream inarg(argv[4]);
		while (inarg.good()){
			inarg >> args4[i];
			i++;	
		}
	}

	if (argc > 2){
		int i = 0;
		stringstream inarg(argv[3]);
		while (inarg.good()){
			inarg >> args3[i];
			i++;	
		}
	}
	if (argc > 1){
		int i = 0;
		stringstream inarg(argv[2]);
		while (inarg.good()){
			inarg >> args2[i];
			i++;	
		}
	}
	int i = 0;
	stringstream inarg(argv[1]);
	while (inarg.good()){
		inarg >> args1[i];
		i++;	
	}

	if((childpid1 = fork()) == -1){
		perror("Error creating a child process");
		exit(1);
	}      
	if (childpid1 == 0) {
		dup2(pipes1[1], 1);
		close(pipes1[0]);
		close(pipes1[1]);
		execvp(*args1, args1);
		exit(0);
	}	
	else {
		if((childpid2 = fork()) == -1){
			perror("Error creating a child process");
			exit(1);
		}      

		if (childpid2 == 0) {
			dup2(pipes1[0], 0);
			dup2(pipes2[1], 1);
			close(pipes1[0]);
			close(pipes1[1]);
			close(pipes2[0]);
			close(pipes2[1]);
			execvp(*args2, args2);
			exit(0);
		}
		if (argc == 2){
			return(0);
		}
		else {
			if((childpid3 = fork()) == -1){
				perror("Error creating a child process");
				exit(1);
			}      

			if (childpid3 == 0) {
				dup2(pipes2[0], 0);
				dup2(pipes3[1], 1);
				close(pipes2[0]);
				close(pipes2[1]);
				close(pipes3[0]);
				close(pipes3[1]);
				execvp(*args3, args3);
				exit(0);
			}
			if (argc == 3){
				return(0);
			}
			else {
				if((childpid4 = fork()) == -1){
					perror("Error creating a child process");
					exit(1);
				}      

				if (childpid4 == 0) {
					dup2(pipes3[0], 0);
					dup2(pipes4[1], 1);
					close(pipes3[0]);
					close(pipes3[1]);
					close(pipes4[0]);
					close(pipes4[1]);
					execvp(*args4, args4);
					exit(0);
				}
				if (argc == 4){
					return(0);
				}
				else {
					dup2(pipes4[0], 0);
					close(pipes4[0]);
					close(pipes4[1]);
					execvp(*args5, args5);
					exit(0);
				}
			}
		}	
	}	
	return(0);
}
