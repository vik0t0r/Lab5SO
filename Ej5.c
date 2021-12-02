#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int prirntDir(const char* path,unsigned long inode){
    DIR *dirp;
    struct dirent *direntp;
    int foundN = 0;


    dirp = opendir(path);
    char *linkname = malloc(128);
    strcpy(linkname,"");

    while ((direntp = readdir(dirp))!= NULL){
        if(direntp->d_type == DT_DIR){
            // recursivity
            if(strcmp(direntp->d_name,".") != 0 && strcmp(direntp->d_name,"..") != 0) {
                char *recPath = malloc(1024);
                strcpy(recPath,path);
                recPath = strcat(recPath,"/");
                recPath = strcat(recPath,direntp->d_name);
                foundN += prirntDir(recPath,inode);
            }
        } else if(direntp->d_type == DT_REG) {
            char *sPath = malloc(1024);
            strcpy(sPath,path);
            sPath = strcat(sPath,"/");
            sPath = strcat(sPath,direntp->d_name);
            struct stat file;
            stat(sPath,&file);
            if (file.st_ino == inode){
                printf("(%lu) %s\n",file.st_ino,sPath);
                foundN += 1;
                // imprimimos inodo
            }
        }
    }
    return foundN;
}



int main(int argc, char* argv[]) {
    if (argc != 3){
        printf("Incorrect number of arguments\n");
        exit(-1);
    }
    // check first arg
    struct stat stat_dir;
    if (stat(argv[1], &stat_dir) == -1){
        printf("Directory does not exist, exiting\n");
        exit(-1);

    }else if (!S_ISDIR(stat_dir.st_mode)){
        printf("ARG 1 must be a directory\n");
        exit(-1);
    }
    // check second arg
    if (lstat(argv[2], &stat_dir) == -1) {
        printf("ARG 2 does not exist, exiting \n");
        exit(-1);
    } else if(!S_ISREG(stat_dir.st_mode)){
        printf("ARG 2 must be a regular file\n");
        exit(-1);
    }

    //print inode
    printf("Inode of file: %s : %lu\n\n",argv[2],stat_dir.st_ino);
    printf("Hard links to %s:\n",argv[2]);

    int hard_links = prirntDir(argv[1],stat_dir.st_ino);
    printf("Total number of hard links: %d\n",hard_links);

    exit(0);
}
/*
 * mkdir dir1
 * mkdir dir1/dir2
 * touch fileH
 * touch dir1/decoy1
 * touch dir1/dir2/decoy2
 * ln fileH dir1/H
 * ln fileH dir1/dir2/H2
 * ln -s ../fileH dir1/Hs
 * ln -s H dir1/Hs2
 * gcc Ej5.c -o Ej5
 * ./Ej5 dir1 fileH
 * OUTPUT:
Inode of file: fileH : 11545268

Hard links to fileH:
(11545268) dir1/H
(11545268) dir1/dir2/H2
Total number of hard links: 2

 * ./Ej5 dir1 dir1/Hs
 * OUTPUT:
ARG 2 must be a regular file

 *
 */

