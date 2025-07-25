# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 12:02:35 by kmaeda            #+#    #+#              #
#    Updated: 2025/07/25 18:19:36 by kmaeda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -ILibft

LIBFT_DIR = Libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRCS = main.c pipex.c pipex_utils.c
OBJS = $(SRCS:.c=.o)

BONUS_SRCS = main_bonus.c pipex_bonus.c pipex_utils_bonus.c here_doc_bonus.c clean_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_LIB) -o $(NAME)

bonus: $(BONUS_OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_OBJS) $(LIBFT_LIB) -o $(NAME)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all bonus clean fclean re
