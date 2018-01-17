#include "syscall.h"

#define STOP 0
#define IDLE 1

struct threadParam{
    int boxFrom;
    char* otherName;
};
struct threadParam p;

void reception(void *arg) {
    char buf[100];
    int box = p.boxFrom;
    while(1){
        ReceiveMessage(buf, box);
 //       PutString(p.otherName);
        PutString(buf);
    }
}

// int strcmp(char *s1, char *s2){
//     int i = 0;
//     while(s1[i] != '\0'){
//         if(s1[i] != s2[i]){
//             return 0;
//         }
//         i++;
//     }
//     return 1;
// }

int main (){
    char cmd[100];
 //   char selfName[30];
 //   char otherName[30];
    int state, boxFrom, addrTo, boxTo;

    PutString("Sur quelle boite souhaitez-vous écoutez ? ");
    GetInt(&boxFrom);
    PutInt(boxFrom);
    PutString("\nA quelle adresse souhaitez-vous tchatter ? ");
    GetInt(&addrTo);
    PutString("\nA quelle box souhaitez-vous tchatter ? ");
    GetInt(&boxTo);
 //   PutString("\nQuel est votre nom ? ");
 //   GetString(selfName, 30);
 //   SendMessage(addrTo, boxTo, boxFrom, selfName);
 //   ReceiveMessage(otherName, boxFrom);
    p.boxFrom = boxFrom;
 //   p.otherName = (char*) otherName;
    UserThreadCreate(reception,0);
    state = IDLE;
    while(!state){
        GetString(cmd,100);
 //       PutString(selfName);
        PutString(cmd);
        SendMessage(addrTo, boxTo, boxFrom, cmd);
    }
    return 0;
}
