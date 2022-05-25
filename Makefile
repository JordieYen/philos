NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g#-fsanitize=thread

MAIN = philo.c 

SRC =	libftfunc.c \
		libftfunc1.c \
		inits.c \
		errorchecks.c

OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ ${MAIN} ${SRC}

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean

# rm -rf *.dSYM