/*
** msg.c for msg in /home/peixot_a/Documents/pierre.peixoto@epitech.eu/perso/tek2/c_tek2/lemipc
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sat Apr  1 14:41:34 2017 pierre.peixoto
** Last update Sat Apr  1 20:49:12 2017 pierre.peixoto
*/

#include "../include/msg.h"

int		main(int ac, char **av)
{
  key_t		key;
  int		msg_id;
  t_pos		old;
  t_pos		new;

  if (ac != 5)
    return (-1);
  key = ftok(av[1], 0);
  old.col = atoi(av[2]);
  old.row = atoi(av[3]);
  new.col = old.col + 1;
  new.row = old.row + 1;
  send_new_pos(old, new, av[4][0], key); // T'as juste à appeler ça
  return (0);
}
