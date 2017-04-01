//
// Created by root on 01/04/17.
//


#include "leminpc.h"

int      get_dist(t_pos *other, t_pos *curr)
{
    int         col_dist;
    int         row_dist;

    col_dist = other->col - curr->col;
    row_dist = other->row - curr->row;
    return (ABS(col_dist) + ABS(row_dist));
}

void            go_mate(t_pos *curr, int *map, int team)
{
    t_pos       save;
    t_pos       other;
    int         ret;
    int         closest;

    closest = MAP_SIZE;
    save.col = -1;
    other.col = 0;
    other.row = 0;
    while (other.row < ROW_SIZE)
    {
        other.col = 0;
        while (other.col < COL_SIZE)
        {
            if (trad_check(&other, map) == team &&
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
    if (save.col != -1)
        move_to(curr, &save, map);
}

bool            close_mate(t_pos *curr, int *map, int team)
{
    t_pos       other;

    other.row = curr->row - ALLY_DIST;
    while (other.row < curr->row + 1 + ALLY_DIST)
    {
        other.col = curr->col - ALLY_DIST;
        while (other.col < curr->col + 1 + ALLY_DIST)
        {
            if ((other.col != curr->col || other.row != curr->row) &&
                (other.row >= 0 && other.row < ROW_SIZE) &&
                (other.col >= 0 && other.col < COL_SIZE))
                if (trad_check(&other, map) == team)
                    return (true);
            //trad_change(&other, map, 9);
            other.col++;
        }
        other.row++;
    }
    return (false);
}