#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <dirent.h>

//program that simulates the mv command. moving a file from one location to another.
int main(int argc, char *argv[]){
    umask(0);
    if(argc != 3){
        printf("Invalid number of arguments. \n");
        exit(-1);
    }
int l = link(argv[1],argv[2]);
if(l < 0){
    //concatinates argv[1] in front of argv[2] under the assumption that argv[2] is a directory, thereby making a copy of argv[1] in the directory argv[2].
    int ar1 = 0;
    int ar2 = 0;
    //finds sizes of argv[1] and argv[2]
    while(argv[2][ar2] != '\0'){
        ar2++;
    }
    while(argv[1][ar1] != '\0'){
        ar1++;
    }
    char arg1[ar1];
    char arg2[ar2];
    //copies contents of argv[1] and argv[2] (not 100% sure if this is necessary, but I put it in there just in case.)
    for(int i = 0; i < ar1; i++){
        arg1[i] = argv[1][i];
    }
    for(int i = 0; i < ar2; i++){
        arg2[i] = argv[2][i];
    }
    //find total size. +1 is for the / that designates the argv[1] at the end as a file in argv[2].
    int size = ar1 + ar2 + 1;
    char argcon[size];
    for(int i = 0; i < ar2; i++){
        argcon[i] = arg2[i];
    }
    //inserts / between the strings.
    argcon[ar2] = '/';
    //generates second part of the string past /
    for(int i = ar2+1; i < size; i++){
        argcon[i] = arg1[i-(ar2+1)];
    }
    //links argv[1] and the complete string location together.
    int l = link(arg1,argcon);
    //just in case linking fails.
    if (l < 0){
        printf("linking failure. \n");
        exit(-1);
    }
}
//unlinks argv[1] from original location.
int e = unlink(argv[1]);
if(e < 0){
    printf("file unlinking error\n");
    exit(-1);
}
exit(0);
}
