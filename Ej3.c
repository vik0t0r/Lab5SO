#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

void prirntDir(const char* path){
    DIR *dirp;
    struct dirent *direntp;


    dirp = opendir(path);
    char type = 'U'; //unknown defaults

    char *linkname = malloc(128);
    strcpy(linkname,"");

    printf("Directory %s contains:\n",path);
    while ((direntp = readdir(dirp))!= NULL){
        if(direntp->d_type == DT_DIR){
            type ='D';
        } else if(direntp->d_type == DT_REG) {
            type = 'R';
        } else if(direntp->d_type == DT_LNK){
            type = 'L';

            // calculate path which is pointing the symbolic link
            strcpy(linkname,"-> ");

            char *l_path = strcat(path,"/"); // building path to call readlink on symbolik link
            l_path = strcat(l_path,direntp->d_name);
            long r = readlink(l_path,&linkname[3],125);
            linkname[r+3] = '\0';

        }
        printf("%c %s/%s %s\n",type,path,direntp->d_name,linkname);
        strcpy(linkname,""); // reset linkname
    }
}



int main(int argc, char* argv[]) {
    if (argc != 2){
        printf("Incorrect number of arguments\n");
        exit(-1);
    }

    struct stat stat_dir;
    if (stat(argv[1], &stat_dir) == -1){
        printf("Directory does not exist, creating one NOW\n");
        mkdir(argv[1],0775); // no hace falta comprobarlo porque ya lo hace la funcion

    }else if (!S_ISDIR(stat_dir.st_mode)){
        printf("File given is not a directory\n");
        exit(-1);
    }

    prirntDir(argv[1]);
    exit(0);
}
