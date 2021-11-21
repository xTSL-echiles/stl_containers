NAME = go

SRCS = ./stack_test.cpp

OBJS = $(patsubst ./%.cpp,./%.o,$(SRCS))
CC	= clang++

FLAGS = -Wall -Wextra -Werror -std=C++98

$(NAME):	$(OBJS) ../vector/vector.hpp
			$(CC) $(FLAGS) -o $(NAME)  $(OBJS)

all:	$(NAME)

clean: 
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME)

re:		fclean all

.PHONY:	all, clean, fclean, re

.SILENT: