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
        	char *argv[] = {"mkdir", "-p", "/home/salma/Modul 2/Musyik", NULL};
        	execv ("/bin/mkdir", argv); }
        	
	else if (child >= 10) { 
		while ((wait(&status)) >= 10);
        	char *argv[] = {"mkdir", "-p", "/home/salma/Modul 2/Fylm", NULL};
        	execv ("/bin/mkdir", argv);
        }
	
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
    }
