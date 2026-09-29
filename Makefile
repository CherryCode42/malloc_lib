NAME	=	libft_malloc_$(HOSTTYPE).so
LINK	=	libft_malloc.so
MAKE	=	make
LIBFT	=	$(LIBFT_PATH)libft.a

CC	=	gcc
CFLAGS	=	-g -Wall -Wextra -Werror -fPIC

SRC_PATH	=	./src/
OBJ_PATH	=	./obj/
INC_PATH	=	./inc/
LIBFT_PATH	=	./libft/

SRC		=	malloc.c \
			utils.c \
			show_alloc_mem.c \
			free.c

SRCS	=	$(addprefix $(SRC_PATH), $(SRC))

OBJ		=	$(SRC:.c=.o)
OBJS	=	$(addprefix $(OBJ_PATH), $(OBJ))

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: $(OBJ_PATH) $(LIBFT) $(NAME) $(LINK)
	
$(NAME): $(OBJS) $(LIBFT)
	$(CC) -shared -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft

$(LINK): $(NAME)
	ln -sf $(NAME) $(LINK)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -I$(INC_PATH) -I$(LIBFT_PATH) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	@rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean:	clean
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME) $(LINK)
	$(MAKE) -C $(LIBFT_PATH) fclean

re:	fclean	all

.PHONY: all clean fclean re
