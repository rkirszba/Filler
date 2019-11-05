# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 12:50:11 by rkirszba          #+#    #+#              #
#    Updated: 2019/08/07 14:56:32 by rkirszba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visu 

LIB_PATH = ./../libft

SRC_NAME = visu.c\
		   check_header.c\
		   check_input.c\
		   map_manager.c\
		   check_piece.c\
		   check_second_piece.c\
		   print_state.c\
		   print_background.c\
		   print_texts.c\
		   print_texts2.c\
		   check_events.c\
		   free_manager.c\
		   errors.c

HEADER_PATH = ./../includes/

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:.c=.o)

CC = gcc
CCFLAGS = -Wall\
		  -Wextra\
		  -Werror\
		  #-g3\
		  #-fsanitize=address

SDL2_FOLDER = /Users/rkirszba/SDL2/
#SDL2_FOLDER = /Users/romainkirszbaum/SDL2/
SDL2_TTF_LIBS_PATH = $(SDL2_FOLDER)SDL2_ttf-2.0.14/lib/
SDL2_MAIN_INCLUDE_PATH = $(SDL2_FOLDER)SDL2-2.0.8/include/SDL2/
SDL2_TTF_INCLUDE_PATH =	$(SDL2_FOLDER)/SDL2_ttf-2.0.14/include/SDL2/

CPPFLAGS = -I $(HEADER_PATH) -I $(SDL2_MAIN_INCLUDE_PATH) -I $(SDL2_TTF_INCLUDE_PATH) -MMD
LIBFLAGS = -L $(LIB_PATH) -lft -lm

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: lib $(NAME)

lib:
	@make -C ../libft/

$(NAME): $(OBJ)
	@make -C ../libft/
	$(CC) $(CCFLAGS) $(LIBFLAGS) $^ -o $@ `$(SDL2_FOLDER)/SDL2-2.0.8/bin/sdl2-config --cflags --libs` -L$(SDL2_TTF_LIBS_PATH) -lSDL2_ttf

$(OBJ_PATH)/%.o: %.c | $(OBJ_PATH)
	$(CC) $(CCFLAGS) $(CPPFLAGS) `$(SDL2_FOLDER)/SDL2-2.0.8/bin/sdl2-config --cflags` -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

clean:
	@make clean -C ../libft/
	@rm -f $(OBJ) $(OBJ:.o=.d)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@make fclean -C ../libft/
	@rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: lib make clean fclean re san

-include $(OBJ:.o=.d)
