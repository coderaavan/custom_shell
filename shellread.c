void shellread(char input[1000]){
  char *inp[1000];
  char *ptr = strtok(input," ");
  int arg_c=0;
  int para_flag = 0, arg_c_p1=0, arg_c_p2=0, inp_flag = -1, op_flag = -1, pipe_flag = 0;
  while(ptr!=NULL){
    inp[arg_c]=ptr;
    if(strcmp(ptr,";")==0){
      para_flag = 1;
      arg_c_p1 = arg_c;
    }
    else if(strcmp(ptr,"<")==0){
      inp_flag = arg_c+1;
    }
    else if((strcmp(ptr,">")==0)||(strcmp(ptr,">>")==0)) {
      op_flag = arg_c+1;
    }
    else if(strcmp(ptr,"|")==0){
      pipe_flag = 1;
    }
    arg_c++;
    ptr = strtok(NULL, " ");
  }

  char *args[arg_c+1];
  for(int i=0;i<arg_c;i++){
    args[i]=inp[i];
  }
  args[arg_c]=NULL;


  if(para_flag){
    arg_c_p2 = arg_c - arg_c_p1 - 1;
    char *args_p1[arg_c_p1+1], *args_p2[arg_c_p2+1];
    int flip = 0,j=0;
    for(int i=0;i<arg_c;i++){
      if(flip==0){
        if(strcmp(args[i],";")==0){
          flip=1;
          j=0;
          continue;
        }
        args_p1[j]=args[i];
        j++;
      }
      else{
        args_p2[j]=args[i];
        j++;
      }
    }
    args_p1[arg_c_p1]=NULL;
    args_p2[arg_c_p2]=NULL;
    pid_t child_m1, child_m2;
    int status_m1, status_m2;
    child_m1 = fork();
    if(child_m1==0){
      shellfunc(arg_c_p1,args_p1,inp_flag,op_flag,pipe_flag);
      exit(3);
    }
    else{
      child_m2 = fork();
      if(child_m2==0){
        shellfunc(arg_c_p2,args_p2,inp_flag,op_flag,pipe_flag);
        exit(3);
      }
      else{
        waitpid(child_m1, &status_m1, 0);
        waitpid(child_m2, &status_m2, 0);
      }
    }
  }
  else{
    shellfunc(arg_c,args,inp_flag,op_flag,pipe_flag);
  }
}
