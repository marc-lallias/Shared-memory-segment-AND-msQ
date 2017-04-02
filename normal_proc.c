//
// Created by root on 31/03/17.
//

#include "./include/msg.h"
#include "leminpc.h"

static bool     can_start(int sem_id, int *map)
{
    int         count;
    int         i;

    count = 0;
    i = 0;
    while (1)
    {
        dec_sem(sem_id);
        i = 0;
        count = 0;
        while (i < MAP_SIZE)
        {
            if (map[i] != 0)
                count++;
            if (count == 4)
            {
                inc_sem(sem_id);
                return (true);
            }
            i++;
        }
        inc_sem(sem_id);
    }
}

static int     play(t_pos *curr_pos, int team, int *map, int key, t_pos *older)
{
    if (close_mate(curr_pos, map, team) == false)
        go_mate(curr_pos, map, team);// if == -1
    else
        go_enemy(curr_pos, map, team, older);// if == -1*/
    //display_map(map);
    usleep(40000);
}

static int      loop(int *map, const int team, const int sem_id, int key)
{
    t_pos       old_pos;
    t_pos       older;
    t_pos       curr_pos;
    int         trad;
    int         i;

    i = 0;
    found_place(map, &curr_pos, team);//MESS_NEW--------------
    if (curr_pos.row == -1)
        return (-1);
    copy(&old_pos, curr_pos.col, curr_pos.row);
    send_new_pos(old_pos, curr_pos, team + '0', key);//die * en team
    can_start(sem_id, map);
    while (i < 40 && is_die(&curr_pos, team, map) == false &&
            is_other_team_present(map, team) == true)
    {
        dec_sem(sem_id);
        copy(&older, old_pos.col, old_pos.row);
        copy(&old_pos, curr_pos.col, curr_pos.row);
        play(&curr_pos, team, map, key, &older);
        send_new_pos(old_pos, curr_pos, team + '0', key);//die * en team
        //display_map(map);
        copy(&old_pos, curr_pos.col, curr_pos.row);
        inc_sem(sem_id);
        i++;
    }
    leave(&curr_pos, map, key);
}

int             normal_proc(const int key, const int shm_id, const int team)
{
    int         *map;
    int         sem_id;

    printf("Using shm segment %d\n", shm_id);
    sem_id = semget(key, 1, SHM_R | SHM_W);
    map = shmat(shm_id, NULL, SHM_R | SHM_W);
    loop(map, team, sem_id, key);
    //shmctl(shm_id, IPC_RMID, NULL);
}