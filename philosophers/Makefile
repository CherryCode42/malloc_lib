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
		$(CC) $(LDFLAGS) $^ -o $(NAME)

clean:
		$(RM) $(OBJS) 

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	clean fclean re 