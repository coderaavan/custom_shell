#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(int argc, char *argv[]){
  int fd = open(argv[1],O_RDONLY);
  if(fd<0){
    printf("Illegal command or arguements\n");
    exit(0);
  }
  dup2(fd,0);
  //char input[10000];
  //int c=read(0,input,10000);
  int status;
  pid_t child;
  fflush(stdout);
  child = fork();
  fflush(stdout);
  if (child!=0){
    waitpid(child, &status, 0);
    char input[10000];
    int c=read(0,input,10000);
    int i=0;
    for(i=0;i<c;i++){
      printf("%c",input[i]);
    }
  }
  else{
    char *eargs[]={"sort","-f",NULL};
    fflush(stdout);
    execvp("sort",eargs);
    fflush(stdout);
  }
}
