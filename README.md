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

## PROBLEM 2



## PROBLEM 3
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
