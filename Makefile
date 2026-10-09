NAME	=	libft_malloc_$(HOSTTYPE).so
LINK	=	libft_malloc.so
MAKE	=	make

CC	=	gcc
DEBUG ?= 0

CFLAGS = -Wall -Wextra -Werror -fPIC -DDEBUG=$(DEBUG)

SRC_PATH	=	./src/
OBJ_PATH	=	./obj/
INC_PATH	=	./inc/

SRC		=	malloc.c \
			utils.c \
			show_alloc_mem.c \
			free.c \
			realloc.c \
			calloc.c \
			show_alloc_mem_ex.c

SRCS	=	$(addprefix $(SRC_PATH), $(SRC))

OBJ		=	$(SRC:.c=.o)
OBJS	=	$(addprefix $(OBJ_PATH), $(OBJ))

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: $(OBJ_PATH) $(NAME) $(LINK)
	
$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS)

$(LINK): $(NAME)
	ln -sf $(NAME) $(LINK)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -I$(INC_PATH) -c $< -o $@

test:
	@cd tests && ./run_tests.sh

clean:
	@rm -f $(OBJS)

fclean:	clean
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME) $(LINK)

re:	fclean	all

.PHONY: all clean fclean re
