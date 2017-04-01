//
// Created by root on 01/04/17.
//

#include "leminpc.h"

static void     put_in_buff(int buff[],int val)
{
    ;
}

int             on_contact(t_pos *curr, int team, int *map)
{
    int         buff[50];
    t_pos       other;

    other.row = curr->row - 1;
    while (other.row < curr->row + 1 + 1)
    {
        other.col = curr->col - ALLY_DIST;
        while (other.col < curr->col + 1 + 1)
        {
            if ((other.col != curr->col || other.row != curr->row) &&
                (other.row >= 0 && other.row < ROW_SIZE) &&
                (other.col >= 0 && other.col < COL_SIZE))
                if (trad_check(&other, map) != team)
                    put_in_buff(buff, trad_check(&other, map));
                    //return (true);
            trad_change(&other, map, 9);
            other.col++;
        }
        other.row++;
    }
    return (false);
}

void            go_enemy(t_pos *curr, int *map, int team)
{
    t_pos       save;
    t_pos       other;
    int         ret;
    int         closest;

    closest = MAP_SIZE;
    save.col = -1;
    other.col = 0;
    other.row = 0;
    //if (on_contact(curr) > 0)
    //    return ;
    while (other.row < ROW_SIZE)
    {
        other.col = 0;
        while (other.col < COL_SIZE)
        {
            if (trad_check(&other, map) != team &&
                (other.row != curr->row || other.col != curr->col))
                if ((ret = get_dist(&other, curr)) < closest)
                {
                    closest = ret;
                    save.col = other.col;
                    save.row = other.row;
                }
            other.col++;
        }
        other.row++;
    }
    printf("++++++++++> col %d  ++  row %d\n", save.col, save.row);
    if (save.col != -1)
        move_to(curr, &save, map);
}