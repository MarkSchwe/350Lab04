#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <dirent.h>

//program that shows the functionality and use of symlink.
int main(){
    umask(0);
    //setup of each new directory
    mkdir("dir1",0666);
    mkdir("dir2",0666);
    chdir("dir2");
    mkdir("dir21",0666);
    chdir("..");
    //copies Hello executable to dir21 in the program since dir21 didnt exist before.
    char b[1];
    int l = open("Hello",O_RDONLY);
    if(l < 0){
        printf("file open error\n");
        exit(-1);
    }
    int nread = 0;
    int size = 0;
    while((nread = read(l,b,1) > 0)){
        size++;
        if(nread < 0){
            printf("file read error\n");
            exit(-1);
        }
    }
    char c[size];
    lseek(l,0,SEEK_SET);
    read(l,c,size);
    //heads to dir21 to input text to the other executable.
    chdir ("dir2");
    chdir ("dir21");
    int v = open("Hello",O_CREAT | O_RDWR,0777);
    int e = write(v,c,size);
    if(v < 0){
        printf("file open error\n");
        exit(-1);
    } else if (e < 0){
        printf("file write error\n");
        exit(-1);
    }
    close(v);
    close(l);
    //heads to dir1
    chdir("../../dir1");
    //links both hello and dir21 to links in dir1
    int g1 = symlink("../dir2/dir21/Hello","toHello");
    int g = symlink("../dir2/dir21","toDir21");
    if(g1 < 0 || g < 0){
        printf("symbolic link error\n");
        exit(-1);
    }
    exit(0);
}
