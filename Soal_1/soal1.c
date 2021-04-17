#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main () {
	pid_t child = fork ();
	int status;  
	if (child < 0) {
		exit(EXIT_FAILURE);
 	}
    
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
        	sleep (5); //program with interval time 5s
        	char *argv[] = {"mkdir", "-p", "/home/salma/Modul 2/Musyik", NULL};
        	execv ("/bin/mkdir", argv); }
        	
	else if (child >= 10) { 
		while ((wait(&status)) >= 10);
        	sleep (5); //program with interval time 5s
        	char *argv[] = {"mkdir", "-p", "/home/salma/Modul 2/Fylm", NULL};
        	execv ("/bin/mkdir", argv);
        }
        
    }
