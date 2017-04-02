/*
** display.c for display in /home/peixot_a/tek2/c_tek2/PSU_2016_lemipc
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sun Apr  2 19:16:21 2017 pierre.peixoto
** Last update Sun Apr  2 19:17:42 2017 pierre.peixoto
*/

#include <unistd.h>
#include "leminpc.h"

int		buff_map[MAP_SIZE];

static void	*copy_map(int *map)
{
  int		i;

  i = 0;
  while (i < MAP_SIZE)
    {
      buff_map[i] = map[i];
      i++;
    }
}

static void	display()
{
  int		i;

  i = 0;
  printf("----------------------------------------------------\n");
  while (i < MAP_SIZE)
    {
      if (buff_map[i] == 0)
	printf("_  ");
      else
	printf("%d  ", buff_map[i]);
      if ((i + 1) % COL_SIZE == 0)
	printf("\n");
      i++;
    }
}

int		display_map(int *map)
{
  copy_map(map);
  display();
}
