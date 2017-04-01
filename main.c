//
// Created by root on 31/03/17.
//

//
// Created by root on 30/03/17.
//

#include "leminpc.h"

typedef struct      s_data
{
    int            data;
}                   t_data;

static  void   get_proc(key_t *key)
{
    char            cwd[1024];

    if (getcwd(cwd, 1024) != NULL)
        fprintf(stdout, "Current working dir: %s\n", cwd);
    *key = ftok(cwd, 0);
}

int         main(int ac, char **av)
{
    key_t   key;
    int     shm_id;
    int     team;

    if (ac != 3)
        return (1);
    key = ftok(av[1], 0);
    team = atoi(av[2]);// CHECK IF ONLY NBR
    shm_id = shmget(key, 50, SHM_R | SHM_W);
    if (shm_id == -1)
    {
        go_init(key, team);
    }
    else
    {
        normal_proc(key, shm_id, team);
    }

}
