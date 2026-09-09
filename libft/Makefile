#  #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/26 18:26:56 by iarefeva          #+#    #+#              #
#    Updated: 2024/05/29 13:30:50 by iarefeva         ###   ########.fr        #
#                                                                              #
#  #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = 	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_atoi.c\
	ft_toupper.c ft_tolower.c ft_strncmp.c ft_memcmp.c ft_strlen.c ft_strlcpy.c\
	ft_strlcat.c ft_bzero.c ft_striteri.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c\
	ft_putnbr_fd.c ft_memset.c ft_memcpy.c ft_memmove.c ft_calloc.c ft_memchr.c\
	ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c\
	ft_split.c ft_itoa.c ft_strmapi.c

OBJS = $(SRCS:.c=.o)

BONUS_SRCS =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c\
 ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c\
 ft_lstiter.c ft_lstmap.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all :	$(NAME)
	
$(NAME) :
	@$(CC) $(CFLAGS) -c $(SRCS) -I./
	@ar -rcs $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus:	$(BONUS_OBJS)
	@ar -rcs $(NAME) $(BONUS_OBJS)

clean :
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean :	clean
	@rm -f $(NAME)

re :	fclean	all

.PHONY: all clean fclean re bonus
