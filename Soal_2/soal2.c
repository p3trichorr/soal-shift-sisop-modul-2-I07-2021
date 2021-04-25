#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<syslog.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<wait.h>
#include<dirent.h>

int main() {
    int state_1, state_2, state_3, state_4;
    
    //a
    pid_t cid;
    cid = fork();
    if(cid < 0) exit(0);
    if(cid == 0) {
        char *command[] = {"unzip", "pets", "*.jpg", "-d", "/home/zulu/modul2/petshop", NULL};
        execv("/bin/unzip", command);
    }
    
    //b
    while(wait(&state_1) > 0);
    DIR *pdr1;
    struct dirent *entry1;
    pdr1 = opendir("/home/zulu/modul2/petshop");
    char folder[100][300];
    int n = 0;
    while((entry1 = readdir(pdr1)) != NULL) {
        if(entry1->d_type == DT_REG) {
            char tmp[300], tmp2[300];
            memset(folder[n], 0, sizeof(folder[n]));
            memset(tmp2, 0, sizeof(tmp2));
            strcpy(tmp, entry1->d_name);
            
            int i, found = 0;
            for(i = 0; i < strlen(tmp); i++) {
                if(tmp[i] == ';') break;
                tmp2[i] = tmp[i];
            }
            
            for(i = 0; i < n && found == 0; i++)
                if(strcmp(folder[i], tmp2) == 0)
                    found = 1;
            
            if(found == 0) {
                strcpy(folder[n], tmp2);
                n++;
            }
        }
    }
    
    int i;
    for(i = 0; i < n; i++) {
        pid_t cid;
        cid = fork();
        if(cid < 0) exit(0);
        if(cid == 0) {
            char tmp[300];
            sprintf(tmp, "/home/zulu/modul2/petshop/%s", folder[i]);
            char *command[] = {"mkdir", tmp, NULL};
            execv("/bin/mkdir", command);
        }
    }
    
    //c
    while(wait(&state_2) > 0);
    DIR *pdr2;
    struct dirent *entry2;
    pdr2 = opendir("/home/zulu/modul2/petshop");
    while((entry2 = readdir(pdr2)) != NULL) {
        if(entry2->d_type == DT_REG) {
            char tmp[300];
            char type1[300], name1[300], age1[300];
            char type2[300], name2[300], age2[300];
            memset(type1, 0, sizeof(type1));
            memset(name1 , 0, sizeof(name1));
            memset(age1 , 0, sizeof(age1));
            memset(type2, 0, sizeof(type2));
            memset(name2 , 0, sizeof(name2));
            memset(age2 , 0, sizeof(age2));
            strcpy(tmp, entry2->d_name);
            
            int i, l, found = 0, counter = 0;
            for(i = 0; i < strlen(tmp); i++) {
                if(tmp[i] == ';') break;
                type1[i] = tmp[i];
            }
            
            i++; l = i;
            for(; i < strlen(tmp); i++) {
                if(tmp[i] == ';') break;
                name1[i-l] = tmp[i];
            }
            
            i++; l = i;
            for(; i < strlen(tmp); i++) {
                if(tmp[i] == '_' || (tmp[i] == '.' && tmp[i+1] == 'j')) break;
                age1[i-l] = tmp[i];
            }
            
            //c&d
            if(tmp[i] == '_') {
                i++; l = i;
                for(; i < strlen(tmp); i++) {
                    if(tmp[i] == ';') break;
                    type2[i-l] = tmp[i];
                }
                
                i++; l = i;
                for(; i < strlen(tmp); i++) {
                    if(tmp[i] == ';') break;
                    name2[i-l] = tmp[i];
                }
                
                i++; l = i;
                for(; i < strlen(tmp); i++) {
                    if(tmp[i] == '.' && tmp[i+1] == 'j') break;
                    age2[i-l] = tmp[i];
                }
                
                counter = 1;
            }
            //end of c
            
            int state_1, state_2;
            pid_t cid;
            cid = fork();
            if(cid < 0) exit(0);
            if(cid == 0) {
                char from[300], to[300];
                sprintf(from, "/home/zulu/modul2/petshop/%s", entry2->d_name);
                sprintf(to, "/home/zulu/modul2/petshop/%s/%s", type1, name1);
                char *command[] = {"cp", "-r", from, to, NULL};
                execv("/bin/cp", command);
            }
            
            
            //e
            while(wait(&state_1) > 0);
            char ket[300];
            sprintf(ket, "/home/zulu/modul2/petshop/%s/keterangan.txt", type1);
            FILE *filep;
            filep = fopen(ket, "a+");
            fprintf(filep, "nama : %s\n", name1);
            fprintf(filep, "umur : %s tahun\n\n", age1);
            fclose(filep);
            //end of e
            
            if(counter == 1) {
                pid_t cid;
                cid = fork();
                if(cid < 0) exit(0);
                if(cid == 0) {
                    char from[300], to[300];
                    sprintf(from, "/home/zulu/modul2/petshop/%s", entry2->d_name);
                    sprintf(to, "/home/zulu/modul2/petshop/%s/%s", type2, name2);
                    char *command[] = {"cp", "-r", from, to, NULL};
                    execv("/bin/cp", command);
                }
                
                //e
                while(wait(&state_2) > 0);
                char ket[300];
                sprintf(ket, "/home/zulu/modul2/petshop/%s/keterangan.txt", type2);
                FILE *filep;
                filep = fopen(ket, "a+");
                fprintf(filep, "nama : %s\n", name2);
                fprintf(filep, "umur : %s tahun\n\n", age2);
                fclose(filep);
                //end of e
            }
            //end of d
        }
    }
    
    //remove image before
    while(wait(&state_3) > 0);
    DIR *pdr3;
    struct dirent *entry3;
    pdr3 = opendir("/home/zulu/modul2/petshop");
    while((entry3 = readdir(pdr3)) != NULL) {
        if((entry3->d_type == DT_REG) && strcmp(entry3->d_name, ".") != 0 && strcmp(entry3->d_name, "..") != 0){
            pid_t cid;
            cid = fork();
            if(cid < 0) exit(0);
            if(cid == 0) {
                char folder[300];
                sprintf(folder, "/home/zulu/modul2/petshop/%s", entry3->d_name);
                char *command[] = {"rm", "-r", folder, NULL};
                execv("/bin/rm", command);
            }
        }
    }
}
