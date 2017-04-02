/*
** attack_function.c for attack in /home/rendu/tek2/c_tek2/PSU_2016_lemipc
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sun Apr  2 19:12:42 2017 pierre.peixoto
** Last update Sun Apr  2 19:14:48 2017 pierre.peixoto
*/

#include "leminpc.h"

static bool	is_on_buff(int buff[], int val)
{
  int		i;

  i = 0;
  while (buff[i] != -1)
    {
      if (buff[i] == val) {
	return (true);
      }
      i++;
    }
  return (false);
}

bool		is_die(t_pos *curr, int team, int *map) {
  int		*buff;
  t_pos		other;
  int		i;

  i = 0;
  other.row = curr->row - 1;
  buff = malloc(50 * sizeof(int));
  buff[0] = -1;
  while (other.row < curr->row + 1 + 1) {
    other.col = curr->col - 1;
    while (other.col < curr->col + 1 + 1) {
      if ((other.col != curr->col || other.row != curr->row) &&
	  (other.row >= 0 && other.row < ROW_SIZE) &&
	  (other.col >= 0 && other.col < COL_SIZE))
	{
	  if ((trad_check(&other, map)) != team && (trad_check(&other, map)) != 0)
	    {
	      if ((is_on_buff(buff, trad_check(&other, map))) == true)
		{
		  free(buff);
		  return (true);
		}
	      buff[i] = trad_check(&other, map);
	      i++;
	      buff[i] = -1;
	    }
	}
      other.col++;
    }
    other.row++;
  }
  free(buff);
  return (false);
}

int	on_contact(t_pos *curr, int team, int *map) {
  t_pos other;

  other.row = curr->row - 1;
  while (other.row < curr->row + 1 + 1) {
    other.col = curr->col - 1;
    while (other.col < curr->col + 1 + 1) {
      if ((other.col != curr->col || other.row != curr->row) &&
	  (other.row >= 0 && other.row < ROW_SIZE) &&
	  (other.col >= 0 && other.col < COL_SIZE))
	if (trad_check(&other, map) != team && trad_check(&other, map) != 0)
	  return (true);
      other.col++;
    }
    other.row++;
  }
  return (false);
}

void	go_enemy(t_pos *curr, int *map, int team, t_pos *old)
{
  t_pos	save;
  t_pos	other;
  int	ret;
  int	closest;

  closest = MAP_SIZE;
  save.col = -1;
  copy(&other, 0, 0);
  while (other.row < ROW_SIZE) {
    other.col = 0;
    while (other.col < COL_SIZE) {
      if (trad_check(&other, map) != team &&
	  (other.row != curr->row || other.col != curr->col)
	  && trad_check(&other, map) != 0
	  && (old->col != other.col || old->row != other.row))
	if ((ret = get_dist(&other, curr)) < closest) {
	  closest = ret;
	  copy(&save, other.col, other.row);
	}
      other.col++;
    }
    other.row++;
  }
  if (save.col != -1)
    move_to(curr, &save, map);
}
