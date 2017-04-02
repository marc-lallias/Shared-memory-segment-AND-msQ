//
// Created by root on 31/03/17.
//

#ifndef LEMINPC_LEMINPC_H
#define LEMINPC_LEMINPC_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

/*
 * MAP_DEFINE
 */
#define COL_SIZE    15
#define ROW_SIZE    15
#define MAP_SIZE    COL_SIZE * ROW_SIZE

/*
 * COMBAT_DEFINE
 */
#define ALLY_DIST   2

/*
 * OTHER DEFINE
 */
#define POP_DIST    2

/*
 * MACRO
 */
#define ABS(x) ((x)<0 ? -(x) : (x))

/*
 * STRUCTURE
 */
typedef struct      s_pos
{
    int             col;
    int             row;
}                   t_pos;

int     go_init(const int key, const int team);
int     normal_proc(const int key, const int shm_id, const int team);
int     display_map(int *map);

/*
 * TOOLS
 */
int         trad_pos(const t_pos *pos);
void        trad_change(const t_pos *pos, int *map, int val);
int         trad_check(const t_pos *pos, int *map);
int         int_trad_check(const int row, const int col, int *map);
void        copy(t_pos *buff, int col, int row);

/*
 * ALLY_FUNC
 */
bool        close_mate(t_pos *curr, int *map, int team);
void        go_mate(t_pos *curr, int *map, int team);

/*
 * MOVE
 */
void        found_place(int *map, t_pos *pos, const int team);
void        move_to(t_pos *curr, t_pos *other, int *map);

/*
 * SEM_TOOLS
 */
void        inc_sem(int sem_id);
void        dec_sem(int sem_id);

/*
 * ATTACK
 */
int             on_contact(t_pos *pos, int team, int *map);
int             get_dist(t_pos *other, t_pos *curr);
void            go_enemy(t_pos *curr, int *map, int team, t_pos *old);
bool            is_die(t_pos *curr, int team, int *map);

/*
 * QUITE
 */
bool            is_other_team_present(int *map, int team);
bool            is_last_one(int *map);
int             leave(t_pos *curr_pos, int *map, int key);

#endif //LEMINPC_LEMINPC_H