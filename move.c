//
// Created by root on 01/04/17.
//

#include "leminpc.h"

typedef struct          s_square
{
    t_pos               pos;
    int                 dist;
}                       t_square;

static void go(t_pos *curr, int col, int row, int *map)
{
    int     team;

    team = trad_check(curr, map);
    //printf("-------------> %d\n", team);
    trad_change(curr, map, 0);
    curr->col = col;
    curr->row = row;
    trad_change(curr, map, team);
}

static void     sort_by_dist(t_square tab[])
{
    int         mark;
    int         keep;
    t_pos       keep_pos;
    int         i;

    mark = 1;
    while (mark == 1)
    {
        i = 0;
        mark = 0;
        while (i < 3)
        {
            if (tab[i].dist > tab[i + 1].dist)
            {
                keep = tab[i].dist;
                tab[i].dist = tab[i + 1].dist;
                tab[i + 1].dist = keep;
                copy(&keep_pos, tab[i].pos.col, tab[i].pos.row);
                copy(&tab[i].pos, tab[i + 1].pos.col, tab[i + 1].pos.row);
                copy(&tab[i + 1].pos, keep_pos.col, keep_pos.row);
                mark = 1;
            }
            i++;
        }
    }
}

void            move_to(t_pos *curr, t_pos *other, int *map)
{
    t_square    tab[4];
    int         i;

    i = 0;
    tab[0].pos.row = curr->row + 1;
    tab[0].pos.col = curr->col;
    tab[0].dist = ABS(curr->col - other->col) + ABS(curr->row + 1 - other->row);

    tab[1].pos.row = curr->row;
    tab[1].pos.col = curr->col + 1;
    tab[1].dist = ABS(curr->col + 1 - other->col) + ABS(curr->row - other->row);

    tab[2].pos.row = curr->row - 1;
    tab[2].pos.col = curr->col;
    tab[2].dist = ABS(curr->col - other->col) + ABS(curr->row - 1 - other->row);

    tab[3].pos.row = curr->row;
    tab[3].pos.col = curr->col - 1;
    tab[3].dist = ABS(curr->col - 1 - other->col) + ABS(curr->row - other->row);

    sort_by_dist(tab);
    while (i < 4)
    {
        if (tab[i].pos.col >= 0 && tab[i].pos.row >= 0
            && tab[i].pos.col < COL_SIZE && tab[i].pos.row < ROW_SIZE &&
                trad_check(&(tab[i].pos), map) == 0)
        {
            //printf("place col %d\trow %d\tdist %d\n", tab[i].pos.col, tab[i].pos.row,tab[i].dist);
            go(curr, tab[i].pos.col, tab[i].pos.row, map);
            return ;
        }
        i++;
    }
}

static bool someone(t_pos *curr, int *map)
{
    t_pos       other;

    other.row = curr->row - POP_DIST;
    while (other.row < curr->row + 1 + POP_DIST)
    {
        other.col = curr->col - POP_DIST;
        while (other.col < curr->col + 1 + POP_DIST)
        {
            if ((other.row >= 0 && other.row < ROW_SIZE) &&
                (other.col >= 0 && other.col < COL_SIZE))
                if (trad_check(&other, map) != 0)
                    return (true);
            //trad_change(&other, map, 9);
            other.col++;
        }
        other.row++;
    }
    return (false);
}

void            found_place(int *map, t_pos *pos, const int team)
{
    int         i;

    i = 0;
    while (i < 15)
    {
        pos->col = rand() % COL_SIZE;
        pos->row = rand() % ROW_SIZE;
        if (someone(pos, map) != true)
        {
            trad_change(pos, map, team);
            return;
        }
        i++;
    }
    pos->col = -1;
    pos->row =  -1;
}