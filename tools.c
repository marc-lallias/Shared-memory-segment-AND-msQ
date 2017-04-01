//
// Created by root on 31/03/17.
//

#include "leminpc.h"

int         trad_pos(const t_pos *pos)
{
    if (pos->row < 0 || pos->col < 0)
        return (-1);
    if (pos->row >= ROW_SIZE || pos->col >= COL_SIZE)
        return (-1);
    return (pos->row * COL_SIZE + pos->col);
}

void         trad_change(const t_pos *pos, int *map, int val)
{
    int     trad;

    if ((trad = trad_pos(pos)) == -1)
        return ;
    map[trad] = val;
}

int         trad_check(const t_pos *pos, int *map)
{
    int     trad;
    if ((trad = trad_pos(pos)) == -1)
        return (-1);
    return (map[trad]);
}

int         int_trad_check(const int col, const int row, int *map)
{
    if (row < 0 || col < 0)
        return (-1);
    if (row >= ROW_SIZE || col >= COL_SIZE)
        return (-1);
    return (map[row * COL_SIZE + col]);
}

void        copy(t_pos *buff, int col, int row)
{
    buff->col = col;
    buff->row = row;
}