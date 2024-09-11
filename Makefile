# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amandour <amandour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/23 19:12:38 by achahlao          #+#    #+#              #
#    Updated: 2024/09/11 14:21:00 by amandour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror  #-g -fsanitize=address
LDFLAGS = -lreadline #-g 
SRC = $(shell find . -type f -name "*.c")
OBJS_DIR = build/
OBJ     = $(patsubst %.c,$(OBJS_DIR)%.o,$(SRC))
EXEC = minishell
 
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

$(OBJS_DIR)%.o: %.c minishell.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(EXEC)
re: fclean all

.PHONY: all clean fclean re