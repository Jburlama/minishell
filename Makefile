GREEN = \e[0;32m
BLUE = \e[1;034m
RED = \e[0;31m
MAGENTA = \033[1;35m
ORANGE = \033[1;38;5;208m
GREY = \033[0;37m
RESET = \e[0m

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LINK = -lreadline
CFILES = main.c get_line.c signals.c panic.c tokenize.c  \
		 tokens_list_words.c token_list_quotes.c token_list_quotes2.c \
		 tokens_list_special.c tree.c parse_tree.c construct.c utils.c \
		 check.c prepare_token.c clear.c execute.c runexec.c prepare_dollar.c \
		 logical.c find_root.c cmd_echo.c cmd_export.c cmd_unset.c\
		 cmd_env.c cmd_pwd.c cmd_cd.c cmd_exit.c cmd_utils.c start_data.c \
		 prepare_wildcards.c prepare_wildcards_aux.c here_doc.c pipe_execute.c \
		 construct_redir.c prepare_dollar_aux.c prepare_token_aux.c check_utils.c \
		 cmd_cd_aux.c
RM = rm -f
OBJS_DIR = ./objs/
SRC_DIR = ./srcs/
OBJS = ${addprefix ${OBJS_DIR}, ${CFILES:.c=.o}}
LIBFT = libft/libft.a
VPATH = ${SRC_DIR}:${SRC_DIR}tree:${SRC_DIR}tokens:${SRC_DIR}cmds

COMPILE_COUNT = 0
NUM_SRCS	= $(words $(CFILES))

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	@${CC} ${CFLAGS} ${LINK} ${OBJS} ${LIBFT} -o $@
	@printf "\r[\033[32m100%%\033[0m] \001\033[1;97m\002- 42-Minishell compiled successfully! \n \001\033[0m\002"
	@printf "\n\e[1;97;3m	Welcome to 42-Minishell! \n\e[0m"
	@printf "\n\e[1;97;3m        A project developed by\n        ${BLUE}Vbritto- && Jburlama .\n\e[0m"
	@printf "\nRun \001\033[1;97m\002./minishell\001\033[0m\002 to start the program.\n"

${OBJS_DIR}:
	mkdir $@

${OBJS}: | ${OBJS_DIR}

${OBJS_DIR}%.o: %.c
	@${CC} ${CFLAGS} -c $^ -o $@
	@$(eval COMPILE_COUNT=$(shell echo $$(($(COMPILE_COUNT)+1))))
	@printf "\r[\033[32m%3d%%\033[0m] Compiling: $<" $$(($(COMPILE_COUNT) * 100 / $(NUM_SRCS)))

${LIBFT}: libft
	@make -s -C libft

valgrind: ${NAME}
	@valgrind --suppressions=.ignore_readline ./minishell

clean:
	rm -rf ${OBJS}
	rm -rf ${OBJS_DIR}
	echo "${ORANGE} >> cleaning ${RESET}"
	make clean -s -C libft

fclean: clean
	rm -rf ${NAME}
	echo "${ORANGE} >> fcleaning ${RESET}"
	@make fclean -s -C libft

re: fclean ${NAME}

.SILENT:

.PHONY: clean re fclean
