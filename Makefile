NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBS = -lreadline -L libft -lft

SRCS = minishell.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\033[1;32mminishell is ready"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	@rm -f $(OBJS)
	@echo "\033[1;31mminishell objects are deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;31mminishell is deleted"

re: fclean all

.PHONY: all clean fclean re
