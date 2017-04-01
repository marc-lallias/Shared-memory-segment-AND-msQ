//
// Created by root on 31/03/17.
//

#include "./include/msg.h"
#include "leminpc.h"

static int      loop(int *map, const int team, const int sem_id, int key)
{
    t_pos       old_pos;
    t_pos       curr_pos;
    int         trad;
    int         i;

    i = 0;
    found_place(map, &curr_pos, team);//MESS_NEW--------------
    if (curr_pos.row == -1)
        return (-1);
    copy(&old_pos, curr_pos.col, curr_pos.row);
    send_new_pos(old_pos, curr_pos, team + '0', key);//die * en team
    //curr_pos.col = 10;
    //curr_pos.row = 10;//search_pos
    //trad_change(&curr_pos, map, team);
    //display_map(map);//TO_RM
    printf("key ----> %d\n", key);
    while (i < 4)
    {
        dec_sem(sem_id);
        copy(&old_pos, curr_pos.col, curr_pos.row);
        // semaph++
        //check_if_dire(curr_pos);
        if (close_mate(&curr_pos, map, team) == false)
            go_mate(&curr_pos, map, team);// if == -1
        else
            on_contact(&curr_pos, team, map);
          //  go_on_ennemy(curr_pos, team);// if == -1 leav()
        send_new_pos(old_pos, curr_pos, team + '0', key);//die * en team
        //display_map(map);
        sleep(1);
        inc_sem(sem_id);
        i++;
    }
    /*
     * fin old.col = -1
     */
    send_new_pos(old_pos, curr_pos, '*', key);//die * en team
    sleep(2);
    old_pos.col = -1;
    send_new_pos(old_pos, curr_pos, team + '0', key);//die * en team
    //
    //destroy semaphore
}

int             normal_proc(const int key, const int shm_id, const int team)
{
    int         *map;
    int         sem_id;

    printf("Using shm segment %d\n", shm_id);
    sem_id = semget(key, 1, SHM_R | SHM_W);
    map = shmat(shm_id, NULL, SHM_R | SHM_W);
    loop(map, team, sem_id, key);
    shmctl(shm_id, IPC_RMID, NULL);
}