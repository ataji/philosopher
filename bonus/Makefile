# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ataji <ataji@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 06:40:08 by ataji             #+#    #+#              #
#    Updated: 2022/06/16 06:47:38 by ataji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher_b
INC = philosopher_b.h
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
COMP_LINUX = -lpthread

SRCS = main_bonus.c \
	check.c \
	ft_itoa.c \
	ft_strjoin.c \
	utils.c \
	philo_bonus.c \
	lifetime_bonus.c \
	forks_bonus.c

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