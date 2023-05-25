
NAME = minishell

SRCS = main.c \

LIBFT = ft_strchr.c ft_strnstr.c ft_memcpy.c ft_strdup.c ft_strlen.c ft_strtrim.c ft_substr.c \

LLIST = arg_to_list.c arg_list_utils.c cmd_list_utils.c \

SRC = $(addprefix srcs/, $(SRCS))
SRC_LIBFT = $(addprefix srcs/libft/, $(LIBFT))
SRC_LLIST = $(addprefix srcs/linklist/, $(LLIST))

CFLAGS = -Wall -Wextra -Werror -I includes/ -g3 -fsanitize=address
#dont forget to remove -fsanitize=address for evaluation

LDFLAGS = -lreadline

OBJ = ${SRC:.c=.o}
OBJ_LIBFT = ${SRC_LIBFT:.c=.o}
OBJ_LLIST = ${SRC_LLIST:.c=.o}

ALL_OBJ = ${OBJ} ${OBJ_LIBFT} ${OBJ_LLIST}

${NAME}: ${ALL_OBJ}
		@gcc ${CFLAGS} ${ALL_OBJ} ${LDFLAGS} -o ${NAME}

all: ${NAME}

%.o: %.c
		@cc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
		@rm -rf ${OBJ} ${OBJ_LIBFT}

fclean: clean
		@rm -rf ${NAME}

re: fclean all

.PHONY: all re clean fclean
