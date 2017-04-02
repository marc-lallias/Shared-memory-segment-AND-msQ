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

static bool check_if_valid_nbr(char *str)
{
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return (false);
        str++;
    }
    return (true);
}

int         main(int ac, char **av)
{
    key_t   key;
    int     shm_id;
    int     team;

    if (ac != 3)
      {
	printf("Usage : ./lemipc path_to_key team_number\n\n");
	printf("path_to_key is a valid path that will be used by ftok\n");
	printf("team_number is the team number assigned to the current player\n");
	return (1);
      }
    if (check_if_valid_nbr(av[2]) == false)
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
