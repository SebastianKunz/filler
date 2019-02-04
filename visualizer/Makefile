# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skunz <skunz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/23 20:21:22 by skunz             #+#    #+#              #
#    Updated: 2019/02/03 11:15:55 by skunz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################################  GENERAL  ###################################

INC = -I ./includes/

SRC_DIR = ./src/

OBJ_DIR = ./.obj/

NAME = visualizer

FLAGS = -Wall -Wextra -Werror -fsanitize=address

INCLUDES_VISU = -I ~/.brew/include/SDL2/ -D_THREAD_SAFE

LIB_VISU = -L ~/.brew/lib -l SDL2 -l SDL2_ttf

SRC = main.cpp window.cpp parser.cpp draw.cpp

#OBJECTS
OBJ = $(addprefix $(OBJ_DIR),$(SRC:.cpp=.o))

###############################  COLORS AND TEXT  ##############################

#COLORS
COM_COLOR   = \033[0;32m
NO_COLOR    = \033[m

#TEXT
COM_STRING  = "$(NAME) Compilation Successful"
CLEAN_OBJ	= "Cleaned $(NAME) Objects"
CLEAN_NAME	= "Cleaned $(NAME)"

####################################  RULES  ###################################

all: obj $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@clang++ $(FLAGS) $(LIB_VISU) $^ -o $@
	@echo "$(COM_COLOR)$(COM_STRING)$(NO_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@clang++ $(FLAGS) $(INCLUDES_VISU) $(INC) -c $< -o $@

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@echo "$(COM_COLOR)$(CLEAN_OBJ)$(NO_COLOR)"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(COM_COLOR)$(CLEAN_NAME)$(NO_COLOR)"

re: fclean all