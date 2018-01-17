#include "syscall.h"

#define DEBUG 0
#define NBMAXARGS 8
#define MAXLENGTHCMD 40

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
    char cmdline[NBMAXARGS][MAXLENGTHCMD];
    int i,j;
    int z;
    int index_cmdline;

    while(1){
        index_cmdline = 0;
        PutString("Shell>> ");
        GetString(cmd,100);
        i=0;

        /* Séparation de la commande entrée par l'utilisateur */
        while (index_cmdline < NBMAXARGS && cmd[i] != '\n'){
            j=0;

            // on stocke 
            while(j < MAXLENGTHCMD - 1 && cmd[i] != ' ' && cmd[i] != '\n'){
                cmdline[index_cmdline][j] = cmd[i];
                i++;
                j++;
            }
            if(cmd[i] == ' '){
                i++;
            } else if(j >= MAXLENGTHCMD -1){
                PutString("passe\n");
                break;
            }
            cmdline[index_cmdline][j] = '\0';
            index_cmdline++;
        }

        if(index_cmdline >= NBMAXARGS){
            PutString("Too many arguments\n");
            continue;
        }
        if(j >= MAXLENGTHCMD -1){
            PutString("args too long\n");
            continue;
        }



        if(DEBUG){ /* DEBUG parse string */  
            for(z=0; z<index_cmdline; z++){
                PutString("Arg ");
                PutInt(z);
                PutString(": ");
                PutString(cmdline[z]);
                PutChar('\n');
            }
        }

        if(index_cmdline > 0){

            /* SWITCH sur les commandes */

            if(strcmp(cmdline[0], "mkdir") == 1){
                if(index_cmdline < 2){
                    PutString("Too few arguments\n");
                    continue;
                } else {
                    CreateDirectory(cmdline[1]);
                }


            } else if(strcmp(cmdline[0], "cd") == 1){
                if(index_cmdline < 2){
                    PutString("Too few arguments\n");
                    continue;
                } else {
                    ChangeDirectoryPath(cmdline[1]);
                }

            } else if(strcmp(cmdline[0], "rm") == 1){
                if(index_cmdline < 2){
                    PutString("Too few arguments\n");
                    continue;
                } else {
                    Remove(cmdline[1]);
                }
            } else if(strcmp(cmdline[0], "ls") == 1){
                if(index_cmdline < 2){
                    ListDirectory(".");
                } else {
                    ListDirectory(cmdline[1]);
                }
            } else if(strcmp(cmdline[0], "exit")){
                return 0;
            } else if(strcmp(cmdline[0], "exec") == 1){
                if(index_cmdline < 2){
                    PutString("Too few arguments\n");
                    continue;
                } else {
                    ForkExec(cmdline[1]);
                }
            } else if(strcmp(cmdline[0], "touch") == 1){
                if(index_cmdline < 2){
                    PutString("Too few arguments\n");
                    continue;
                } else {
                    Create(cmdline[1],1);
                }
            } else if(strcmp(cmdline[0], "send") == 1){
                PutString("Not implemented yet\n");
            } else if(strcmp(cmdline[0], "receive") == 1){
                PutString("Not implemented yet\n");
            } else {
                PutString("Error command not found\n");
            }
        
        } /* fin if index_cmdline > 0 */
        
    } /* fin while(1) */


    return 0;
}
