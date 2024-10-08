NAME = minishell

CC = cc 

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

LIBS = -L ./readline -lreadline -L libft -lft  -lcurses -I ./readline

SRCS = main.c utils.c syntax_check.c expanding.c \
		lexer.c env.c  lexer_utils.c syntax_utils.c \
		command_table.c command_table_utils.c exec/builtins/pwd.c \
		exec/builtins/utils_builtins.c exec/builtins/echo.c\
		exec/builtins/env.c exec/builtins/exit.c exec/builtins/cd.c\
		exec/utils.c exec/execution.c  exec/execution2.c \
		exec/builtins/unset.c norm.c\
		exec/builtins/export.c herdoc.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\033[1;32mminishell is ready\033[0;0m"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(HOME)/readline-8.2

clean:
	@make -C libft clean
	@rm -f $(OBJS)
	@echo "\033[1;31mminishell objects are deleted\033[0;0m"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "\033[1;31mminishell is deleted\033[0;0m"

re: fclean all

.PHONY: all clean fclean re