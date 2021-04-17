#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

//3A - Make directory according to the format name
void directory(char datedirectory[])
{
  pid_t child_id;
  struct tm *timenow;
  
  //Save child_id from child process
  child_id = fork();

  //Make format name for the directory
  time_t t = time(NULL);
  timenow = localtime(&t);
  strftime(datedirectory, 100, "%Y-%m-%d_%H:%M:%S", timenow);

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

//3B - Download 10 photos for each directory
void download(datedirectory)
{
  pid_t child_id;
  char link[100];
  struct tm *timenow;
  char datephoto[100];
  
  child_id = fork();

  if(child_id < 0) 
  {
    exit(EXIT_FAILURE);
  }
  
  if(child_id == 0)
  {
    //Download photos to the directory that we want --> (downloaddirectory)
    chdir(downloaddirectory);
    for(int i = 0; i < 10; i++)
    {
      //Make format name for the photos
      time_t t_photo = time(NULL);
      timenow = localtime(&t_photo);
      strftime(datephoto, sizeof(datephoto), "%Y-%m-%d_%H:%M:%S", timenow);
      
      //Download photos from the website
      sprintf(link , "https://picsum.photos/%ld", (t_photo % 1000) + 50);

      pid_t child_id_datephoto

      child_id_datephoto = fork();

      if(child_id_datephoto < 0)
      {
        exit(EXIT_FAILURE);
      }

      if(child_id_datephoto == 0)
      {
        char *argv[] = {"wget", link, "-O", datephoto, "-o", "/dev/null" NULL};
        execv("/usr/bin/wget", argv);
      }
      //Wait 5 seconds to download another photo
      sleep(5);
    }
    //Download photos to the next directory
    chdir("..")
  }
}

//Main function
int main(int argc, char *argv[])
{
  int status, status2;
  
  while(1)
  {
    char datedirectory[100];
    directory(datedirectory);
    while(wait(&status) > 0);
    
    download(datedirectory);
    while(wait(&status2) > 0);
     
    //Wait 40 seconds to make another directory
    sleep(40);
  }
}
