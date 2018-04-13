##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

CC		= 	g++ -g

CPPFLAGS 	+=	-fPIC -I./include/ -W -Wall -Werror -Wextra -std=c++11

LDFLAGS		=	-ldl

NAME		=	arcade

SRCS		=	src/core/Arcade.cpp	\
			src/error/Error.cpp	\
			src/main.cpp

OBJS		=	$(SRCS:.cpp=.o)

all: core games graphicals

core: $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

graphicals:
	mkdir -p ./lib
	make -f Makefiles/MakefileSdl
	make -f Makefiles/MakefileSFML
	#make -f Makefiles/MakefileNcurse

games:
	mkdir -p ./games
	make -f Makefiles/MakefilePacman
	make -f Makefiles/MakefileNibbler

clean:
	$(RM) $(OBJS)
	make -f Makefiles/MakefilePacman clean
	make -f Makefiles/MakefileNibbler clean
	make -f Makefiles/MakefileSdl clean
	make -f Makefiles/MakefileSFML clean
	#make -f Makefiles/MakefileNcurse clean

fclean: clean
	$(RM) $(NAME)
	make -f Makefiles/MakefilePacman fclean
	make -f Makefiles/MakefileNibbler fclean
	make -f Makefiles/MakefileSdl fclean
	make -f Makefiles/MakefileSFML fclean
	#make -f Makefiles/MakefileNcurse fclean

re:	fclean all

.PHONY: all clean fclean re games core graphicals
