#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* args[]) {

    if (argc != 2){
        printf("Incorrect number of arguments\n");
        exit(-1);
    }
    struct stat x;
    stat(args[1],&x);

    struct stat lx;
    lstat(args[1],&lx);

    if (S_ISLNK(lx.st_mode)){
        printf("LINK: %s\n",args[1]);
        printf("\tPERMISSIONS: %o\n",lx.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
        printf("\tHARD LINKS: %lu\n",lx.st_nlink);
        printf("\tSIZE: %lu\n",lx.st_size);
        printf("\tINODE: %lu\n",lx.st_ino);
        printf("\tLAST MODIFICATION: %s\n\n",ctime(&lx.st_mtime));

        char *linkname = malloc(128);
        long r = readlink(args[1],linkname,127);
        linkname[r] = '\0';
        printf("FILE WHERE %s LINKS %s\n",args[1],linkname);
        printf("\tPERMISSIONS: %o\n",x.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
        printf("\tHARD LINKS: %lu\n",x.st_nlink);
        printf("\tSIZE: %lu\n",x.st_size);
        printf("\tINODE: %lu\n",x.st_ino);
        printf("\tLAST MODIFICATION: %s\n",ctime(&x.st_mtime));

    }else if (S_ISREG(x.st_mode)){
        printf("TYPE: Regular file\n");
        printf("PERMISSIONS: %o\n",x.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
        printf("HARD LINKS: %lu\n",x.st_nlink);
        printf("SIZE: %lu\n",x.st_size);
        printf("INODE: %lu\n",x.st_ino);
        printf("LAST MODIFICATION: %s\n",ctime(&x.st_mtime));
    }else if (S_ISDIR(x.st_mode)){
        printf("TYPE: Directory\n");
        printf("PERMISSIONS: %o\n",x.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
        printf("HARD LINKS: %lu\n",x.st_nlink);
        printf("SIZE: %lu\n",x.st_size);
        printf("INODE: %lu\n",x.st_ino);
        printf("LAST MODIFICATION: %s\n",ctime(&x.st_mtime));
    }

    return 0;
}

/*
 *  a) because they are the same file
 *
 *  b) because it stores the path to de linked file which is stored in the symlink file
 *
 *  c) They match because they are the same file, (just different paths pointing to the same inode). Modifying one file modifies the other one because they are the same file.
 */