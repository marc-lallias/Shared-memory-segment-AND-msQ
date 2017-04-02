##
## Makefile for  in /home/darkmark/rendu/leminpc
##
## Made by DarKmarK
## Login   <marc.lallias@epitech.eu>
##
## Started on  Sat Apr  1 22:00:04 2017 DarKmarK
## Last update Sun Apr  2 20:11:03 2017 pierre.peixoto
##

NAME	=	lemipc

SRC	=	main.c			\
		tools.c			\
		father.c		\
		display.c		\
		normal_proc.c		\
		ally_func.c		\
		move.c			\
		sem_tools.c		\
		attack_function.c	\
		./src/msg.c		\
		./src/rcv.c		\
		quite.c			\
		init_tab.c		\

OBJ	=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -lpthread

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
