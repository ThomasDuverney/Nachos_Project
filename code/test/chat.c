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
        PutString(buf);
        PutString("\nEntrez le message :\n");
    }
}

int main (){
    char cmd[100];
    int boxFrom, addrTo, boxTo;

    PutString("Sur quelle boite souhaitez-vous écouter ? ");
    GetInt(&boxFrom);
    PutString("\nA quelle adresse souhaitez-vous tchatter ? ");
    GetInt(&addrTo);
    PutString("\nA quelle box souhaitez-vous tchatter ? ");
    GetInt(&boxTo);
    p.boxFrom = boxFrom;
    UserThreadCreate(reception,0);

    while(1){
        PutString("Entrez le message :\n");
        GetString(cmd,100);
        SendMessage(addrTo, boxTo, boxFrom, cmd);
    }
    return 0;
}
