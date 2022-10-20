#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <dirent.h>

//program that takes input from a file and outputs different categories of characters to different
//output files. Specifically, alphanumeric characters, number characters, and characters in
//neither category.
int main(int argc,char *argv[]){
    if(argc != 6){
        printf("invalid number of arguments\n");
        exit(-1);
    }
    umask(0);
    int input = open(argv[1],O_RDONLY);
    int alpha = open(argv[2], O_RDWR | O_CREAT, 0666);
    int num = open(argv[3], O_RDWR | O_CREAT, 0666);
    int other = open(argv[4], O_RDWR | O_CREAT, 0666);
    int copy = open(argv[5], O_RDWR | O_CREAT, 0666);
    if(input<0 || alpha < 0 || num < 0 || other < 0 || copy < 0){
        printf("file open error.\n");
        exit(-1);
    }
    char b[1];
    int nread = 0;
    //partitions the input from input into alpha num and copy
    while((nread = read(input,b,1)>0)){
        if(nread < 0){
            printf("file read error\n");
            exit(-1);
        }
        if(*b >= '0' && *b <= '9'){
            write(num,b,1);
            write(alpha," ",1);
            write(other," ",1);
        } else if(*b >= 'a' && *b <= 'z'){
            write(alpha,b,1);
            write(num," ",1);
            write(other," ",1);
        } else if(*b >= 'A' && *b <= 'Z'){
            write(alpha,b,1);
            write(num," ",1);
            write(other," ",1);
        } else if(*b == ' '){
            write(alpha," ",1);
            write(num," ",1);
            write(other," ",1);
        } else if(*b == '\n'){
            write(alpha,"\n",1);
            write(num,"\n",1);
            write(other,"\n",1);
        } else {
            write(other,b,1);
            write(num," ",1);
            write(alpha," ",1);
        }
    }
    //3 buffers for each of the partitioned inputs
    char a[1];
    char n[1];
    char o[1];
    int nread2 = 0;
    //lseeks so the last section functions well.
    lseek(alpha,0,SEEK_SET);
    lseek(num,0,SEEK_SET);
    lseek(other,0,SEEK_SET);
    //while loop to finish the copy.
    int rn,ro,wr = 0;
    while((nread2 = read(alpha,a,1)>0)){
        rn = read(num,n,1);
        ro = read(other,o,1);
        if(nread2 < 0 || rn < 0 || ro < 0){
            printf("file read error");
            exit(-1);
        }
        //does what the while statement at the start does, but in reverse. Instead of
        //splitting one input into multiple outputs, it takes multiple inputs and combines them 
        //into one output.
        if(*n >= '0' && *n <= '9'){
            wr = write(copy,n,1);
        } else if((*a >= 'a' && *a <= 'z') || (*a >= 'A' && *a <= 'Z')){
            wr = write(copy,a,1);
        } else if(*a == *n == *o == ' '){
            wr = write(copy," ",1);
        } else if(*a == *n == *o =='\n'){
            wr = write(copy,"\n",1);
        } else {
            wr = write(copy,o,1);
        }
        if(wr < 0){
            printf("file write error\n");
            exit(-1);
        }
    }
    


    exit(0);
}
