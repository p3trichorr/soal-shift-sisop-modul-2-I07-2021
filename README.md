# soal-shift-sisop-modul-2-I07-2021

Made by:

Group I07

Gede Yoga Arisudana (051119420000098)

Salma Rahma Lailia (05111942000016)

Zulfiqar Rahman Aji (05111942000019)



## PROBLEM 1
**a. Show The Folder Named Musyik, Fylm, Pyoto**

```
	if (child == 0) {
	        pid_t child = fork();
        
        if (child < 0) {
		exit(EXIT_FAILURE);
	} 
    }
    
	if (child == 0) { 
    		char *argv[] = {"mkdir", "-p", "/home/salma/Modul 2/Pyoto", NULL};
        	execv("/bin/mkdir", argv); }
        
	else if (child <= 10) {
        	while ((wait(&status)) <= 10);
        	char *argv[] = {"mkdir", "-p", "/home/salma/Modul 2/Musyik", NULL};
        	execv ("/bin/mkdir", argv); }
        	
	else if (child >= 10) { 
		while ((wait(&status)) >= 10);
        	char *argv[] = {"mkdir", "-p", "/home/salma/Modul 2/Fylm", NULL};
        	execv ("/bin/mkdir", argv);
```

First make a program run fail if the program condition running this ``if (child < 0) { exit(EXIT_FAILURE)``

We need to make 3 if else condition, ``if (child == 0)`` for folder Pyoto, ``else if (child <= 10)`` for folder Musyik, and ``else if (child >= 10)`` for folder Fylm.

To make the folder coming out we need to do system call ``wait`` and ``fork`` ``exec``

<img width="350" alt="soal1a" src="https://user-images.githubusercontent.com/73702347/115103100-676d2f00-9f79-11eb-823d-defc8f7458ed.png">

**b. Download Files for Each Folder**

```
if ((chdir("/home/salma/Modul2") <0)) {
 		exit (EXIT_FAILURE); }
 	
	if (fork () == 0) { 
		char web [100];
		sprintf (web, "https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view?usp=sharing"); 
		char name[100];
		char *argv[]={"wget", web, "-qO", name, NULL};
 		execv ("/bin/wget", argv); }
 	
	if (fork () == 0) {
        	char web [100];
		sprintf (web, "https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view?usp=sharing");
		char name[100];
		char *argv[]={"wget", web, "-qO", name, NULL};
 		execv ("/bin/wget", argv); }
 	
	if (fork () == 0) { 
		char web [100];
		sprintf (web, "https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view?usp=sharing");
		char name[100];
		char *argv[]={"wget", web, "-qO", name, NULL};
 		execv ("/bin/wget", argv); 
 	}   
```
We need to download each folder from gdrive that given 

## PROBLEM 2
**a. Make a folder, Extract the zip folder and Delete folders else then the jpeg's**

```
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
  pid_t child1_id;
  int status1;
  child1_id = fork();
  
  if (child1_id < 0) {
    exit(EXIT_FAILURE); // failing in making a process will result in stopping the program
  }

  if (child1_id == 0) {
    char *argv[] = {"mkdir", "-p", "/home/zulu/modul2/petshop", NULL};
    execv("/bin/mkdir", argv); 
```
The code above is the first child process in which it will make a folder using the `mkdir -p` command for the upcoming extracted with the directory `/home/zulu/modul2/petshop`.
```
} else {
    while ((wait(&status1)) > 0);
    pid_t child2_id;
    int status2;
    child2_id = fork();
    
    if (child2_id < 0){
    	exit(EXIT_FAILURE);
    }
    if (child2_id == 0){
    	char *argv[] = {"unzip", "pets", "-d", "/home/zulu/modul2/petshop", NULL};
    	execv("/bin/unzip", argv);
```
The code was then continued with the `unzip` command specifying `pets` to unzip the file and put them into the `/home/zulu/modul2/petshop` directory.
```
}	else {
    	while ((wait(&status2)) > 0);
    	char *argv[] = {"rm", "-r", "/home/zulu/modul2/petshop/apex_cheats","/home/zulu/modul2/petshop/musics", "/home/zulu/modul2/petshop/unimportant_files" ,NULL};
    	execv("/usr/bin/rm", argv);
```
Finally the code then removed all the folder that is not a jpeg file using the `rm` command to remove and `-r` command to do it recursively.

## PROBLEM 3

**a. Make a directory every 40 seconds with a name according to the timestamp**
```
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
```
In problem 3A, we are needed to make a directory with a name according to the timestamp, As we can see above, I already take the code for 3A from the source code, the first thing that I do is to make the format name for the directory, I use `struct tm *` command to get the localtime from my laptop, after that I use `strftime` command to break down the time so it will go like the format that the question want. And then I will get the format name for the directory that will be made by this `void directory()` function. And then to make the directory for every 40 seconds I will use `sleep` command in the main function like this
```
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
```

**b. Download 10 photos for each directory**
```
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
        char *argv[] = {"wget", link, "-O", datephoto, "-o", "/dev/null" NULL};
        execv("/bin/wget", argv);
      }
      //Wait 5 seconds to download another photo
      sleep(5);
    }
    //Download photos to the next directory
    chdir("..")
  }
}
```
In problem 3B, we are needed to download 10 photos for each directory, and each photo will be downloaded for every 5 seconds, the first thing I do is to choose the directory to be the place of the photo that will be downloaded, therefore I use `chdir(downloaddirectory)` command, after that I will make format name for the photo using `struct tm *` command to get the localtime from my laptop then I use `strftime` command to break down the time so it will go like the format that the question want. Now, I want to make format to download the photos including the size of the photos using `sprintf` command. And now, in the child process in `char *argv[]` function, I write `{"wget", link, "-O", datephoto, "-o", "/dev/null" NULL}` to get the picture, I use `wget` so I can get the photo from the link, then I use `-O` so the output  will be seen in the `datephoto` directory or document, after that I use `-o` to log all the message or in this case the photos to the logfile, lastly I will use `"/dev/null"` so it will give the permission. After that, I will use `sleep` command, so eaxh photo will be downloaded for every 5 seconds. And the last thing that I will do is to use `chdir("..")` command, so the downloaded photo will be downloaded to the next directory or the new one.
