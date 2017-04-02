/*
** ally_func.c for ally in /home/peixot_a/tek2/c_tek2/PSU_2016_lemipc
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sun Apr  2 19:12:17 2017 pierre.peixoto
** Last update Sun Apr  2 20:05:03 2017 pierre.peixoto
*/

#include "leminpc.h"

int		get_dist(t_pos *other, t_pos *curr)
{
  int		col_dist;
  int		row_dist;

  col_dist = other->col - curr->col;
  row_dist = other->row - curr->row;
  return (ABS(col_dist) + ABS(row_dist));
}

static void	init_nrm(int *closest, t_pos *save, t_pos *other)
{
  *(closest) = MAP_SIZE;
  save->col = -1;
  other->col = 0;
  other->row = 0;
}

void		go_mate(t_pos *curr, int *map, int team)
{
  t_pos		save;
  t_pos		other;
  int		ret;
  int		closest;

  init_nrm(&closest, &save, &other);
  while (other.row < ROW_SIZE)
    {
      other.col = 0;
      while (other.col < COL_SIZE)
	{
	  if (trad_check(&other, map) == team &&
	      (other.row != curr->row || other.col != curr->col))
	    if ((ret = get_dist(&other, curr)) < closest)
	      {
		closest = ret;
		save.col = other.col;
		save.row = other.row;
	      }
	  other.col++;
	}
      other.row++;
    }
  if (save.col != -1)
    move_to(curr, &save, map);
}

bool		close_mate(t_pos *curr, int *map, int team)
{
  t_pos		other;

  other.row = curr->row - ALLY_DIST;
  while (other.row < curr->row + 1 + ALLY_DIST)
    {
      other.col = curr->col - ALLY_DIST;
      while (other.col < curr->col + 1 + ALLY_DIST)
	{
	  if ((other.col != curr->col || other.row != curr->row) &&
	      (other.row >= 0 && other.row < ROW_SIZE) &&
	      (other.col >= 0 && other.col < COL_SIZE))
	    if (trad_check(&other, map) == team)
	      return (true);
	  other.col++;
	}
      other.row++;
    }
  return (false);
}
