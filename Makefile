NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
LIBS = -lreadline
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

SRCS		= main.c error.c finish.c env.c allocation.c check.c  list_creating.c \
				LEXER/lexer.c \
				LEXER/edit_list.c \
				EXPANDER/expander.c\



OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "\033[0;32mMinishell created\033[0;38m...\033[0m"

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[0;38mCompiling \033[0;37m$<\033[0;38m...\033[0m"

clean:
	@rm -f $(OBJS)
	@echo "\033[0;38mCleaning \033[0;37m$(NAME)\033[0;38m...\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;38mDeleting \033[0;37m$(NAME)\033[0;38m...\033[0m"

leaks:
	@make all
	@rm -f leaks.txt
	@echo "\033[0;38mRunning \033[0;37m$(NAME)\033[0;38m with valgrind...\033[0m"
	@valgrind --leak-check=full --show-leak-kinds=all --log-file=leaks.txt ./$(NAME)

re: fclean all

f: fclean

c : clean

l : leaks

r:  f all c
	@valgrind --leak-check=full --show-leak-kinds=all --log-file=leaks.txt ./$(NAME)

PHONY: all clean fclean re leaks f c r l
