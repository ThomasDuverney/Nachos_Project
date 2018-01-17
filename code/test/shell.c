#include "syscall.h"

#define IDLE 0
#define CD 1
#define RM 2
#define LS 3
#define MKDIR 4
#define EXEC  5
#define TOUCH  6

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
    int i,j,state;
    int stopped = 0;

    while(1){
        state = IDLE;
        PutString("Shell>> ");
        GetString(cmd,100);
        i=0;
        stopped = 0;
        while (stopped == 0 && cmd[i] != '\n'){
            j=0;

            // on stocke 
            while(cmd[i] != ' ' && cmd[i] != '\n'){
                buff[j] = cmd[i];
                i++;
                j++;
            }
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
                    ListCurrentDirectory();
                    state = IDLE;
                    stopped = 1;
                } else if(strcmp(buff, "exec") == 1){
                    state =EXEC;
                } else if(strcmp(buff, "touch") == 1){
                    state =TOUCH;
                } else {
                    PutString("Error command not found");
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
            default:
                PutString("Error state not found");
                return 1;
                break;
            }

            if(cmd[i] == ' '){
                i++;
            }
        }
    }
    return 0;
}
