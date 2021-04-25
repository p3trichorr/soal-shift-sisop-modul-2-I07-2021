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
      
    pid_t cid;
    cid = fork();
    if(cid < 0) exit(0);
    if(cid == 0) {
        char *command[] = {"unzip", "pets", "*.jpg", "-d", "/home/zulu/modul2/petshop", NULL};
        execv("/bin/unzip", command);
    }
    
    while(wait(&state_2) > 0);
    DIR *dirp2;
    struct dirent *entry2;
    dirp2 = opendir("/home/zulu/modul2/petshop");
    char foldername[100][300];
    int idx = 0;
    while((entry2 = readdir(dirp2)) != NULL) {
        if(entry2->d_type == DT_REG) {
            char tmp[300], tmp2[300];
            memset(foldername[idx], 0, sizeof(foldername[idx]));
            memset(tmp2, 0, sizeof(tmp2));
            strcpy(tmp, entry2->d_name);
            
            int i, found = 0;
            for(i = 0; i < strlen(tmp); i++) {
                if(tmp[i] == ';') break;
                tmp2[i] = tmp[i];
            }
            
            for(i = 0; i < idx && found == 0; i++)
                if(strcmp(foldername[i], tmp2) == 0)
                    found = 1;
            
            if(found == 0) {
                strcpy(foldername[idx], tmp2);
                idx++;
            }
        }
    }
    
    int i;
    for(i = 0; i < idx; i++) {
        pid_t cid;
        cid = fork();
        if(cid < 0) exit(0);
        if(cid == 0) {
            char tmp[300];
            sprintf(tmp, "/home/zulu/modul2/petshop/%s", foldername[i]);
            char *command[] = {"mkdir", tmp, NULL};
            execv("/bin/mkdir", command);
        }
    }
    
    while(wait(&state_3) > 0);
    DIR *dirp3;
    struct dirent *entry3;
    dirp3 = opendir("/home/zulu/modul2/petshop");
    while((entry3 = readdir(dirp3)) != NULL) {
        if(entry3->d_type == DT_REG) {
            char tmp[300];
            char tmp2_jenis[300], tmp2_nama[300], tmp2_umur[300];
            char tmp3_jenis[300], tmp3_nama[300], tmp3_umur[300];
            memset(tmp2_jenis, 0, sizeof(tmp2_jenis));
            memset(tmp2_nama , 0, sizeof(tmp2_nama));
            memset(tmp2_umur , 0, sizeof(tmp2_umur));
            memset(tmp3_jenis, 0, sizeof(tmp3_jenis));
            memset(tmp3_nama , 0, sizeof(tmp3_nama));
            memset(tmp3_umur , 0, sizeof(tmp3_umur));
            strcpy(tmp, entry3->d_name);
            
            int i, ii, found = 0, counter = 0;
            for(i = 0; i < strlen(tmp); i++) {
                if(tmp[i] == ';') break;
                tmp2_jenis[i] = tmp[i];
            }
            
            i++; ii = i;
            for(; i < strlen(tmp); i++) {
                if(tmp[i] == ';') break;
                tmp2_nama[i-ii] = tmp[i];
            }
            
            i++; ii = i;
            for(; i < strlen(tmp); i++) {
                if(tmp[i] == '_' || (tmp[i] == '.' && tmp[i+1] == 'j')) break;
                tmp2_umur[i-ii] = tmp[i];
            }
            
            if(tmp[i] == '_') {
                i++; ii = i;
                for(; i < strlen(tmp); i++) {
                    if(tmp[i] == ';') break;
                    tmp3_jenis[i-ii] = tmp[i];
                }
                
                i++; ii = i;
                for(; i < strlen(tmp); i++) {
                    if(tmp[i] == ';') break;
                    tmp3_nama[i-ii] = tmp[i];
                }
                
                i++; ii = i;
                for(; i < strlen(tmp); i++) {
                    if(tmp[i] == '.' && tmp[i+1] == 'j') break;
                    tmp3_umur[i-ii] = tmp[i];
                }
                
                counter = 1;
            }
            
            int state_1, state_2;
            pid_t cid;
            cid = fork();
            if(cid < 0) exit(0);
            if(cid == 0) {
                char asal[300], tujuan[300];
                sprintf(asal, "/home/zulu/modul2/petshop/%s", entry3->d_name);
                sprintf(tujuan, "/home/zulu/modul2/petshop/%s/%s", tmp2_jenis, tmp2_nama);
                char *command[] = {"cp", "-r", asal, tujuan, NULL};
                execv("/bin/cp", command);
            }
            
            
            while(wait(&state_1) > 0);
            char ket[300];
            sprintf(ket, "/home/zulu/modul2/petshop/%s/keterangan.txt", tmp2_jenis);
            FILE *filep;
            filep = fopen(ket, "a+");
            fprintf(filep, "nama : %s\n", tmp2_nama);
            fprintf(filep, "umur : %s tahun\n\n", tmp2_umur);
            fclose(filep);
            

            if(counter == 1) {
                pid_t cid;
                cid = fork();
                if(cid < 0) exit(0);
                if(cid == 0) {
                    char asal[300], tujuan[300];
                    sprintf(asal, "/home/zulu/modul2/petshop/%s", entry3->d_name);
                    sprintf(tujuan, "/home/zulu/modul2/petshop/%s/%s", tmp3_jenis, tmp3_nama);
                    char *command[] = {"cp", "-r", asal, tujuan, NULL};
                    execv("/bin/cp", command);
                }
                
                while(wait(&state_2) > 0);
                char ket[300];
                sprintf(ket, "/home/zulu/modul2/petshop/%s/keterangan.txt", tmp3_jenis);
                FILE *filep;
                filep = fopen(ket, "a+");
                fprintf(filep, "nama : %s\n", tmp3_nama);
                fprintf(filep, "umur : %s tahun\n\n", tmp3_umur);
                fclose(filep);
            }
        }
    }
    
    while(wait(&state_4) > 0);
    DIR *dirp4;
    struct dirent *entry4;
    dirp4 = opendir("/home/zulu/modul2/petshop");
    while((entry4 = readdir(dirp4)) != NULL) {
        if((entry4->d_type == DT_REG) && strcmp(entry4->d_name, ".") != 0 && strcmp(entry4->d_name, "..") != 0){
            pid_t cid;
            cid = fork();
            if(cid < 0) exit(0);
            if(cid == 0) {
                char foldername[300];
                sprintf(foldername, "/home/zulu/modul2/petshop/%s", entry4->d_name);
                char *command[] = {"rm", "-r", foldername, NULL};
                execv("/bin/rm", command);
            }
        }
    }
}
