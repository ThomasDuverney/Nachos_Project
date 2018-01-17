#include "syscall.h"

#define IDLE 0
#define CD 1
#define RM 2
#define LS 3
#define MKDIR 4
#define EXEC  5
#define TOUCH  6
#define SEND  7
#define RECEIVE  8

int strcmp(char *s1, char *s2){
    int i = 0;
    while(s1[i] != '\0'){
        if(s1[i] != s2[i]){
            return 0; // les chaines ne sont pas les memes
        }
        i++;
    }

    return 1;
}

int main (){
    char cmd[100];
    char buff[30];
    char cmdline[8][40];
    int i,j,state;
    int stopped = 0;
    int index_cmdline;

    while(1){
        state = IDLE;
        index_cmdline = 0;
        PutString("Shell>> ");
        GetString(cmd,100);
        i=0;
        stopped = 0;

        while (cmd[i] != '\n'){
            j=0;

            // on stocke 
            while(cmd[i] != ' ' && cmd[i] != '\n'){
                cmdline[index_cmdline][j] = cmd[i];
                i++;
                j++;
            }
            index_cmdline++;
        }


            j++;
            buff[j] = '\0';

            switch(state){
            case IDLE:
                if(strcmp(buff, "mkdir") == 1){
                    state = MKDIR;
                } else if(strcmp(buff, "cd") == 1){
                    state = CD;
                } else if(strcmp(buff, "rm") == 1){
                    state = RM;
                } else if(strcmp(buff, "ls") == 1){
                    if(cmd[i] == '\n'){
                        ListDirectory(".");
                        state = IDLE;
                        stopped = 1;
                    } else {
                        state = LS;
                    }
                } else if(strcmp(buff, "exit")){
                    state = IDLE;
                    return 0;
                } else if(strcmp(buff, "exec") == 1){
                    state =EXEC;
                } else if(strcmp(buff, "touch") == 1){
                    state =TOUCH;
                } else if(strcmp(buff, "send") == 1){
                    state =SEND;
                } else if(strcmp(buff, "receive") == 1){
                    state = RECEIVE;
                } else {
                    PutString("Error command not found\n");
                }
                break;
            case CD:
                ChangeDirectoryPath(buff);
                stopped = 1;
                state = IDLE;
                break;
            case MKDIR:
                CreateDirectory(buff);
                stopped = 1;
                state = IDLE;
                break;
            case LS:
                ListDirectory(buff);
                stopped = 1;
                state = IDLE;
                break;
            case RM:
                Remove(buff);
                stopped = 1;
                state = IDLE;
                break;
            case EXEC:
                ForkExec(buff);
                stopped = 1;
                state = IDLE;
                break;
            case TOUCH:
                Create(buff,1);
                stopped = 1;
                state = IDLE;
                break;
            case SEND:
                Send(,,,1);
                state = IDLE;
                break;
            case RECEIVE:
                Receive(buff,1);
                stopped = 1;
                state = IDLE;
                break;
            default:
                PutString("Error state not found\n");
                return 1;
                break;
            }



    }
    return 0;
}
