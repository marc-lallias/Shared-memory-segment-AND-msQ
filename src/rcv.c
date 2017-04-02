/*
** msg.c for msg in /home/peixot_a/Documents/c_tek2/lemipc
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sat Apr  1 14:41:34 2017 pierre.peixoto
** Last update Sun Apr  2 23:04:32 2017 DarKmarK
*/

#include "../include/msg.h"
#include "../leminpc.h"

char		tab[ROW_SIZE][COL_SIZE];

void		static_init_tab(void)
{
  int		j;
  int		i;

  j = 0;
  while(j < ROW_SIZE)
    {
      i = 0;
      while (i < COL_SIZE)
	{
	  tab[j][i] = '-';
	  i++;
	}
      j++;
    }
}

void		print_tab()
{
  int		x;
  int		y;

  printf("\e[1;1H\e[2J");
  y = 0;
  while (y < ROW_SIZE)
    {
      x = 0;
      while (x < COL_SIZE)
	{
	  printf("%c ", tab[y][x]);
	  ++x;
	}
      printf("\n");
      ++y;
    }
}

int		handle_display(key_t *arg)
{
  key_t		key;
  int		msg_id;
  t_msg		msg;

  key = *arg;
  create_msg_queue(key);
  static_init_tab();
  while (1)
    {
      msg = receive_msg(key);
      if (msg.pos.curr_x == -1)
	{
	  del_msg_queue(key);
	  return (0);
	}
      tab[msg.pos.curr_y][msg.pos.curr_x] = '-';
      tab[msg.pos.new_y][msg.pos.new_x] = msg.team;
      print_tab();
    }
  return (0);
}
