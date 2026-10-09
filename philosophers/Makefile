NAME	= philo

SRCS	= philo.c philo_utils.c life_parse.c life_init.c routine_life_start.c \
			routine.c time.c set_and_get.c synchronise.c check_philos.c clean_life.c \

OBJS	:= $(SRCS:%.c=%.o)

CC		= cc
RM		= rm -f

CFLAGS	= -g -Wall -Wextra -Werror
LDFLAGS = -L.. -lft_malloc -pthread

%.o:	%.c
			$(CC) $(CFLAGS) -c $^ -o $@

all:	$(OBJS)
		$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
		$(RM) $(OBJS) 

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

load:
	LD_LIBRARY_PATH=.. ./philo 2 800 200 200 3

.PHONY:	clean fclean re 