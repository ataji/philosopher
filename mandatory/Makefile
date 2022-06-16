# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ataji <ataji@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 06:36:55 by ataji             #+#    #+#              #
#    Updated: 2022/06/16 06:41:30 by ataji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher
INC = philosopher.h
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
COMP_LINUX = -lpthread
SRCS = main.c \
		parse.c \
		philo.c \
		time.c \
		lifetime.c \
		forks.c

OBJS = $(SRCS:%.c=%.o)

all:$(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(COMP_LINUX)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@
	
clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all