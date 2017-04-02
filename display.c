//
// Created by root on 31/03/17.
//

#include "leminpc.h"
#include <unistd.h>

int     buff_map[MAP_SIZE];

static void         *copy_map(int *map)
{
    int             i;

    i = 0;
    while (i < MAP_SIZE)
    {
        buff_map[i] = map[i];
        i++;
    }
}

static void        display()
{
    int             i;

    i = 0;
    printf("----------------------------------------------------\n");
    while (i < MAP_SIZE)
    {
        if (buff_map[i] == 0)
            printf("_  ");
        else
            printf("%d  ", buff_map[i]);
        if ((i + 1) % COL_SIZE == 0)
            printf("\n");
        i++;
    }
}

int         display_map(int *map)
{
    copy_map(map);
    //thread
    display();
}