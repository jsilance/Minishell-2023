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

# ======DEFINE COLORS======

RED = "\e[31m"
CYAN = "\e[36m"
MAGENTA = "\e[35m"
GREEN = "\e[92m"
ENDCOLOR = "\e[0m"

# echo -e "${RED}Red text${ENDCOLOR}"

# ======SOURCES======

SRCS = main.c path_finder.c parsing.c ft_pipe.c str_var.c signal.c\

LIBFT = ft_strchr.c ft_strnstr.c ft_memcpy.c ft_strdup.c ft_strlen.c ft_strtrim.c ft_substr.c \
		ft_split.c ft_strjoin.c ft_strncmp.c ft_tabdup.c ft_len_until_equal.c \

LLIST = arg_to_list.c arg_list_utils.c cmd_list_utils.c arg_to_tab.c \

BASE_PROG = ft_execute.c echo.c ft_unset.c ft_export.c ft_env.c \

# ======ADD PREFIX======

SRC = $(addprefix srcs/, $(SRCS))
SRC_LIBFT = $(addprefix srcs/libft/, $(LIBFT))
SRC_LLIST = $(addprefix srcs/linklist/, $(LLIST))
SRC_BASE_PROG = $(addprefix srcs/programs/, $(BASE_PROG))

# ======COMPILATION FLAGS======

CFLAGS = -Wall -Wextra -Werror -I includes/ -g3 -fsanitize=address
#dont forget to remove -fsanitize=address for evaluation

# ======LDFLAGS======

LDFLAGS = -lreadline

# ======RULES FOR OBJECTS COMPILATION======

OBJ = ${SRC:.c=.o}
OBJ_LIBFT = ${SRC_LIBFT:.c=.o}
OBJ_LLIST = ${SRC_LLIST:.c=.o}
OBJ_BASE_PROG = ${SRC_BASE_PROG:.c=.o}

ALL_OBJ = ${OBJ} ${OBJ_LIBFT} ${OBJ_LLIST} ${OBJ_BASE_PROG}


# ======RULES======

${NAME}: set_green ${ALL_OBJ}
		@echo "\n======COMPILING <<${NAME}>>======\n"
		gcc ${CFLAGS} ${ALL_OBJ} ${LDFLAGS} -o ${NAME}
		@echo ${MAGENTA}
		@echo ${NAME} "\e[0m"HAS BEEN CREATED AND IS READY TO USE
		@echo ${ENDCOLOR}

all: ${NAME}

%.o: %.c
		gcc ${CFLAGS} -c $< -o ${<:.c=.o}

clean: set_red
		@echo "======CLEANING======\n"
		rm -rf ${ALL_OBJ}
		@echo ${ENDCOLOR}

fclean: clean
		@echo -n ${RED}
		@echo "======REMOVING <<${NAME}>>======\n"
		rm -rf ${NAME}
		@echo ${ENDCOLOR}

re: fclean all

set_green:
		@echo ${GREEN}

set_red:
		@echo ${RED}

.PHONY: all re clean fclean
