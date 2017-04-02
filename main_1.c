//
// Created by root on 30/03/17.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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

static int     create_sem(key_t key)
{
    int         sem_id;
    sem_id = semget(key, 1, IPC_CREAT | SHM_R | SHM_W);
    printf("CREATED sem %d\n", sem_id);
    semctl(sem_id, 0, SETVAL, 4);

    return sem_id;
}

int         main(int ac, char **av)
{
    key_t   key;
    int     sem_id;
    t_data  *data_struct;
    t_data  *cast;
    int     shm_id;
    void    *addr;
    char    *str;

    get_proc(&key);
    //
    printf("XXXXXXXXXXXXXXXXX\n");
    //data_struct->data = strdup("message_11");
    //
    shm_id = shmget(key, 50, SHM_R | SHM_W);
    if (shm_id == -1)
    {
        shm_id = shmget(key, 50, IPC_CREAT | SHM_R |SHM_W);
        printf("Created she segment %d\n", shm_id);
        addr = shmat(shm_id, NULL, SHM_R | SHM_W);
        data_struct = addr;
        data_struct->data = 9;
        //str =  addr;
        //str = data_struct;
        //sprintf((char *)addr, "MESSAGE_22");
        //addr = &data_struct;//malloc
    }
    else
    {
        printf("Using shm segment %d\n", shm_id);
        addr = shmat(shm_id, NULL, SHM_R | SHM_W);
        cast = addr;
        printf("------->%d\n", cast->data);
        //printf("-----> %s\n", addr);

        //cast->data = 3;
        shmctl(shm_id, IPC_RMID, NULL);
    }

}
