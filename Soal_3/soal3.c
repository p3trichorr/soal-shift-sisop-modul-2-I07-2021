#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

//3A - Make directory according to the format name
void directory()
{
  pid_t child_id;
  char datedirectory[100];
  struct tm *timenow;
  
  //Save child_id from child process
  child_id = fork();

  //Make format name for the directory
  time_t t = time(NULL);
  timenow = localtime(&t);
  strftime(datedirectory, sizeof(datedirectory), "%Y-%m-%d_%H:%M:%S", timenow);

  if(child_id < 0) 
  {
    exit(EXIT_FAILURE);
  }

  if(child_id == 0) 
  {
    char *argv[] = {"mkdir", date, NULL};
    execv("/bin/mkdir", argv);
  }
}

//Main function
int main(int argc, char *argv[])
{
  int status;
    
  while(wait(&status) > 0);
  
  while(1)
  {
    directory();
    sleep(40);
  }
}
