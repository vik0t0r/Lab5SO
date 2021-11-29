#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char* args[]) {
    if (argc != 2){
        printf("Incorrect number of arguments\n");
        exit(-1);
    }
    mkdir(args[1],0775);


    struct dirent *d = readdir(opendir(args[1]));



    exit(0);
}
