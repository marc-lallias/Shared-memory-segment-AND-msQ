/*
** normal_proc.c for normal in /home/peixot_a/tek2/c_tek2/PSU_2016_lemipc
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sun Apr  2 19:31:02 2017 pierre.peixoto
** Last update Sun Apr  2 19:41:19 2017 pierre.peixoto
*/

#include "./include/msg.h"
#include "leminpc.h"

static bool	can_start(int sem_id, int *map)
{
  int		count;
  int		i;

  count = 0;
  i = 0;
  while (1)
    {
      dec_sem(sem_id);
      i = 0;
      count = 0;
      while (i < MAP_SIZE)
	{
	  if (map[i] != 0)
	    count++;
	  if (count == 4)
	    {
	      inc_sem(sem_id);
	      return (true);
	    }
	  i++;
	}
      inc_sem(sem_id);
    }
}

static int	play(t_norme *nrm, int team, int *map, int key)
{
  if (close_mate(&(nrm->curr_pos), map, team) == false)
    go_mate(&(nrm->curr_pos), map, team);
  else
    go_enemy(&(nrm->curr_pos), map, team, &(nrm->older));
  usleep(40000);
}

static int	loop(int *map, const int team, const int sem_id, int key)
{
  t_norme	nrm;
  t_pos		old_pos;
  int		trad;
  int		i;

  i = 0;
  found_place(map, &nrm.curr_pos, team);
  if (nrm.curr_pos.row == -1)
    return (-1);
  copy(&old_pos, nrm.curr_pos.col, nrm.curr_pos.row);
  send_new_pos(old_pos, nrm.curr_pos, team + '0', key);
  can_start(sem_id, map);
  while (i < 40 && is_die(&nrm.curr_pos, team, map) == false &&
	 is_other_team_present(map, team) == true)
    {
      dec_sem(sem_id);
      copy(&nrm.older, old_pos.col, old_pos.row);
      copy(&old_pos, nrm.curr_pos.col, nrm.curr_pos.row);
      play(&nrm, team, map, key);
      send_new_pos(old_pos, nrm.curr_pos, team + '0', key);
      copy(&old_pos, nrm.curr_pos.col, nrm.curr_pos.row);
      inc_sem(sem_id);
      i++;
    }
  leave(&nrm.curr_pos, map, key);
}

int		normal_proc(const int key, const int shm_id, const int team)
{
  int		 *map;
  int		 sem_id;

  sem_id = semget(key, 1, SHM_R | SHM_W);
  map = shmat(shm_id, NULL, SHM_R | SHM_W);
  loop(map, team, sem_id, key);
}
