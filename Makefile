# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/17 17:55:31 by mchoma            #+#    #+#              #
#    Updated: 2025/05/17 17:55:33 by mchoma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = piping_the_child.c\
		main_bonus.c\
		binary_path.c\
		ft_strjoin.c\
		ft_split.c\
		ft_putstr_fd.c\
		ft_strlen.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_strnstr.c\
		ft_calloc.c\
		ft_substr.c\
		ft_strncmp.c\
		utils.c\
		here_doc.c
		
OBJ = $(FILES:.c=.o)

all : $(OBJ) $(NAME)
	

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: re fclean clean all
