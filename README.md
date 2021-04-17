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

First make a program run fail if the condition the program running this ``if (child < 0) { exit(EXIT_FAILURE)``

We need to make 3 if else condition, ``if (child == 0)`` for folder Pyoto, ``else if (child <= 10)`` for folder Musyik, and ``else if (child >= 10)`` for folder Fylm.

To make the folder coming out we need to do system call ``wait`` and ``fork`` ``exec``

<img width="375" alt="soal1a" src="https://user-images.githubusercontent.com/73702347/115103100-676d2f00-9f79-11eb-823d-defc8f7458ed.png">

**b. Download Files for Each Folder**

