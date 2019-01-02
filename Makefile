# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skunz <skunz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/20 14:30:14 by skunz             #+#    #+#              #
#    Updated: 2019/01/01 15:57:48 by skunz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################################### GENERAL ##################################

NAME = skunz.filler

FLAGS = -Wall -Wextra -Werror -fsanitize=address

SRC_DIR = ./src/

SRC = main.c map.c

###################################### OBJECTS #################################

OBJ_DIR = ./obj/

OBJ = $(addprefix $(OBJ_DIR),$(SRC:.c=.o))

################################ LIBRARIES - FRAMEWORK #########################

LIB_DIR = ./libraries

LIBFT = -L $(LIB_DIR)/libft/ -lft

###################################### HEADERS #################################

INC_DIR = ./includes/

LIB_HEAD = $(LIB_DIR)/libft/includes/

INC = -I $(LIB_HEAD) -I $(INC_DIR)

###############################  COLORS AND TEXT  ##############################

#COLORS
COM_COLOR   = \033[0;33m
NO_COLOR    = \033[m

#TEXT
COM_STRING  = "Filler Compilation Successful"
CLEAN_OBJ	= "Cleaned Filler Objects"
CLEAN_NAME	= "Cleaned Filler Binary"

######################################## RULES #################################

all: lib obj $(NAME)

$(NAME): $(OBJ)
	@gcc $(FLAGS) $(LIBFT) $(MINILIB) $(FRAMEWORK) -g $^ -o $@
	@echo "$(COM_COLOR)$(COM_STRING)$(NO_COLOR)"

#OBJECTS

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@gcc $(FLAGS) $(INC) -g -c $< -o $@

obj:
	@mkdir $(OBJ_DIR)

#FILLER

clean: libclean
	@/bin/rm -rf $(OBJ_DIR)
	@echo "$(COM_COLOR)$(CLEAN_OBJ)$(NO_COLOR)"

fclean: clean libfclean
	@/bin/rm -f $(NAME)
	@echo "$(COM_COLOR)$(CLEAN_NAME)$(NO_COLOR)"

#LIBFT

lib:
	@make -C $(LIB_DIR)/libft/ all

libfclean:
	@make -C $(LIB_DIR)/libft/ fclean

libclean:
	@make -C $(LIB_DIR)/libft/ clean

re: fclean all
