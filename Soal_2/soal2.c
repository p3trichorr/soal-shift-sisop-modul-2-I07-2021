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
    int state_1, state_2, state_3;
    
    pid_t cid;
    cid = fork();
    if(cid < 0) exit(0);
    if(cid == 0) {
        char *command[] = {"unzip", "pets", "*.jpg", "-d", "/home/zulu/modul2/petshop", NULL};
        execv("/bin/unzip", command);
    }
    
    while(wait(&state_1) > 0);
    DIR *pdr1;
    struct dirent *entry1;
    pdr1 = opendir("/home/zulu/modul2/petshop");
    char foldername[100][300];
    int n = 0;
    while((entry1 = readdir(pdr2)) != NULL) {
        if(entry1->d_type == DT_REG) {
            char tmp[300], tmp2[300];
            memset(foldername[n], 0, sizeof(foldername[n]));
            memset(tmp2, 0, sizeof(tmp2));
            strcpy(tmp, entry1->d_name);
            
            int i, found = 0;
            for(i = 0; i < strlen(tmp); i++) {
                if(tmp[i] == ';') break;
                tmp2[i] = tmp[i];
            }
            
            for(i = 0; i < n && found == 0; i++)
                if(strcmp(foldername[i], tmp2) == 0)
                    found = 1;
            
            if(found == 0) {
                strcpy(foldername[n], tmp2);
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
            sprintf(tmp, "/home/zulu/modul2/petshop/%s", foldername[i]);
            char *command[] = {"mkdir", tmp, NULL};
            execv("/bin/mkdir", command);
        }
    }
    
    while(wait(&state_2) > 0);
    DIR *pdr2;
    struct dirent *entry2;
    pdr3 = opendir("/home/zulu/modul2/petshop");
    while((entry2 = readdir(pdr2)) != NULL) {
        if(entry2->d_type == DT_REG) {
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
            
            int i, l, found = 0, counter = 0;
            for(i = 0; i < strlen(tmp); i++) {
                if(tmp[i] == ';') break;
                tmp2_jenis[i] = tmp[i];
            }
            
            i++; l = i;
            for(; i < strlen(tmp); i++) {
                if(tmp[i] == ';') break;
                tmp2_nama[i-l] = tmp[i];
            }
            
            i++; l = i;
            for(; i < strlen(tmp); i++) {
                if(tmp[i] == '_' || (tmp[i] == '.' && tmp[i+1] == 'j')) break;
                tmp2_umur[i-l] = tmp[i];
            }
            
            if(tmp[i] == '_') {
                i++; l = i;
                for(; i < strlen(tmp); i++) {
                    if(tmp[i] == ';') break;
                    tmp3_jenis[i-l] = tmp[i];
                }
                
                i++; l = i;
                for(; i < strlen(tmp); i++) {
                    if(tmp[i] == ';') break;
                    tmp3_nama[i-l] = tmp[i];
                }
                
                i++; l = i;
                for(; i < strlen(tmp); i++) {
                    if(tmp[i] == '.' && tmp[i+1] == 'j') break;
                    tmp3_umur[i-l] = tmp[i];
                }
                
                counter = 1;
            }
            
            int state_1, state_2;
            pid_t cid;
            cid = fork();
            if(cid < 0) exit(0);
            if(cid == 0) {
                char asal[300], tujuan[300];
                sprintf(asal, "/home/zulu/modul2/petshop/%s", entry2->d_name);
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
                    sprintf(asal, "/home/zulu/modul2/petshop/%s", entry2->d_name);
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
                char foldername[300];
                sprintf(foldername, "/home/zulu/modul2/petshop/%s", entry3->d_name);
                char *command[] = {"rm", "-r", foldername, NULL};
                execv("/bin/rm", command);
            }
        }
    }
}
