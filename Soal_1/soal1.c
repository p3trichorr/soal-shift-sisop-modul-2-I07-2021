#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

char cwd[] = "/home/salma/Modul2";
char *folder[] = {"Pyoto", "Musyik", "Fylm"};
void makeDirectory();
void downloadUnzip();

int main() {

	pid_t pid, sid;
	
	pid = fork();
	
	if (pid > 0) {
 		exit (EXIT_FAILURE); 
 	}
	
	if (pid < 0) {
 		exit (EXIT_FAILURE); 
 	}
 	
 	umask(0);
 	
	sid = setsid();
	if(sid < 0) {
		exit (EXIT_FAILURE);
	}
	
	if ((chdir(cwd)) < 0) {
 		exit (EXIT_FAILURE); 
 	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	
	while(1) {
		makeDirectory();
		downloadUnzip();
		sleep(30);
	}
}

void makeDirectory() {  
	pid_t pid, sid;
	int status;
	pid = fork();
	
	if ((chdir(cwd)) < 0) {
 		exit (EXIT_FAILURE); 
 	}
 		
	if (pid == 0) { 
    		char *argv[] = {"mkdir", folder[0], folder[1], folder[2], NULL};
        	execv ("/bin/mkdir", argv);
	}
	
	else {
		while((wait(&status)) > 0);
		return;
	}
}

void downloadUnzip() {
	pid_t pid, sid;
	int status;
	pid = fork();
	
	if ((chdir(cwd)) < 0) {
 		exit (EXIT_FAILURE); 
 	}
 	
	if (pid == 0) { 
		char *argv[] = {"wget", "-q", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto_for_Stevany.zip", NULL};
        	execv ("/usr/bin/wget", argv);
	}
	
	else { 
		while ((wait(&status)) > 0);
		if (fork() == 0) {
			char *argv[] = {"wget", "-q", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik_for_Stevany.zip", NULL};
        		execv ("/usr/bin/wget", argv);	
	}
	
	else { 
		while ((wait(&status)) > 0);
		if (fork() == 0) {
			char *argv[] = {"wget", "-q", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Film_for_Stevany.zip", NULL};
        		execv ("/usr/bin/wget", argv);
			}			
		}
	}
}
