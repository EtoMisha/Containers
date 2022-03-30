SRCS = test.cpp

SRCS_TEST = test.cpp

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

INCLUDES = vector.hpp stack.hpp map.hpp iterator.hpp \
			reverse_iterator.hpp iterator_traits.hpp \
			map_iterator.hpp enable_if.hpp is_integral.hpp \
			pair.hpp compare.hpp

OBJS = $(SRCS:.cpp=.o) 

OBJS_TEST = $(SRCS_TEST:.cpp=.o) 

NAME = main

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o : %.cpp $(INCLUDES)
	$(CC) ${FLAGS} -o $@ -c $<

all : $(NAME)

test: $(OBJS)
	$(CC) $(OBJS) -o test

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re