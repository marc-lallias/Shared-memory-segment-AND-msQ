//
// Created by root on 30/03/17.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <strings.h>

typedef struct      s_msg
{
    long            mtype;
    char            str[32];
}                   t_msg;

typedef struct      s_data
{
    int            data;
}                   t_data;

static  void   get_proc(key_t *key)
{
    char            cwd[1024];

    if (getcwd(cwd, 1024) != NULL)
        fprintf(stdout, "Current working dir: %s\n", cwd);
    *key = ftok(cwd, 0);
}

int         main(int ac, char **av) {
    key_t   key;
    int     msg_id;
    t_msg   msg;

    get_proc(&key);
    //
    msg_id = msgget(key, SHM_R | SHM_W);
    if (msg_id == -1)
    {
        msg_id = msgget(key, IPC_CREAT | SHM_R | SHM_W);
        msgrcv(msg_id, &msg, sizeof(t_msg), 42, 0);
        printf("Received message type %d : %s\n", msg.mtype, msg.str);
    }
    else
    {
        printf("Using msgq %d\n", msg_id);
        bzero(&msg, sizeof(t_msg));
        msg.mtype = 42;
        sprintf(msg.str, "mess");
        msgsnd(msg_id, &msg, sizeof(t_msg), 0);//envoie a l'existant
        msgctl(msg_id, IPC_RMID, NULL);
    }
    return 0;
}