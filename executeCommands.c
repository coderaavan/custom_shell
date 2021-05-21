#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include"shellfunc.c"
#include"shellread.c"

int main(int argc, char *argv[]){
  int fd = open(argv[1],O_RDONLY);
  if(fd<0){
    printf("Illegal command or arguements\n");
    exit(0);
  }
  char input[10000],args_ls[10000];
  int c=read(fd,input,10000);
  int k=0;
  for(int i=0;i<c;i++){
    if(input[i]=='\n'||input[i]=='\0'){
      args_ls[k]='\0';
      k=0;
      shellread(args_ls);
    }
    else{
      args_ls[k]=input[i];
      k++;
    }
  }
}
