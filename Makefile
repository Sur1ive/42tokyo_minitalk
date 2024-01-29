NAME1	= server
NAME2	= client
SRCS1	= srcs/server.c srcs/utilities.c
SRCS2	= srcs/client.c srcs/utilities.c
OBJS1	= $(SRCS1:.c=.o)
OBJS2	= $(SRCS2:.c=.o)

NAME1B	= server_bonus
NAME2B	= client_bonus
SRCS1B	= srcs/server_bonus.c srcs/utilities_bonus.c
SRCS2B	= srcs/client_bonus.c srcs/utilities_bonus.c
OBJS1B	= $(SRCS1:.c=.o)
OBJS2B	= $(SRCS2:.c=.o)

LIB		= ./libft/libft.a
CC		= cc -Wall -Wextra -Werror -Iincludes

all: $(NAME1) $(NAME2)

$(NAME1): $(OBJS1)
	make -C libft
	$(CC) $(OBJS1) $(LIB) -o $(NAME1)

$(NAME2): $(OBJS2)
	make -C libft
	$(CC) $(OBJS2) $(LIB) -o $(NAME2)

bonus: $(NAME1B) $(NAME2B)

$(NAME1B): $(OBJS1B)
	make -C libft
	$(CC) $(OBJS1B) $(LIB) -o $(NAME1B)

$(NAME2B): $(OBJS2B)
	make -C libft
	$(CC) $(OBJS2B) $(LIB) -o $(NAME2B)

clean:
	rm -rf $(OBJS1) $(OBJS2) $(OBJS1B) $(OBJS2B)
	make clean -C libft

fclean: clean
	rm -rf $(NAME1) $(NAME2) $(NAME1B) $(NAME2B) $(LIB)

re: fclean all

.PHONY: all clean fclean re bonus
