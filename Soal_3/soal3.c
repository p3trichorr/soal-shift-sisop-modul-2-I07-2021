#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <signal.h>

//Caesar cipher algorithm
void cipher(char message[], int key)
{
  char ch; 
  int i;

  for(i = 0; message[i] != '\0'; i++)
  {
    ch = message[i];

    if(ch >= 'a' && ch <= 'z')
    {
      ch = ch + key;
            
      if(ch > 'z')
      {
        ch = ch - 'z' + 'a' - 1;
      }
      message[i] = ch;
    }

    else if(ch >= 'A' && ch <= 'Z')
    {
      ch = ch + key;
        
      if(ch > 'Z')
      {
        ch = ch - 'Z' + 'A' - 1;
      }
      message[i] = ch;
    }
  }
}

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
    char *argv[] = {"mkdir", datedirectory, NULL};
    execv("/bin/mkdir", argv);
  }
}

//3B - Download 10 photos to each directory
void download(char datedirectory[])
{
  pid_t child_id;
  char link[100];
  struct tm *timenow;
  char datephoto[100];
  int status;
  
  child_id = fork();

  if(child_id < 0) 
  {
    exit(EXIT_FAILURE);
  }
  
  if(child_id == 0)
  {
    //Download photos to the directory that we want --> (date directory)
    chdir(datedirectory);
    for(int i = 0; i < 10; i++)
    {
      //Make format name for the photos
      time_t t_photo = time(NULL);
      timenow = localtime(&t_photo);
      strftime(datephoto, sizeof(datephoto), "%Y-%m-%d_%H:%M:%S", timenow);
      
      //Make format to download the photos including the size of the photos
      sprintf(link , "https://picsum.photos/%ld", (t_photo % 1000) + 50);

      pid_t child_id_datephoto

      child_id_datephoto = fork();

      if(child_id_datephoto < 0)
      {
        exit(EXIT_FAILURE);
      }

      if(child_id_datephoto == 0)
      {
        char *argv[] = {"wget", link, "-O", datephoto, "-o", "/dev/null", NULL};
        execv("/bin/wget", argv);
      }
      //Wait 5 seconds to download another photo
      sleep(5);
    }
    while(wait(&status) > 0);

    //3C - Make a txt file 
    char message[100] = {"Download Success"};
    cipher(message, 5);

    FILE* text = fopen("status.txt", "w");
    fprintf(text, "%s", message);
    fclose(text);
   
    //Download photos to the next directory
    chdir("..")
  }
}

//3C - Zip the txt folder with the txt file in it
void zip(char datedirectory[])
{
  char zipfile[100];
  strcpy(zipfile, datedirectory);
  strcat(zipfile, ".zip");

  pid_t child_id;

  child_id = fork();

  if(child_id_datephoto < 0)
  {
    exit(EXIT_FAILURE);
  }

  if(child_id_datephoto == 0)
  {
    char *argv[] = {"zip", "-r", zipfile, datedirectory, NULL};
    execv("/bin/zip", argv);
  }
}

//3C - Delete forder that has been zipped
void delete(char datedirectory[])
{
  pid_t child_id;

  child_id = fork();

  if(child_id < 0)
  {
    exit(EXIT_FAILURE);
  }

  if(child_id == 0)
  {
    char *argv[] = {"rm", "-r", datedirectory, NULL};
    execv("/bin/rm", argv);
  }
}

//3D - Killer program
void killerbash(int argc, char *argv[], int pid)
{
  pid_t child_id;
  child_id = fork();
  int status;

  if(child_id < 0)
  {
    exit(EXIT_FAILURE);
  }

  if (child_id == 0)
  {
    //3E - Killer program with 2 mode
    FILE* killer = fopen("killer.sh", "w");
    if (strcmp(argV[1], "-z") == 0)
    {
      //Kill program immedietly
      fprintf(killer, "#!/bin/bash\nkillall -9 soal3\nrm\"$0\"");
    }
	  
    else if (strcmp(argV[1], "-x") == 0)
    {
      //Kill program after done doing 3A-3C
      fprintf(killer, "#!/bin/bash\nkill %d\nrm \"$0\"", pid);
    }
    fclose(killer);
  }

  else if(child_id > 0 && wait(&status) > 0)
  {
    //To make the bash program executable
    char *argv[] = {"chmod", "+x", "killer.sh", NULL};
    execv("/bin/chmod", argv);
  }
}

//Main function
int main(int argc, char *argv[])
{
  int status, status2, status3, status4;

  pid_t pid, sid;
  pid = fork();

  if(pid < 0)
  {
    exit(EXIT_FAILURE);
  }

  if(pid > 0)
  {
    exit(EXIT_SUCCESS);
  }
 
  umask(0);

  sid = setsid();

  if(sid < 0)
  {
    exit(EXIT_FAILURE);
  }
   
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  killerbash(argc, argv, (int) getpid()+1);

  while(1)
  {
    char datedirectory[100];
    directory(datedirectory);
    while(wait(&status) > 0);
    
    download(datedirectory);
    while(wait(&status2) > 0);

    zip(datedirectory);
    while(wait(&status3) > 0);

    delete(datedirectory);
    while(wait(&status4) > 0);

    //Wait 40 seconds to make another directory
    sleep(40);
  }
}
