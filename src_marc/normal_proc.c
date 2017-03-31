//
// Created by root on 31/03/17.
//

#include "leminpc.h"

int             normal_proc(const int key, const int shm_id)
{
    int         *map;

    printf("Using shm segment %d\n", shm_id);
    map = shmat(shm_id, NULL, SHM_R | SHM_W);
    //shmctl(shm_id, IPC_RMID, NULL);
}