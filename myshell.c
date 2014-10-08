#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>/*for strlen*/
#include <unistd.h>/*for execlp*/
#include <signal.h>
#include "myerr.h"

static void sig_int();

int main(void)
{
	char buff[MAXLINE];
	pid_t pid;
	int status;

	if( signal(SIGINT, sig_int)==SIG_ERR )
	{
		perror("signal error:");
		return 0;
	}
	printf("+>");
	while( fgets(buff, MAXLINE, stdin) != NULL)
	{
		if ( '\n'==buff[strlen(buff) - 1] )
			buff[ strlen(buff)-1 ]='\0';
		if( (pid=fork()) < 0)
		{
			perror("fork error:");
		}
		else if(pid == 0)/*child*/
		{
			execlp(buff, buff, (char*)0);	
			err_ret("couldn't exec %s",buff);
			exit(127);
		}
		/*parent*/
		if( (pid=waitpid(pid, &status, 0)) < 0)
			perror("wait error:");
		printf("+> ");
	}
	exit(0);
}

void sig_int()
{
	printf("interrupted\n+>");
}

