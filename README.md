# soal-shift-sisop-modul-2-I07-2021

Made by:

Group I07

Gede Yoga Arisudana (051119420000098)

Salma Rahma Lailia (05111942000016)

Zulfiqar Rahman Aji (05111942000019)



## PROBLEM 1
**a. Show The Folder Named Musyik, Fylm, Pyoto**

```
	void makeDirectory() {
	pid_t pid;
 	int status;
    	pid = fork();

    	if ((chdir(cwd)) < 0) {
      		exit(EXIT_FAILURE);
    }

    	if (pid == 0){
      		char *argv[] = {"mkdir", fileStevany[0], fileStevany[1], fileStevany[2], NULL};
      		execv("/bin/mkdir", argv);
    }
     
  	else {
      		while((wait(&status)) > 0);
    		return;          
    }
}
```

First make a program run fail if the program condition running this ``if ((chdir(cwd)) < 0) { exit(EXIT_FAILURE); }`` when the ``char cwd[]= "/home/salma/Modul2/";``

We need to make 3 folder named Pyoto, Musyik, Fylm ``char *argv[] = {"mkdir", fileStevany[0], fileStevany[1], fileStevany[2], NULL}; execv("/bin/mkdir", argv);`` and named the file in this char ``char *fileStevany[] = {"Pyoto", "Musyik", "Fylm"};``

<img width="350" alt="soal1a" src="https://user-images.githubusercontent.com/73702347/115103100-676d2f00-9f79-11eb-823d-defc8f7458ed.png">

**b. Download Files for Each Folder**

```
void downloadAndUnzip () {
	pid_t pid;
  	int status;
    	pid = fork();
  
  	if ((chdir(cwd)) < 0) {
      		exit(EXIT_FAILURE);
  }
  
  	if(pid==0) {
  
      		if (fork() == 0) {              // child process -- download FOTO
        		char *argv[] = {"wget", "--no-check-certificate", web[0], "-O", fileZip[0], NULL};
        		execv("/usr/bin/wget", argv);
      } 
  
      else {
      		while((wait(&status)) > 0);
  
        	if (fork() == 0) {         // child process -- download MUSIK
            		char *argv[] = {"wget", "--no-check-certificate", web[1], "-O", fileZip[1], NULL};
            	execv("/usr/bin/wget", argv);
        } 
  
        else {
        	while((wait(&status)) > 0);
  
            	if (fork() == 0) {       // child process -- download FILM
              		char *argv[] = {"wget", "--no-check-certificate", web[2], "-O", fileZip[2], NULL};
              		execv("/usr/bin/wget", argv);
            } 
```

