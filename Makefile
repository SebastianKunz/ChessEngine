##################################### GENERAL ##################################

CC = g++

NAME = Chess

FLAGS = -Wall -Wextra -fsanitize=address -g

SRC_DIR = ./src/

SRC = main.cpp GameBoard.cpp FigureLoader.cpp AFigure.cpp \
	Pawn.cpp Rook.cpp Bishop.cpp King.cpp

###################################### OBJECTS #################################

OBJ_DIR = ./.obj/

OBJ = $(addprefix $(OBJ_DIR),$(SRC:.cpp=.o))

################################ LIBRARIES - FRAMEWORK #########################

SDL_PATH = ~/homebrew/Cellar/sdl2/2.0.9_1/lib

SDL_LIB = -L $(SDL_PATH)/ -l SDL2

LIB_DIR = ./libraries

###################################### HEADERS #################################

INC_DIR = ./includes/

INC = -I $(INC_DIR)

###############################  COLORS AND TEXT  ##############################

#COLORS
COM_COLOR   = \033[0;33m
NO_COLOR    = \033[m

#TEXT
COM_STRING  = "$(NAME) Compilation Successful"
CLEAN_OBJ	= "Cleaned $(NAME) Objects"
CLEAN_NAME	= "Cleaned $(NAME) Binary"

######################################## RULES #################################

all: obj $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $^ -lSDL2 -lSDL2main -lSDL2_image -o $@
	@echo "$(COM_COLOR)$(COM_STRING)$(NO_COLOR)"

#OBJECTS

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@$(CC) $(FLAGS) $(INC) -g -c $< -o $@

obj:
	@mkdir -p $(OBJ_DIR)

lib:
	@make -C $(VECTOR_PATH) all

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@echo "$(COM_COLOR)$(CLEAN_OBJ)$(NO_COLOR)"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(COM_COLOR)$(CLEAN_NAME)$(NO_COLOR)"

re: fclean all