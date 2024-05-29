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
CFILES = main.c get_line.c signals.c \
		 tokenize.c tokens_list_words.c token_list_arg.c
RM = rm -f
OBJS_DIR = ./objs/
SRC_DIR = ./srcs/
OBJS = ${addprefix ${OBJS_DIR}, ${CFILES:.c=.o}}
LIBFT = libft/libft.a

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${LINK} ${OBJS} ${LIBFT} -o $@
	echo "${GREEN} >> ${NAME} done ${RESET}"

${OBJS_DIR}:
	mkdir $@

${OBJS}: | ${OBJS_DIR}

${OBJS_DIR}%.o: ${SRC_DIR}%.c
	${CC} ${CFLAGS} -c $^ -o $@
	echo "${GREY} >> compiling $^ ${RESET}"

${LIBFT}: libft
	@make -C libft

clean:
	rm -rf ${OBJS}
	rm -rf ${OBJS_DIR}
	echo "${ORANGE} >> cleaning ${RESET}"
	make clean -C libft

fclean: clean
	rm -rf ${NAME}
	echo "${ORANGE} >> fcleaning ${RESET}"
	@make fclean -C libft

re: fclean ${NAME}

.SILENT:

.PHONY: clean re fclean
