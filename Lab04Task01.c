#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <dirent.h>

//program that takes an input file and searches the file for numbers and combines them
//using multiple functions.

//directly converts a single character digit into an int
int strToInt(char x){
if(x == '0'){
    return 0;
}
if(x == '1'){
    return 1;
}
if(x == '2'){
    return 2;
}
if(x == '3'){
    return 3;
}
if(x == '4'){
    return 4;
}
if(x == '5'){
    return 5;
}
if(x == '6'){
    return 6;
}
if(x == '7'){
    return 7;
}
if(x == '8'){
    return 8;
}
if(x == '9'){
    return 9;
}
}

//function to replicate an exponential operation.
double expon(int carrot){
    double b = 1;
    for(int i = 0; i <= carrot; i++){
        b = b * 10;
    }
    return b;
}

//function that converts an integer into a string.
int convIntToStr(char *str, int x){
sprintf(str, "%d", x);
return (strlen(str));
}

//main function. takes 1 command line argument to use.
int main(int argc, char *argv[]){
if (argc > 1 && argc < 3){
char b[1];
int nread = 0;
int floomp = 0;
int expo = 0;
int total = 0;
int flo = 0;
floomp = open(argv[1], O_RDONLY);
if(floomp != 0 && floomp != -1){
    //reads all entries of the file and adds all integers together.
while(nread = read(floomp,b,1)){
    if(nread < 0){
        printf("file read error\n");
        exit(1);
    }
int l = *b;
if(l >= 48 && l <= 57){
int f = strToInt(*b);
total = total + f;
total = total * 10;
flo = flo++;
}
}
//adjusts total to add 10.
total = total / 10;
total = total + 10;
char pl[flo];
int pls = 0;
//converts total to a string.
pls = convIntToStr(pl,total);
//writes total to screen.
int h = write(1,pl,pls);
if(h < 0){
    printf("file write error");
    exit(-1);
}
printf("\n");

} else {
    printf("opening error \n");
    exit(-1);
}
} else {
    printf("Not enough or too many arguments \n");
    exit(-1);
}
exit(0);
}
