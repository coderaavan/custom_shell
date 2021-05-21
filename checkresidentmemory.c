#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char *argv[]){
  //printf("%s\n",argv[1]);
  char *eargs[] = {"ps","-p",argv[1],"-o","rss=",NULL};
  fflush(stdout);
  int err = execvp("ps",eargs);
  fflush(stdout);
  if(err<0){
    printf("Illegal command or arguements\n");
    exit(0);
  }
  return 0;
}
