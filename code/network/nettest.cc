// nettest.cc
//	Test out message delivery between two "Nachos" machines,
//	using the Post Office to coordinate delivery.
//
//	Two caveats:
//	  1. Two copies of Nachos must be running, with machine ID's 0 and 1:
//		./nachos -m 0 -o 1 &
//		./nachos -m 1 -o 0 &
//
//	  2. You need an implementation of condition variables,
//	     which is *not* provided as part of the baseline threads
//	     implementation.  The Post Office won't work without
//	     a correct implementation of condition variables.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"

#include "system.h"
#include "network.h"
#include "post.h"
#include "interrupt.h"
#include <unistd.h>
#include <string>

// Test out message delivery, by doing the following:
//	1. send a message to the machine with ID "farAddr", at mail box #0
//	2. wait for the other machine's message to arrive (in our mailbox #0)
//	3. send an acknowledgment for the other machine's message
//	4. wait for an acknowledgement from the other machine to our
//	    original message

void MailTest(int farAddr) {
    // PacketHeader outPktHdr, inPktHdr;
    // MailHeader outMailHdr, inMailHdr;
    // const char *data = "Hello there!";
    // const char *ack = "Got it!";
    // char buffer[MaxMailSize];
    //
    // for (int i=0; i<10; i++){
    //
    //     // construct packet, mail header for original message
    //     // To: destination machine, mailbox 0
    //     // From: our machine, reply to: mailbox 1
    //     outPktHdr.to = farAddr;
    //     outMailHdr.to = 0;
    //     outMailHdr.from = 1;
    //     outMailHdr.length = strlen(data) + 1;
    //
    //     // Send the first message
    //     postOffice->Send(outPktHdr, outMailHdr, data);
    //
    //     // Wait for the first message from the other machine
    //     postOffice->Receive(0, &inPktHdr, &inMailHdr, buffer);
    //     printf("Got \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);
    //     fflush(stdout);
    //
    //     // Send acknowledgement to the other machine (using "reply to" mailbox
    //     // in the message that just arrived
    //     outPktHdr.to = inPktHdr.from;
    //     outMailHdr.to = inMailHdr.from;
    //     outMailHdr.length = strlen(ack) + 1;
    //     postOffice->Send(outPktHdr, outMailHdr, ack);
    //
    //     // Wait for the ack from the other machine to the first message we sent.
    //     postOffice->Receive(1, &inPktHdr, &inMailHdr, buffer);
    //     printf("Got \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);
    //     fflush(stdout);
    // }
    //
    // // Then we're done!
    // interrupt->Halt();
}

void MailTestRing(int farAddrPrev, int farAddrNext) {
    // PacketHeader outPktHdr, inPktHdr;
    // MailHeader outMailHdr, inMailHdr;
    // const char *token = "Jeton";
    // char buffer[MaxMailSize];
    //
    // // construct packet, mail header for original message
    // // To: destination machine, mailbox 0
    // // From: our machine, reply to: mailbox 1
    // if (farAddrNext == 2){
    //     outPktHdr.to = farAddrNext;
    //     outMailHdr.to = 0;
    //     outMailHdr.from = 1;
    //     outMailHdr.length = strlen(token) + 1;
    //
    //     // Send the first token
    //     postOffice->Send(outPktHdr, outMailHdr, token);
    //
    //     // Wait for the token from the prev machine
    //     postOffice->Receive(0, &inPktHdr, &inMailHdr, buffer);
    //     printf("Got \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);
    //     fflush(stdout);
    //
    //
    // } else {
    //
    //     // Wait for the token from the prev machine
    //     postOffice->Receive(0, &inPktHdr, &inMailHdr, buffer);
    //     printf("Got \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);
    //     fflush(stdout);
    //
    //     outPktHdr.to = farAddrNext;
    //     outMailHdr.to = 0;
    //     outMailHdr.from = 1;
    //     outMailHdr.length = strlen(buffer) + 1;
    //
    //     // Send the token to the next
    //     postOffice->Send(outPktHdr, outMailHdr, buffer);
    //
    // }

    // Then we're done!
    //interrupt->Halt();
}

void MailTestRingTCP(int farAddrPrev, int farAddrNext) {
    const char *token = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string buffer;
    PacketHeader pktHdr;
    MailHeader mailHdr;

    if (farAddrNext == 2){

        postOffice->Send(farAddrNext, 0, 1, token);
        buffer = postOffice->Receive(0, &pktHdr, &mailHdr);
        printf("RECU=%s\n", buffer.c_str());

    } else {

        // Wait for the token from the prev machine
        buffer = postOffice->Receive(0, &pktHdr, &mailHdr);
        printf("RECU=%s\n", buffer.c_str());
        postOffice->Send(farAddrNext, 1, 0, buffer.c_str());

    }

    // Then we're done!
    //interrupt->Halt();
}

void MailTestSendFile(int addrTo, const char* filename){
    postOffice->PutFile(addrTo, 1, 0, filename);
}

void MailTestReceiveFile(int addrTo, const char* filename){
    postOffice->GetFile(addrTo, 1, 0, filename);
}
