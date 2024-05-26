GREEN = \e[0;32m
BLUE = \e[1;034m
RED = \e[0;31m
MAGENTA = \033[1;35m
ORANGE = \033[1;38;5;208m
GREY = \033[0;37m
RESET = \e[0m

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LINK = -lreadline
CFILES = main.c
RM = rm -f
OBJS_DIR = ./objs/
SRC_DIR = ./srcs/
OBJS = ${addprefix ${OBJS_DIR}, ${CFILES:.c=.o}}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${LINK} ${OBJS} -o $@
	echo "${GREEN} ${NAME} done ${RESET}"

${OBJS_DIR}:
	mkdir $@

${OBJS}: | ${OBJS_DIR}

${OBJS_DIR}%.o: ${SRC_DIR}%.c
	${CC} ${CFLAGS} -c $^ -o $@
	echo "${GREY} compiling $^ ${RESET}"

clean:
	rm -rf ${OBJS}
	rm -rf ${OBJS_DIR}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}

.SILENT:

.PHONY: clean re fclean
