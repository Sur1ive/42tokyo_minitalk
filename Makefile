NAME1	= server
NAME2	= client
SRCDIR1	= ./server_srcs/
SRCDIR2	= ./client_srcs/
SRCS1	= server.c
SRCS2	= client.c
SRCS1	:= $(addprefix $(SRCDIR1), $(SRCS1))
SRCS2	:= $(addprefix $(SRCDIR2), $(SRCS2))
OBJS1	= $(SRCS1:.c=.o)
OBJS2	= $(SRCS2:.c=.o)
LIB		= ./libft/libft.a
CC		= cc -Wall -Wextra -Werror -Iincludes

all: $(NAME1) $(NAME2)

$(NAME1): $(OBJS1)
	make -C libft
	$(CC) $(OBJS1) $(LIB) -o $(NAME1)

$(NAME2): $(OBJS2)
	make -C libft
	$(CC) $(OBJS2) $(LIB) -o $(NAME2)

bonus: all

clean:
	rm -rf $(OBJS1) $(OBJS2)
	make clean -C libft

fclean: clean
	rm -rf $(NAME1) $(NAME2) $(LIB)

re: fclean all

.PHONY: all clean fclean re bonus
