/*
** init_tab.c for init_tab in /home/peixot_a/rendu/tek2/c_tek2/PSU_2016_lemipc
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sun Apr  2 20:07:53 2017 pierre.peixoto
** Last update Sun Apr  2 20:21:42 2017 pierre.peixoto
*/

#include "leminpc.h"

void		init_tab(t_square *tab, t_pos *curr, t_pos *other)
{
  tab->pos.row = curr->row + 1;
  tab->pos.col = curr->col;
  tab->dist = ABS(curr->col - other->col) + ABS(curr->row + 1 - other->row);
}

void		init_stab(t_square *tab, t_pos *curr, t_pos *other)
{
  tab->pos.row = curr->row;
  tab->pos.col = curr->col + 1;
  tab->dist = ABS(curr->col + 1 - other->col) + ABS(curr->row - other->row);
}
