#include "syscall.h"

#define IDLE 0
#define CD 1
#define RM 2
#define LS 3
#define MKDIR 4



int main (){
  char cmd[100];
  char buff[30];
  int i, j;

  int state;

  while(1){
      state = IDLE;
      PutString("Shell>> ");
      GetString(cmd,100);
      i=0;
	  while (cmd[i++] != '\n'){
          j=0;
          while(cmd[i++] != ' ' && cmd[i++] != '\n'){
            buff[j] = cmd[i];
            j++;
          }
          buff[j] = '\0';

          switch(state){
          case IDLE:
            if(!strcmp(
            break;

          }


      }
  }
  return 0;
}
