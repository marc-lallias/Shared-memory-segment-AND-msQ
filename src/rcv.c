/*
** msg.c for msg in /home/peixot_a/Documents/pierre.peixoto@epitech.eu/perso/tek2/c_tek2/lemipc
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sat Apr  1 14:41:34 2017 pierre.peixoto
** Last update Sat Apr  1 21:08:26 2017 DarKmarK
*/

#include "../include/msg.h"

char		tab[15][15] = {
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
  { '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}
};

void		print_tab()
{
  int		x;
  int		y;

  printf("\e[1;1H\e[2J");
  y = 0;
  while (y < 15)
    {
      x = 0;
      while (x < 15)
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
    key_t key;
  int		msg_id;
  t_msg		msg;

    printf("XXXX\n");
    key = *arg;
    printf("YYYY  %d\n", key);
  create_msg_queue(key);
  while (1)
    {
      msg = receive_msg(key);
      if (msg.pos.curr_x == -1)
	{
	  del_msg_queue(key);
	  return (0);
	}
      tab[msg.pos.curr_y][msg.pos.curr_x] = '*';
      tab[msg.pos.new_y][msg.pos.new_x] = msg.team;
      print_tab();
    }
  return (0);
}

/*int		main(int ac, char **av)
{
  key_t		key;

  if (ac != 2)
    return (-1);
  key = ftok(av[1], 0);
  if (handle_display(key) == -1)
    return (-1);
  return (0);
}*/
