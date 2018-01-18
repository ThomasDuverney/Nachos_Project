#include "syscall.h"

#define DEBUG 0
#define NBMAXARGS 8
#define MAXLENGTHCMD 40
#define MAX_SIZE 100

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

int atoi(char * str){
    int resultat = 0;  // Initialisation du résultat
    int sign = 1;  // Initialisation du flag signe comme positif
    int i = 0;

    /* Si le première caractère de la chaine est "-" alors le nombre
       est négatif */
    if (str[0] == '-')
        {
            sign = -1;
            i++;
        }

    /* Itère sur chaque caractère de la chaine et met à jour le résultat */
    for (; str[i] != '\0'; ++i)
        resultat = resultat*10 + str[i] - '0';

    // Retourne le résultat avec le signe correspondant
    return sign*resultat;
}

void cat(char * filename){
    int fd = Open(filename);
    char buffer[MAX_SIZE];
    while(Read(buffer,MAX_SIZE,fd)!=0){
        PutString(buffer);
    }
    Close(fd);
    PutString("\n");
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
                if(index_cmdline < 5){
                    PutString("Too few arguments\n");
                    continue;
                } else {
                    SendMessage(atoi(cmdline[1]),atoi(cmdline[2]),atoi(cmdline[3]),cmdline[4]);
                }
            } else if(strcmp(cmdline[0], "receive") == 1){
                if(index_cmdline < 2){
                    PutString("Too few arguments\n");
                    continue;
                } else {
                    char message[50];
                    ReceiveMessage(message,atoi(cmdline[1]));
                    PutString(message);
                }
            } else if(strcmp(cmdline[0], "cat") == 1){
                if(index_cmdline < 2){
                    PutString("Too few arguments\n");
                    continue;
                } else {
                    cat(cmdline[1]);
                }
            } else {
                PutString("Error command not found\n");
            }
        
        } /* fin if index_cmdline > 0 */
        
    } /* fin while(1) */


    return 0;
}
