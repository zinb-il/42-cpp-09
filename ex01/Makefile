SRCS = main.cpp RPN.cpp

OBJS = $(SRCS:.cpp=.o)

CC = c++

CFLAGS = -Wall -Werror -Wextra -Wshadow -Wno-shadow -std=c++98

#CFLAGS = -Wall -Werror -Wextra -Wshadow -Wno-shadow -std=c++98 -fsanitize=address -g

NAME = RPN

$(NAME) :
		@$(CC) $(CFLAGS) -o $(NAME) $(SRCS)
		@echo "\033[0;32mParfait !!\033[0;0m"


all : $(NAME)

clean :
		@rm -f $(OBJS)
		@echo "\033[0;31mles fichiers .o sont supprimés\033[0;0m"

fclean : clean
		@rm -f $(NAME)
		@echo "\033[0;31mVotre programme est bien supprimé\033[0;0m"

re : fclean all

.PHONY : all clean fclean re