#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"shellfunc.c"

int pipefd[2];

void io_func(char *argv[]){
  int i=0, inp=-1, op=-1;
  while(argv[i]!=NULL){
    if((strcmp(argv[i],"<")==0)){
      inp = i+1;
    }
    if((strcmp(argv[i],">")==0)||(strcmp(argv[i],">>")==0)){
      op = i+1;
    }
    i++;
  }
  int stdin_fd;
  if(inp>=0){
    stdin_fd = open(argv[inp],O_RDONLY);
    if(stdin_fd == -1){
      printf("Illegal command or arguements\n");
      exit(0);
    }
    dup2(stdin_fd,0);
  }
  int stdout_fd;
  if(op>=0){
    FILE *fptr = fopen(argv[op],"w");
    fclose(fptr);
    if((strcmp(argv[op-1],">>")==0))
    {
      stdout_fd = open(argv[op],O_APPEND|O_WRONLY);
      dup2(stdout_fd,1);
    }
    else if((strcmp(argv[op-1],">")==0))
    {
      stdout_fd = open(argv[op],O_TRUNC|O_WRONLY);
      dup2(stdout_fd,1);
    }
  }
  char *args_temp[i];
  i=1;
  int j=0, k=0;
  while(!(argv[i]==NULL||(strcmp(argv[i],"<")==0)||(strcmp(argv[i],">")==0)||(strcmp(argv[i],">>")==0))){
    //puts(argv[i]);
    args_temp[j]=argv[i];
    i++;
    j++;
  }

  char *args[i];
  for(k=0;k<j;k++){
    args[k]=args_temp[k];
  }
  args[i-1]=NULL;

  int status;
  pid_t child;
  int exec_ret = 0;

  fflush(stdout);
  child = fork();
  fflush(stdout);
  if(child<0){
    char error[150]="Not enough space for a new process.";
    write(1,error,150);
  }
  else if(child!=0){
    waitpid(child, &status, 0);
    close(stdin_fd);
    close(stdout_fd);
  }
  else{
    shellfunc(j,args,-1,-1,0);
  }
}

int main(int argc, char *argv[])
{
  int pipe_flag=0, i=0;
  while(argv[i]!=NULL){
    //puts(argv[i]);
    if((strcmp(argv[i],"|")==0)){
      pipe_flag=1;
    }
    i++;
  }
  if(pipe_flag==0){
    io_func(argv);
  }
  else{
    char *arg_pp_temp1[i], *arg_pp_temp2[i];
    i=1;

    int flip = 0, j=1, k=1;
    while(argv[i]!=NULL){
      if((strcmp(argv[i],"|")==0)){
        flip = 1;
        i++;
      }
      if(flip==0){
        arg_pp_temp1[j]=argv[i];
        j++;
      }
      else{
        arg_pp_temp2[k]=argv[i];
        k++;
      }
      i++;
    }

  char *arg_pp1[j+1], *arg_pp2[k+1];
  for(i=1;i<=j;i++){
    arg_pp1[i]=arg_pp_temp1[i];
  }
  for(i=1;i<=k;i++){
    arg_pp2[i]=arg_pp_temp2[i];
  }
  arg_pp1[0]=argv[0];
  arg_pp2[0]=argv[0];
  arg_pp1[j]=NULL;
  arg_pp2[k]=NULL;

  char buffer[10000];
  if (pipe(pipefd) == -1) {
      perror("pipe");
      exit(EXIT_FAILURE);
    }

  int status;
  pid_t child;
  int exec_ret = 0;

  fflush(stdout);
  child = fork();
  fflush(stdout);
  if(child<0){
    char error[150]="Not enough space for a new process.";
    write(1,error,150);
  }
  else if(child!=0){

    waitpid(child, &status, 0);
    dup2(pipefd[0],0);
    close(pipefd[1]);
    io_func(arg_pp2);
    close(pipefd[0]);
  }
  else{
    dup2(pipefd[1],1);
    close(pipefd[0]);
    io_func(arg_pp1);
    close(pipefd[1]);
  }
  }
}
