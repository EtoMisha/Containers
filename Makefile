SRCS = main.cpp

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

INCLUDES = vector.hpp stack.hpp map.hpp iterator.hpp \
			reverse_iterator.hpp iterator_traits.hpp \
			map_iterator.hpp enable_if.hpp is_integral.hpp \
			pair.hpp compare.hpp

NAME = test

$(NAME): main.o
	$(CC) main.o -o $(NAME)

%.o : %.cpp $(INCLUDES)
	$(CC) ${FLAGS} -o $@ -c $<

all : $(NAME)

vector: test_vector.o
	$(CC) test_vector.o -o vector

stack: test_stack.o
	$(CC) test_stack.o -o stack

map: test_map.o
	$(CC) test_map.o -o map

clean :
	rm -rf main.o test_vector.o test_stack.o test_map.o

fclean : clean
	rm -rf $(NAME) vector stack map

re : fclean all

.PHONY: all clean fclean re