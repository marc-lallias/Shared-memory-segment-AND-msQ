//
// Created by root on 31/03/17.
//

#include "leminpc.h"

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

int             go_init(const int key)
{
    int         *map;
    int         shm_id;

    shm_id = shmget(key, MAP_SIZE * sizeof(int), IPC_CREAT | SHM_R |SHM_W);
    printf("Created she segment %d\n", shm_id);
    map = shmat(shm_id, NULL, SHM_R | SHM_W);
    init_map(map);
    display_map(map);
    shmctl(shm_id, IPC_RMID, NULL);
}