We need to download each folder from gdrive that given, and use child process to download each file. Through this link ``char *web[]={"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};``

After that we rename it in the ``char *fileZip[] = {"Foto_for_Stevany.zip", "Musik_for_Stevany.zip", "Film_for_Stevany.zip"};``

**c. Unzip all the downloaded files**

```
else {                   // parent process -- unzip all files
       	while((wait(&status)) > 0);
       	char *argv[] = {"unzip", "-q", "*.zip", NULL};
       	execv("/usr/bin/unzip", argv);
            }
```

Used ``char *argv[] = {"unzip", "-q", "*.zip", NULL};`` to unzip all file

**d. Moving the unzip folder in the folder that we made in the 1a**

```
void moveFiles() {
	pid_t pid;
    	int status;
    	pid = fork();
    
  	if ((chdir(cwd)) < 0) {
      		exit(EXIT_FAILURE);
  }

  	if(pid==0){
      		if(fork() == 0){
        	char *find[] = {"find","/home/salma/Modul2/FOTO" , "-type", "f", "-exec", "mv", "{}", 
                        "/home/salma/Modul2/Pyoto", ";", NULL};
        	execv("/usr/bin/find", find);
      }
  
      else {
      		while((wait(&status)) > 0);
      		if (fork() == 0) {
            		char *find[] = {"find", "/home/salma/Modul2/MUSIK", "-type", "f", "-exec", "mv", "{}", 
                            "/home/salma/Modul2/Musyik", ";", NULL};
            		execv("/usr/bin/find", find);
        }
  
      else {
      		while((wait(&status)) > 0);
       	char *find[] = {"find", "/home/salma/Modul2/FILM", "-type", "f", "-exec", "mv", "{}", 
                            "/home/salma/Modul2/Fylm", ";", NULL};
            	execv("/usr/bin/find", find);
        }
      }
  }
  
else {
	while((wait(&status)) > 0);
	return;
  }
```

After we downloaded the file, then we unzip all file like in the 1c, and unzip with these name (FOTO, MUSIK AND FILM).

Move it with ``mv`` 

**e. Zip all the file named Lopyu_Stevany.zip and Remove all the rest of the folder**

```
void zipFiles() {
	pid_t pid;
  	int status;
 	pid = fork();

	if(pid == 0) {
    		char *argv[] = {"zip", "-q", "-r", "-m", "Lopyu_Stevany.zip", fileStevany[0], fileStevany[1], fileStevany[2], NULL};
    		execv("/usr/bin/zip", argv);
  }

	else {
    		while(wait(&status) > 0);
    		return;
  }
  
  void removeFolder() {
	pid_t pid;
  	int status;
  	pid = fork();

  	if(pid == 0) {
    		char *argv[] = {"rm", "-d", fileUnzip[0], fileUnzip[1], fileUnzip[2], NULL};
    		execv("/usr/bin/rm", argv);
  }

  	else {
    		while(wait(&status) > 0);
    		return;
  }
```

Zipp all the folder from Pyoto, Musyik, Fylm with this ``char *argv[] = {"zip", "-q", "-r", "-m", "Lopyu_Stevany.zip", fileStevany[0], fileStevany[1], fileStevany[2], NULL};``

Name it with Lopyu_Stevany.zip

**f. Run all the program in 6 hours before her birthday in 9 April 22.00**

```
if (local->tm_mon+1==4 && local->tm_mday == 9 && local->tm_hour == 16 && local->tm_min == 22 && local->tm_sec == 0) {
    		makeDirectory();
    		downloadAndUnzip();
    		moveFiles();
  }

  	else if (local->tm_mon+1==4 && local->tm_mday == 9 && local->tm_hour == 22 && local->tm_min == 22 && local->tm_sec == 0) {
    		zipFiles();
    		removeFolder();
  }
    
    sleep(1);
  }
```

Because before 22.00 is 16.00 so we have to run it twice ``sudo date --set="2021-04-09 16:21:59"`` and ``sudo date --set="2021-04-09 22:21:59"``

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
    	char *argv[] = {"unzip", "pets", "*.jpg", -d", "/home/zulu/modul2/petshop", NULL};
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
```

**b. Download 10 photos for each directory**
```
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
    //Download photos to the directory that we want --> (datedirectory)
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
```
In problem 3B, we are needed to download 10 photos for each directory, and each photo will be downloaded for every 5 seconds, the first thing I do is to choose the directory to be the place of the photo that will be downloaded, therefore I use `chdir(datedirectory)` command, after that I will make format name for the photo using `struct tm *` command to get the localtime from my laptop then I use `strftime` command to break down the time so it will go like the format that the question want. Now, I want to make format to download the photos including the size of the photos using `sprintf` command. And now, in the child process in `char *argv[]` function, I write `{"wget", link, "-O", datephoto, "-o", "/dev/null" NULL}` to get the picture, I use `wget` so I can get the photo from the link, then I use `-O` so the output  will be seen in the `datephoto` directory or document, after that I use `-o` to log all the message or in this case the photos to the logfile, lastly I will use `"/dev/null"` so it will give the permission. After that, I will use `sleep` command, so eaxh photo will be downloaded for every 5 seconds. And the last thing that I will do is to use `chdir("..")` command, so the downloaded photo will be downloaded to the next directory or the new one.

**c. Zip the folder and make txt file in the zip also delete the folder that has been zipped**
```
char message[100] = {"Download Success"};
cipher(message, 5);

FILE* text = fopen("status.txt", "w");
fprintf(text, "%s", message);
fclose(text);
```
In problem 3C, we are needed to zip the previous folder from problem 3A, then make a txt file in there, after that we must delete the folder that has been zipped. So now, the first thing that I do is make the txt file first like the code above, I use `FILE*` command to make the file, than use the `fopen` also `"w"` command to open the txt file and to able to write in the txt file, then I use `fprint` command to print in the txt file, lastly I will use `fclose` command to close the txt file.
```
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
```
Now, the next thing that I will do is to zip the folder, firstly I will use `strcpy` file to copy the string from the `datedirectory` to `zipfile` and then I use `strcat` to decide the type of the file. After that, in the child process I will use `{"zip", "-r", zipfile, datedirectory, NULL}` to zip the file that I named `datedirectory`.
```
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
```
Lastly, to solve problem 3C, I must delete the folder that has been zipped, and in this function I will write `{"rm", "-r", datedirectory, NULL}` in the child process to delete the folder that has been zipped.

**d and e. Make a killer program for 2 mode**
```
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
      //Kill program immediately
      fprintf(killer, "#!/bin/bash\nkillall -9 soal3\nrm \"$0\"");
    }
	  
    else if (strcmp(argV[1], "-x") == 0)
    {
      //Kill program after done doing 3A-3C
      fprintf(killer, "#!/bin/bash\nkill %d\nrm\"$0\"", pid);
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
```
In problem 3D and 3E, we are needed to make a killer program with 2 mode the first one is with  `-z` argument so the killer program will immedeatily kill the program and the other one is with `-x` argument so the killer program will kill the program after finishing 3A until 3C, now the first thing to do is to make the file for kller program using `FILE*` command like this,
```
FILE* killer = fopen("killer.sh", "w");
```
After that I will compare the argumen that have been inputted to decide which mode that I will use using `strcmp` command, now for the `-z` argument I will use `fprintf` command so the file will print the killer program, I will use `killall -9 soal 3` so it will kill all the program immedeatily and also I will use `rm` command so the killer program will kill themselves, and for the `-x` argument it will be the same but the different is it will not use `kill all -9 soal3` instead it will use `kill` because we want the program keep running from 3A-3C first, then kill it. So the code will be like this,
```
 if (strcmp(argV[1], "-z") == 0)
    {
      //Kill program immediately
      fprintf(killer, "#!/bin/bash\nkillall -9 soal3\nrm \"$0\"");
    }
	  
    else if (strcmp(argV[1], "-x") == 0)
    {
      //Kill program after done doing 3A-3C
      fprintf(killer, "#!/bin/bash\nkill %d\nrm\"$0\"", pid);
    }
```
Also, I of course use `fclose` command to close the file that has been opened like this,
```
fclose(killer);
```
Lastly, I will use `chmod` command to make the bash program executeable with the code like this,
```
  else if(child_id > 0 && wait(&status) > 0)
  {
    //To make the bash program executable
    char *argv[] = {"chmod", "+x", "killer.sh", NULL};
    execv("/bin/chmod", argv);
  }
```
