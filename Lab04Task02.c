#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <dirent.h>

//program that uses dup to detect a palindrome within an input file.

//checks file descriptors fd1 and fd2 and reads the two in reverse orders (fd1: left to right
//fd2: right to left).
int isPal(int fd1, int fd2){
    char c1[1];
    char c2[1];
    int isPali = 1;
    int n = lseek(fd2,-2,SEEK_END);
    printf("%c",*c2);
    lseek(fd1,0,SEEK_SET);
    int nread = 0;
    int l = 0;
    while((nread = read(fd1,c1,1) > 0 && (n-l) >=0)){
        lseek(fd2,-l-2,SEEK_END);
        int r = read(fd2,c2,1); 
        if(nread < 0 || r < 0){
            printf("file read error\n");
            exit(-1);
        }
        if(*c1 != *c2){
            isPali = 0;
        }
        l=l+1;
        lseek(fd1,l,SEEK_SET);
    }

    return isPali;
}

//main function. takes one parameter: fd1 and uses dup to make a copy in fd2
int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Invalid number of arguments.\n");
        exit(-1);
    }
    int fd1,fd2;
    fd1 = open(argv[1],O_RDONLY);
    fd2 = dup(fd1);
    if(fd1 < 0 || fd2 < 0){
        printf("file open or dup file error\n");
        exit(-1);
    }
    if(isPal(fd1,fd2) == 1){
        printf("File contains a palindrome. \n");
    } else {
        printf("File does not contain a palindrome.\n");
    }
    close(fd1);
    close(fd2);
    exit(0);
}
