// Program to implement Echo Server using Message Qs
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
int wait();
struct msg
{
    long id;
    char m[10];
} m1, m2;

int main()
{
    int qid, pid, msgid, rval;

    system("clear");

    qid = msgget((key_t)10, IPC_CREAT | 0666);

    if (qid == -1)
    {
        perror("Q-CRE-ERR:");
        exit(1);
    }

    printf("\n ES-Q: Queue created with id = %d\n", qid);

    system("ipcs -q");

    printf("\nMP-ES-Q: Enter the message id for communication \n");
    scanf("%d", &msgid);

    pid = fork();

    if (pid == -1)
    {
        perror("FRK-ERR:");
        msgctl(qid, IPC_RMID, 0);
        exit(1);
    }

    if (pid == 0) // Child process
    {
        printf("\n CLNT: Enter the request message to send to server : \t");
        scanf("%s", m1.m);
        m1.id = msgid;
        rval = msgsnd(qid, &m1, sizeof(m1), 0);
        if (rval == 0)
            printf("\n CLNT:Request message sent to server through Q is %s \n", m1.m);
        else
        {
            perror("CLNT:Q-SND-ERR:");
            exit(1);
        }
        sleep(2);
        rval = msgrcv(qid, &m2, sizeof(m2), msgid, 0);
        char *receive = m2.m;
      
        if (rval == -1)
        {
            perror("CLNT:Q-RD-ERR");
            exit(1);
        }
        else
            printf("\n CLNT: Response message of %lu bytes received from Server is %s\n", strlen(receive), m2.m);
        exit(0);
    }
    else
    {

        sleep(1);
        rval = msgrcv(qid, &m2, sizeof(m2), msgid, 0);
        if (rval == -1)
        {
            perror("SRVR:Q-RD-ERR");
            msgctl(qid, IPC_RMID, 0);
            exit(1);
        }
        else
            printf("\n SRVR: Request message received from client is %s \n", m2.m);

        printf("\n SRVR: Enter the response message to send to Client: \t");
        scanf("%s", m1.m);
        char *c = m1.m;
        m1.id = msgid;
        rval = msgsnd(qid, &m1, sizeof(m1), 0);
        if (rval == 0)
            printf("\n SRVR: Response message of %lu bytes sent to Client is %s through Q \n", (strlen(c)), m1.m);
        else
        {
            perror("SRVR:Q-SND-ERR:");
            exit(1);
        }
        wait(0);
        msgctl(qid, IPC_RMID, 0);
    }
}
