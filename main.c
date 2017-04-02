/*
** main.c for main in /home/peixot_a/c_tek2/PSU_2016_lemipc
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sun Apr  2 19:24:19 2017 pierre.peixoto
** Last update Sun Apr  2 19:26:47 2017 pierre.peixoto
*/

#include "leminpc.h"

typedef struct	s_data
{
  int		data;
}		t_data;

static void	get_proc(key_t *key)
{
  char		cwd[1024];

  if (getcwd(cwd, 1024) != NULL)
    fprintf(stdout, "Current working dir: %s\n", cwd);
  *key = ftok(cwd, 0);
}

static bool	check_if_valid_nbr(char *str)
{
  while (*str)
    {
      if (*str < '0' || *str > '9')
	return (false);
      str++;
    }
  return (true);
}

int		main(int ac, char **av)
{
  key_t		key;
  int		shm_id;
  int		team;

  if (ac != 3)
    {
      printf("Usage : ./lemipc path_to_key team_number\n\n");
      printf("path_to_key is a valid path that will be used by ftok\n");
      printf("team_number is the team number assigned ");
      printf("to the current player\n");
      return (1);
    }
  if (check_if_valid_nbr(av[2]) == false)
    return (1);
  key = ftok(av[1], 0);
  team = atoi(av[2]);
  shm_id = shmget(key, 50, SHM_R | SHM_W);
  if (shm_id == -1)
    go_init(key, team);
  else
    normal_proc(key, shm_id, team);
}
