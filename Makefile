# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 12:47:45 by cpuiu             #+#    #+#              #
#    Updated: 2024/02/09 11:42:18 by cpuiu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I./Libft -I./include

LIBFTDIR = ./Libft
LIBFT = $(LIBFTDIR)/libft.a 
LIBFT_PATH = ./Libft

OBJSDIR = objs
OBJSDIR_BONUS = objs_bonus
SRCSDIR = srcs
SRCSDIRBONUS = srcs_bonus
INCLUDES = include/pipex.h $(LIBFT_PATH)/libft.h include/pipex_bonus.h

PIPEX_BONUS =	$(SRCSDIRBONUS)/fd_bonus.c $(SRCSDIRBONUS)/free_all_bonus.c $(SRCSDIRBONUS)/get_next_line.c \
				$(SRCSDIRBONUS)/here_doc.c $(SRCSDIRBONUS)/process_bonus.c \
				$(SRCSDIRBONUS)/error_management_bonus.c \
				$(SRCSDIRBONUS)/free_all_main_bonus.c $(SRCSDIRBONUS)/process_main_bonus.c \
				$(SRCSDIRBONUS)/split_bonus.c $(SRCSDIRBONUS)/utils_bonus.c

OBJ_BONUS_O =	$(OBJSDIR_BONUS)/fd_bonus.o $(OBJSDIR_BONUS)/free_all_bonus.o $(OBJSDIR_BONUS)/get_next_line.o \
				$(OBJSDIR_BONUS)/here_doc.o $(OBJSDIR_BONUS)/process_bonus.o \
				$(OBJSDIR_BONUS)/error_management_bonus.o $(OBJSDIR_BONUS)/free_all_main_bonus.o \
				$(OBJSDIR_BONUS)/process_main_bonus.o $(OBJSDIR_BONUS)/split_bonus.o $(OBJSDIR_BONUS)/utils_bonus.o

PIPEX_MAIN = $(SRCSDIR)/main.c
PIPEX_BONUS_MAIN = $(SRCSDIRBONUS)/main_bonus.c
OBJ_PIPEX_MAIN = $(OBJSDIR)/main.o
OBJ_PIPEX_MAIN_BONUS = $(OBJSDIR_BONUS)/main_bonus.o
SRC_FILES = $(SRCSDIR)/error_management.c $(SRCSDIR)/free_all.c $(SRCSDIR)/process.c $(SRCSDIR)/split.c $(SRCSDIR)/utils.c
OBJ_FILES = $(OBJSDIR)/error_management.o $(OBJSDIR)/free_all.o $(OBJSDIR)/process.o $(OBJSDIR)/split.o $(OBJSDIR)/utils.o

NAME = pipex

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c $(INCLUDES) | $(OBJSDIR)
		$(CC) $(CFLAGS) -c $< -o $@
		
$(OBJSDIR_BONUS)/%.o: $(SRCSDIRBONUS)/%.c $(INCLUDES) | $(OBJSDIR_BONUS)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_FILES) $(OBJ_PIPEX_MAIN) $(LIBFT)
		$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFTDIR) -lft

$(LIBFT):
	make -C $(LIBFTDIR) && make clean -C $(LIBFTDIR)

all: $(NAME)

clean:
	$(RM) -r $(OBJSDIR) $(OBJSDIR_BONUS)

fclean: clean
		$(RM) $(NAME)
		make fclean -C $(LIBFTDIR)

re: fclean all

bonus: $(OBJ_BONUS_O) $(OBJ_PIPEX_MAIN_BONUS) $(LIBFT) | $(OBJSDIR_BONUS)
	$(CC) $(CFLAGS) $^ -o $(NAME) -L$(LIBFTDIR) -lft
	
$(OBJSDIR_BONUS):
	mkdir -p $(OBJSDIR_BONUS)

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

.PHONY: all clean fclean re bonus
