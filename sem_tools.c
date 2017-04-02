/*
** sem_tools.c for sem_tools in /home/peixot_a/tek2/c_tek2/PSU_2016_lemipc
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sun Apr  2 19:45:08 2017 pierre.peixoto
** Last update Sun Apr  2 19:45:59 2017 pierre.peixoto
*/

#include "leminpc.h"

void		inc_sem(int sem_id)
{
  struct sembuf	sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op  = 1;
  semop(sem_id, &sops, 1);
}

void		dec_sem(int sem_id)
{
  struct sembuf	sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op  = -1;
  semop(sem_id, &sops, 1);
}
