
NAME = minishell

SRCS = main.c ft_strchr.c ft_strnstr.c arg_to_list.c \

SRC = $(addprefix srcs/, $(SRCS))

CFLAGS = -Wall -Wextra -Werror -I includes/ -g3

LDFLAGS = -lreadline

OBJ = ${SRC:.c=.o}

${NAME}: ${OBJ}
		@gcc ${CFLAGS} ${OBJ} ${LDFLAGS} -o ${NAME}

all: ${NAME}

%.o: %.c
		@cc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
		@rm -rf ${OBJ}

fclean: clean
		@rm -rf ${NAME}

re: fclean all

.PHONY: all re clean fclean
