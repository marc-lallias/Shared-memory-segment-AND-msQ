//
// Created by root on 31/03/17.
//

#include "leminpc.h"
#include "include/msg.h"

static void     init_map(int *add)
{
    int         i;

    i = 0;
    while (i < MAP_SIZE)
    {
        add[i] = 0;
        i++;
    }
}

static int     create_sem(key_t key)
{
    int         sem_id;
    sem_id = semget(key, 1, IPC_CREAT | SHM_R | SHM_W);
    printf("CREATED sem %d\n", sem_id);
    semctl(sem_id, 0, SETVAL, 1);

    return sem_id;
}

static int      create_thread(pthread_t *th, int *key)
{
    if (pthread_create(th, NULL, (void *)handle_display, key) != 0)
    {
        fprintf(stderr, "phread_failed\n");
        return (1);
    }
}

int             go_init(int key, const int team)
{
    int         *map;
    int         shm_id;
    int         sem_id;
    pthread_t	th;


    shm_id = shmget(key, (MAP_SIZE * sizeof(int)),
                    IPC_CREAT | SHM_R |SHM_W);
    printf("Created she segment %d\n", shm_id);
    map = shmat(shm_id, NULL, SHM_R | SHM_W);
    init_map(map);
    sem_id = create_sem(key);
    create_thread(&th, &key);
    normal_proc(key, shm_id, team);
    pthread_join(th, NULL);
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, IPC_RMID, 0);
    //go normal proc
    /*
     * Thread et JOIN THREAD, c est lui qui quitera
     */
}