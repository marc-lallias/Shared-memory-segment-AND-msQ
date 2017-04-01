/*
** msg.h for msg in /home/peixot_a/Documents/pierre.peixoto@epitech.eu/perso/tek2/c_tek2/lemipc/test
**
** Made by pierre.peixoto
** Login   <pierre.peixoto@epitech.eu>
**
** Started on  Sat Apr  1 15:39:40 2017 pierre.peixoto
** Last update Sat Apr  1 20:28:05 2017 pierre.peixoto
*/

#ifndef MSG_H_
# define MSG_H_

/*
** Includes
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/msg.h>

/*
** Structures
*/
typedef struct	s_mpos
{
  int		curr_x;
  int		curr_y;
  int		new_x;
  int		new_y;
}		t_mpos;

typedef struct	s_pos
{
  int		col;
  int		row;
}		t_pos;

typedef struct	s_msg
{
  long		mtype;
  t_mpos	pos;
  char		team;
}		t_msg;

/*
** Functions
*/
t_msg	receive_msg(key_t key);
int	send_new_pos(t_pos old, t_pos new, char team, key_t key);
int	create_msg_queue(key_t key);
int	del_msg_queue(key_t key);

#endif /* !MSG_H_ */
