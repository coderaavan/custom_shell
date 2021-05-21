void shellfunc(int arg_c,char *args[], int inp, int op, int pipe_flag)
{
  int status;
  pid_t child;
  int exec_ret = 0;
  if(inp>=0 || op>=0 || pipe_flag == 1){
    fflush(stdout);
    child = fork();
    fflush(stdout);
    if(child<0){
      char error[150]="Not enough space for a new process.";
      write(1,error,150);
    }
    else if(child!=0){
      waitpid(child, &status, 0);
    }
    else{
      char *new_args[arg_c+2];
      new_args[0]="io";
      int i=0;
      for(i=0;i<arg_c+1;i++){
        new_args[i+1]=args[i];
      }

      new_args[arg_c+1]==NULL;
      fflush(stdout);
      exec_ret=execve(new_args[0],new_args,NULL);
      fflush(stdout);
      exit(3);
    }
  }
  else if((strcmp(args[0],"checkcpupercentage")==0)||(strcmp(args[0],"checkresidentmemory")==0)||(strcmp(args[0],"sortFile")==0)||(strcmp(args[0],"executeCommands")==0))
  {
    if(arg_c!=2){
      printf("Illegal command or arguements\n");
      return;
    }
    fflush(stdout);
    child = fork();
    fflush(stdout);
    if(child<0){
      char error[150]="Not enough space for a new process.";
      write(1,error,150);
    }
    else if(child!=0){
      waitpid(child, &status, 0);
    }
    else{
      fflush(stdout);
      exec_ret=execve(args[0],args,NULL);
      fflush(stdout);
      exit(3);
    }
  }
  else if(strcmp(args[0],"listFiles")==0)
  {
    if(arg_c!=1){
      printf("Illegal command or arguements\n");
      return;
    }
    fflush(stdout);
    child = fork();
    fflush(stdout);
    if(child<0){
      char error[150]="Not enough space for a new process.";
      write(1,error,150);
    }
    else if(child!=0){
      waitpid(child, &status, 0);
    }
    else{
      fflush(stdout);
      exec_ret=execve(args[0],args,NULL);
      fflush(stdout);
      exit(3);
    }
  }
  else{
    fflush(stdout);
    child = fork();
    fflush(stdout);
    if(child<0){
      char error[150]="Not enough space for a new process.";
      write(1,error,150);
    }
    else if(child!=0){
      waitpid(child, &status, 0);
    }
    else{
      fflush(stdout);
      exec_ret=execve(args[0],args,NULL);
      fflush(stdout);
      if(exec_ret==-1){
        if(strcmp(args[0],"grep")==0){
          int q=0, need_trim=0;
          while(args[1][q]!='\0'){
            q++;
          }
          if(((args[1][0]=='\"')&&(args[1][q-1]=='\"'))||((args[1][0]=='\'')&&(args[1][q-1]=='\''))){
            need_trim=1;
          }
          if(need_trim){
            char trim[q-1];
            int r=0;
            while(r<q-2){
              trim[r]=args[1][r+1];
              r++;
            }
            trim[q-2]='\0';
            strcpy(args[1],trim);
          }
        }
        fflush(stdout);
        exec_ret=execvp(args[0],args);
        fflush(stdout);
      }
      if(exec_ret==-1){
        printf("Illegal command or arguements\n");
      exit(3);
      }
    }
  }
}
