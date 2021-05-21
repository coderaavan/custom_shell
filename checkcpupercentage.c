#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
  char path[1000]="/proc/";
  strcat(path,argv[1]);
  strcat(path,"/stat");
  int fd=open(path,O_RDONLY);
  if(fd<0)
  {
    printf("Illegal command or arguements\n");
    exit(0);
  }
  char stat[1000];
  int r=read(fd,stat,1000);
  char utime[60],stime[60];
  char *ptr = strtok(stat," ");
  int att_c=1;
  while(ptr!=NULL){
    if(att_c==14){
      strcpy(utime,ptr);
    }
    if(att_c==15){
      strcpy(stime,ptr);
      break;
    }
    ptr = strtok(NULL, " ");
    att_c++;
  }
  close(fd);
  fd=open("/proc/stat",O_RDONLY);
  char sys_stat[1000];
  r=read(fd,sys_stat,1000);
  char sys_utime[60],sys_stime[60];
  ptr = strtok(sys_stat," ");
  int sys_att_c=1;
  unsigned long int cpu_sum1=0;
  while(ptr!=NULL){
    if((sys_att_c>=2)&&(sys_att_c<=10)){
     cpu_sum1 = cpu_sum1 + atoi(ptr);
    }
    if(sys_att_c == 11){
      cpu_sum1 = cpu_sum1 + atoi(&ptr[0]);
    }
    if(sys_att_c==12){
      break;
    }
    ptr = strtok(NULL, " ");
    sys_att_c++;
  }
  close(fd);
  unsigned long int ut1 = atoi(utime);
  unsigned long int st1 = atoi(stime);
  sleep(1);
  fd=open(path,O_RDONLY);
  r=read(fd,stat,1000);
  ptr = strtok(stat," ");
  att_c=1;
  while(ptr!=NULL){
    if(att_c==14){
      strcpy(utime,ptr);
    }
    if(att_c==15){
      strcpy(stime,ptr);
      break;
    }
    ptr = strtok(NULL, " ");
    att_c++;
  }
  close(fd);
  fd=open("/proc/stat",O_RDONLY);
  sys_stat[1000];
  r=read(fd,sys_stat,1000);
  ptr = strtok(sys_stat," ");
  sys_att_c=1;
  unsigned long int cpu_sum2=0;
  while(ptr!=NULL){
    if((sys_att_c>=2)&&(sys_att_c<=10)){
     cpu_sum2 = cpu_sum2 + atoi(ptr);
    }
    if(sys_att_c == 11){
      cpu_sum2 = cpu_sum2 + atoi(&ptr[0]);
    }
    if(sys_att_c==12){
      break;
    }
    ptr = strtok(NULL, " ");
    sys_att_c++;
  }
  unsigned long int ut2 = atoi(utime);
  unsigned long int st2 = atoi(stime);
  double u_cpu = ((((double)ut2-(double)ut1))/((double)cpu_sum2-(double)cpu_sum1))*100;
  double s_cpu = ((((double)st2-(double)st1))/((double)cpu_sum2-(double)cpu_sum1))*100;
  printf("user mode cpu percentage: %0.2lf\n",u_cpu);
  printf("system mode cpu percentage: %0.2lf\n",s_cpu);
  return 0;
}
