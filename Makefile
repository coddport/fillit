

NAME	= fillit
LIB		= libft/libft.a

SRCS	= main.c\
			reading.c\
			solving.c

OBJS	= $(SRCS:.c=.o)
DEPS	= -I includes/

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror $(DEPS)

all:	$(NAME)

$(LIB):	
		@- make -C libft

$(OBJS):	%.o: %.c
		@$(CC) -c $(CFLAGS) $< -o $@

$(NAME):	$(LIB) $(OBJS)
		$(CC) $(OBJS) $(LIB) -o $(NAME)

clean:
		@rm -rf $(OBJS)
		@make -C libft clean

fclean:	clean
		@rm -rf $(NAME)
		@make -C libft fclean

re:		fclean all

.PHONY:	all clean fclean re
