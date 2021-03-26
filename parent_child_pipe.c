#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
  pid_t pid;
  int p[2];
  FILE *fp;
  int fd1, fd2;
  //int status;
  //int fd;
  //char str[80];
  //int i;

  pipe(p);

  pid = fork();

  if (pid == 0)
    {
      char str[100];
      
      fp = fdopen(p[0], "r");
      fd2 = creat("output2.txt", 0777);
      dup2(fd2, 1);

      printf("\n\nThis is the child process.\n");
      fgets(str, 100, fp);
      
      while (strstr(str, "\nLast Line") == NULL)
	{
	  printf("\nReceived from parent process (through pipe): %s", str);
	  fflush(stdout);
	  fgets(str, 100, fp);
	}
	printf("\nReceived the last line from the parent.");
    }
  else if (pid > 0)
    {
    	int i;
    	
      printf("\nThis is the parent process.");
	fp = fdopen(p[1], "w");
	fd1 = creat("output1.txt", 0777);
        dup2(fd1, 1);
	
      for (i=0; i<100000; i++)
	{

	  printf("\nSending to child process (through pipe): Here is line %d", i);
	  fprintf(fp, "Here is line %d\n", i);
	}

      printf("\nSending the last line to child process (through pipe)");
      fprintf(fp, "Last Line\n");
      
      fflush(fp);
    }
    
    close(fp);
    close(p[0]);
    close(p[1]);
}
