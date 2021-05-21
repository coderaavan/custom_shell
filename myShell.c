#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#include"shellfunc.c"
#include"shellread.c"

void handlerint(int sig)
{
    char msg[]="the program is interrupted, do you want to exit [Y/N]​";
    write(1,msg,53);
    char response[1];
    int r = read(0,response,1);
    if(r==1 && response[0]=='Y'){
      fflush(stdout);
      exit(0);
    }
}

void handlerterm(int sig)
{
    char msg[]="Got SIGTERM-Leaving​";
    write(1,msg,19);
    exit(0);
}

int main(int argc, char *argv[])
{
  while(1)
  {


    signal(SIGINT, handlerint);
    signal(SIGTERM, handlerterm);
    char msg[]="myShell> ";
    write(1,msg,10);
    char input[1000];

    int c = read(0,input,1000);
    if(input[0]=='\n'){
      continue;
    }

    input[c-1]='\0';
    int q=0,read_flag=0;
    while(input[q]!='\0'){
      if(!(input[q]==' ')){
        read_flag=1;
        break;
      }
      q++;
    }
    if(read_flag==0){
      continue;
    }
    if(strcmp(input,"exit")==0){
      exit(0);
    }
    shellread(input);
  }
}
