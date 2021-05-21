#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
  FILE *fptr = fopen("files.txt","w");
  /*if(fptr==NULL){
    printf("File was not created\n");
  }*/
  fclose(fptr);
  char *eargs[]={"ls",NULL};
  int fd = open("files.txt",O_WRONLY);
  dup2(fd,1);
  execvp("ls",eargs);
}
