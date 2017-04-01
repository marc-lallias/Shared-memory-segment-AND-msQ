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

#define COL_SIZE    15
#define ROW_SIZE    15
#define MAP_SIZE    COL_SIZE * ROW_SIZE

int     go_init(const int key);
int     normal_proc();
int     display_map(int *map);

#endif //LEMINPC_LEMINPC_H