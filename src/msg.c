/*
** msg.c for msg in /home/peixot_a/Documents/pierre.peixoto@epitech.eu/perso/tek2/c_tek2/lemipc
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sat Apr  1 14:41:34 2017 pierre.peixoto
** Last update Sat Apr  1 20:48:53 2017 pierre.peixoto
*/
#include "../include/msg.h"

t_msg		receive_msg(key_t key)
{
  t_msg		msg;
  int		msg_id;

  msg_id = msgget(key, SHM_R | SHM_W);
  msgrcv(msg_id, &msg, sizeof(t_msg), 42, 0);
  return (msg);
}

int		send_new_pos(t_pos old, t_pos new, char team, key_t key)
{
  int		msg_id;
  t_msg		msg;

  msg_id = msgget(key, SHM_R | SHM_W);
  if (msg_id == -1)
    return (-1);
  msg.mtype = 42;
  msg.pos.curr_x = old.col;
  msg.pos.curr_y = old.row;
  msg.pos.new_x = new.col;
  msg.pos.new_y = new.row;
  msg.team = team;
  msgsnd(msg_id, &msg, sizeof(t_msg), 0);
  return (0);
}

int		create_msg_queue(key_t key)
{
  int		msg_id;

  msg_id = msgget(key, SHM_R | SHM_W);
  if (msg_id != -1)
    return (-1);
  msg_id = msgget(key, IPC_CREAT | SHM_R | SHM_W);
  return (0);
}

int		del_msg_queue(key_t key)
{
  int		msg_id;

  msg_id = msgget(key, SHM_R | SHM_W);
  if (msg_id == -1)
    return (-1);
  msgctl(msg_id, IPC_RMID, NULL);
  return (0);
}
