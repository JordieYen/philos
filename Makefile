NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3

MAIN = main.c 

SRC =	libftfunc.c \
		libftfunc1.c \
		inits.c \
		errorchecks.c \
		philo_utils.c

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