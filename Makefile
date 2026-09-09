NAME	=	libft_malloc_$(HOSTTYPE).so
LINK	=	libft_malloc.so

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRC_PATH	=	./src/
OBJ_PATH	=	./obj/
INC_PATH	=	./inc/
LIBFT_PATH	=	./libft/

SRC		=	malloc.c \
			free.c

SRCS	=	$(addprefix $(SRC_PATH), $(SRC))

OBJ		=	$(SRC:.c=.o)
OBJS	=	$(addprefix $(OBJ_PATH), $(OBJ))

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all:	$(NAME) $(LINK)
	
$(NAME):
	$(CC) -shared -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft

$(LINK): $(NAME)
	ln -sf $(NAME) $(LINK)

%.o:	 %.c
	@$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

libft: $(MAKE) -C $(LIBFT_PATH)

clean:
	@rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean:	clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re:	fclean	all

.PHONY: all clean fclean re
