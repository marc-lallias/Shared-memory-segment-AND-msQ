/*
** tools.c for tools in /home/peixot_a/c_tek2/PSU_2016_lemipc
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sun Apr  2 19:46:25 2017 pierre.peixoto
** Last update Sun Apr  2 19:47:52 2017 pierre.peixoto
*/

#include "leminpc.h"

int	trad_pos(const t_pos *pos)
{
  if (pos->row < 0 || pos->col < 0)
    return (-1);
  if (pos->row >= ROW_SIZE || pos->col >= COL_SIZE)
    return (-1);
  return (pos->row * COL_SIZE + pos->col);
}

void	trad_change(const t_pos *pos, int *map, int val)
{
  int	trad;

  if ((trad = trad_pos(pos)) == -1)
    return ;
  map[trad] = val;
}

int	trad_check(const t_pos *pos, int *map)
{
  int	trad;

  if ((trad = trad_pos(pos)) == -1)
    return (-1);
  return (map[trad]);
}

int	int_trad_check(const int col, const int row, int *map)
{
  if (row < 0 || col < 0)
    return (-1);
  if (row >= ROW_SIZE || col >= COL_SIZE)
    return (-1);
  return (map[row * COL_SIZE + col]);
}

void	copy(t_pos *buff, int col, int row)
{
  buff->col = col;
  buff->row = row;
}
