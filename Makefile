# ======================================================================
# 
#  ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓
# ▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒
# ▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░
# ▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░
# ▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒
# ░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░
# ░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░
# ░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░
#        ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░
#
# ======================================================================

NAME = minishell

# ======SOURCES======

SRCS = main.c path_finder.c parsing.c ft_pipe.c str_var.c signal.c\

LIBFT = ft_strchr.c ft_strnstr.c ft_memcpy.c ft_strdup.c ft_strlen.c ft_strtrim.c ft_substr.c \
		ft_split.c ft_strjoin.c ft_strncmp.c ft_tabdup.c ft_len_until_equal.c \

LLIST = arg_to_list.c arg_list_utils.c cmd_list_utils.c arg_to_tab.c \

BASE_PROG = ft_execute.c echo.c ft_unset.c ft_export.c ft_env.c ft_cd.c \

# ======ADD PREFIX======

SRC = $(addprefix srcs/, $(SRCS))
SRC_LIBFT = $(addprefix srcs/libft/, $(LIBFT))
SRC_LLIST = $(addprefix srcs/linklist/, $(LLIST))
SRC_BASE_PROG = $(addprefix srcs/programs/, $(BASE_PROG))

# ======COMPILATION FLAGS======

CFLAGS = -Wall -Wextra -Werror -I includes/ -g3 -fsanitize=address
#dont forget to remove -fsanitize=address for evaluation

# ======LDFLAGS======

LDFLAGS = -lreadline -L /Users/$(USER)/.brew/Opt/readline/lib -I /Users/$(USER)/.brew/Opt/readline/include

# ======RULES FOR OBJECTS COMPILATION======

OBJ = ${SRC:.c=.o}
OBJ_LIBFT = ${SRC_LIBFT:.c=.o}
OBJ_LLIST = ${SRC_LLIST:.c=.o}
OBJ_BASE_PROG = ${SRC_BASE_PROG:.c=.o}

ALL_OBJ = ${OBJ} ${OBJ_LIBFT} ${OBJ_LLIST} ${OBJ_BASE_PROG}


# ======RULES======

${NAME}: ${ALL_OBJ}
		@echo "\n======COMPILING <<${NAME}>>======\n"
		gcc ${CFLAGS} ${ALL_OBJ} ${LDFLAGS} -o ${NAME}
		@echo "\n======COMPILING <<${NAME}>> COMPLETE======\n"
		@echo ${NAME} HAS BEEN CREATED AND IS READY TO USE

all: ${NAME}

%.o: %.c
		gcc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
		@echo "======CLEANING======\n"
		rm -rf ${ALL_OBJ}
		@echo "\n======CLEANING COMPLETE======\n"

fclean: clean
		@echo "======REMOVING <<${NAME}>>======\n"
		rm -rf ${NAME}
		@echo "\n======REMOVING <<${NAME}>> COMPLETE======\n"

re: fclean all

.PHONY: all re clean fclean
