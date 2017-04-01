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
    int     sem_id;
    t_data  *data_struct;
    t_data  *cast;
    int     shm_id;
    void    *addr;
    char    *str;

    get_proc(&key);
    //
    //data_struct->data = strdup("message_11");
    //
    shm_id = shmget(key, 50, SHM_R | SHM_W);
    if (shm_id == -1)
    {
        go_init(key);
    }
    else
    {
        normal_proc(key, shm_id);
    }

}
