NAME	=	Age-Of-Mine
CC	=	g++
SRC	=	*.cpp
LIB	=	-lSDL2main -lSDL2 -lGL -lGLU -lglut -lglfw

all:		$(NAME)

$(NAME):	
		$(CC) -Wall $(SRC) $(LIB) -o $(NAME)

clean:
		rm -rf *.o

fclean:		clean
		rm -rf $(NAME)

re:		fclean all
