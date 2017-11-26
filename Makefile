NAME = ft_retro
CC = clang++
INC = Includes
CFLAGS = -Wall -Wextra -Werror
SRCS = Window.class.cpp\
	   AUnit.class.cpp\
	   Ranger.class.cpp\
	   Enemy.class.cpp\
	   Projectile.class.cpp

OBJ = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ) main.cpp
	$(CC) $(CFLAGS) -lncurses -I $(INC) -o $(NAME) main.cpp $(OBJ)

debug : $(SRCS) main.cpp
	$(CC) $(CFLAGS) -g -I $(INC) -lncurses -o $(NAME) main.cpp $(SRCS)

test : $(NAME)
	./$(NAME)

drun: debug
	lldb ./$(NAME)

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

dclean :
	rm -f $(NAME)
	rm -Rf $(NAME).dSYM

re : fclean all

%.o : %.cpp
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
