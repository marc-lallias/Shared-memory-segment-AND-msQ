//
// Created by root on 01/04/17.
//

#include "leminpc.h"

void        inc_sem(int sem_id)
{
    struct sembuf   sops;

    sops.sem_num = 0;
    sops.sem_flg = 0;
    sops.sem_op  = 1;
    semop(sem_id, &sops, 1);
}

void        dec_sem(int sem_id)
{
    struct sembuf   sops;

    sops.sem_num = 0;
    sops.sem_flg = 0;
    sops.sem_op  = -1;
    semop(sem_id, &sops, 1);
}