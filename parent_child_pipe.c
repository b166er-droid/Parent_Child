#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
  pid_t pid;
  int status;
  int fd;
  int p[2];
  char str[80];
  int i;

  pipe(p);

  pid = fork();

  if (pid == 0)
    {
      dup2(p[0], 0);
      close(p[0]);

      printf("\n\nThis is the child process.\n");
      read(0, str, 16);
      
      while (strcmp(str, "\nHere is line XX") != 0)
	{
	  printf("\nReceived from parent process (through pipe): %s", str);
	  read(0, str, 16);
	}
    }
  else if (pid > 0)
    {
      printf("\nThis is the parent process.");

      for (i=0; i<10; i++)
	{
	  strcpy(str, "Here is line #");
	  str[14] = '0' + i;
	  str[15] = '\0';

	  printf("\nSending to child process (through pipe): %s", str);
	  write(p[1], str, strlen(str)+1);
	}

      strcpy(str, "Here is line XX");
      printf("\nSending to child process (through pipe): %s", str);
      write(p[1], str, strlen(str));
    }
}
