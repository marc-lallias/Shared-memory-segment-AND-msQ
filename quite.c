//
// Created by root on 02/04/17.
//

#include "leminpc.h"
int     send_new_pos(t_pos old, t_pos new, char team, key_t key);

bool            is_other_team_present(int *map, int team)
{
    int         i;

    i = 0;
    while (i < MAP_SIZE)
    {
        if (map[i] != team && map[i] != 0)
            return (true);
        i++;
    }
    return (false);
}

bool            is_last_one(int *map)
{
    int         count;
    int         i;

    i = 0;
    count = 0;
    while (i < MAP_SIZE)
    {
        if (map[i] != 0)
            count++;
        if (count > 1)
        {
            return (false);
        }
        i++;
    }
    return (true);
}

int             leave(t_pos *curr_pos, int *map, int key)
{
    trad_change(curr_pos, map, 0);
    send_new_pos(*curr_pos, *curr_pos, '*', key);//die * en team
    if (is_last_one(map) == true)
    {
        curr_pos->row = -1;
        curr_pos->col = -1;
        send_new_pos(*curr_pos, *curr_pos, -1, key);//die * en team
    }
}