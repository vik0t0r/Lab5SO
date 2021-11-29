#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char* args[]) {
    struct stat x;
    if (argc != 2){
        printf("Incorrect number of arguments\n");
        exit(-1);
    }

    stat(args[1],&x);
    if (S_ISREG(x.st_mode)){
        printf("TYPE: Regular file\n");
    }else if (S_ISDIR(x.st_mode)){
        printf("TYPE: Directory\n");
    }

    printf("PERMISSIONS: %o\n",x.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
    printf("HARD LINKS: %lu\n",x.st_nlink);
    printf("SIZE: %lu\n",x.st_size);
    printf("INODE: %lu\n",x.st_ino);
    printf("LAST MODIFICATION: %s\n",ctime(&x.st_mtime));


    return 0;
}
