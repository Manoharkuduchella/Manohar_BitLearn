#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

char cmd;


int main()
{
	int ret;
	int state;
	int pipefd1[2],pipefd2[2];//pipefd[0]- read , pipefd[1]- write

	printf("In parent\n");

	pipe(pipefd1);
	perror("pipe1");

	pipe(pipefd2);
	perror("pipe2");


	ret = fork();

	if(ret == 0)
	{
		printf("in child\n");

		char ch,CH;

		close(pipefd1[1]);
		close(pipefd2[0]);

		while(1)
		{

			//close(pipefd1[1]);//close writeend
			read(pipefd1[0],&ch, 1);
			perror("child read");

			if(ch == 'e')
				break;

			printf("read form parent: %c\n",ch);

			//process the char
			CH = ch-32;

			//close(pipefd2[0]);
			write(pipefd2[1],&CH,1);
			perror("child write");

		}

	}
	else{

			close(pipefd1[0]);
			close(pipefd2[1]);

			while(1)
			{
				printf("enter command:\n");
				scanf(" %c",&cmd);

				//close(pipefd1[0]);//close readend
				write(pipefd1[1],(const void *)&cmd,1);
				perror("parent write");

				if(cmd == 'e')
					break;


				//close(pipefd2[1]);
				read(pipefd2[0],&cmd,1);
				perror("parent read");

				printf("read form child : %c\n",cmd);
			}


		wait(&state);
		

	}

	return 0;

}
