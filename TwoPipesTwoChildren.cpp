#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char **argv){
	int status;
	int childpid;
	int childpid2;
	
	char *cat_args[] = {"ls", "-ltr", NULL};
	char *grep_args[] = {"grep", "3376", NULL};
	char *wc_args[] = {"wc", "-l", NULL};

	int pipes[2];
	int pipes2[2];
	pipe(pipes);
	pipe(pipes2);

	if((childpid = fork()) == -1){
		perror("Error creating a child process");
		exit(1);
	}      
	if (childpid == 0) {
		dup2(pipes[1], 1);
		close(pipes[0]);
		close(pipes[1]);
		execvp(*cat_args, cat_args);
		exit(0);
	}	
	else {
		if((childpid2 = fork()) == -1){
			perror("Error creating a child process");
			exit(1);
		}      

		if (childpid2 == 0) {
			dup2(pipes[0], 0);
			dup2(pipes2[1], 1);
			close(pipes[0]);
			close(pipes[1]);
			close(pipes2[0]);
			close(pipes2[1]);
			execvp(*grep_args, grep_args);
			exit(0);
		}
		else {
			dup2(pipes2[0], 0);
			close(pipes2[0]);
			close(pipes2[1]);
			execvp(*wc_args, wc_args);
			exit(0);
		}
	}	
	return(0);
}
