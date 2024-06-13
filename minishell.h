/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:25:22 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/13 15:29:40 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED 		"\x1b[31m"
# define YELLOW 	"\x1b[33m"
# define GREEN 		"\x1b[32m"
# define BLUE 		"\x1b[34m"
# define LIGHT_GRAY "\x1b[37m"
# define DARK_GRAY  "\x1b[90m"
# define MAGENTA	"\033[1;35m"
# define RESET 		"\x1b[0m"

# include "libft/libft.h"
# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

extern int	status_exit;

enum e_type
{
	WHITE_SPACE,
	WORD,
	SPECIAL,
	DQUOTES,
	SQUOTES,
	IO,
	I,
	O,
	APEND,
	HERE_DOC,
	EXEC,
	REDIR,
	PIPE,
};

typedef struct s_token
{
	enum e_type		type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_pipe
{
	enum e_type		type;
	void			*left;
	void			*right;
}	t_pipe;

typedef struct s_redir
{
	enum e_type		type;
	enum e_type		file_type;
	char			*file;
	void			*down;
}	t_redir;

typedef struct s_exec
{
	enum e_type		type;
	char			*args;
}	t_exec;

typedef struct s_data
{
	t_token	*head;
	t_token	*tail;
	void	*root;
	char	**env;
}	t_data;

void	clear_tree(void	*root);

// create_tree.c
void	create_tree(t_data *data);
void	*parse_pipe(t_token **tokens);
void	*construct_pipe(void *l, void *r);

// construct.c
void	*construct_redir(void	*subnode, t_token **tokens);
t_exec	*t_exec_fill(t_exec **exec, t_token *token);

// parse_tree.c
void	*parse_exec(t_token **tokens);
void	*parse_redir(void *root, t_token **tokens);

// token_list_quotes.c
void	add_token_quotes(t_data *data, int *i, enum e_type type);
void	create_token_quotes(t_data *data, int *i, enum e_type type, char q);
int		create_token_quotes2(t_data *data, int *i, char q, int len);
void	append_token_quotes(t_data *data, int *i, enum e_type type, char q);

// token_list_quotes2.c
void	new_promp_for_quotes(t_data *data, char q, int len);
void	tokenize_continue(t_data *data, char q, int *i);
void	promp_quotes(char q);

// tokens_list_specil.c
void	add_token_special(t_data *data, int *i, enum e_type type);
void	create_token_special(t_data *data, int *i, enum e_type type);
void	create_token_special2(t_data *data, enum e_type type);
void	append_token_special(t_data *data, int *i, enum e_type type);

// tokens_list_words.c
void	add_token_word(t_data *data, int *i, enum e_type type);
void	append_token_word(t_data *data, int *i, enum e_type type);
void	create_token_word(t_data *data, int *i, enum e_type type);
void	add_token_white_space(t_data *data, int *i, enum e_type type);

// tokenize.c
void	tokenize(t_data *data);
void	add_token(t_data *data, int *i, enum e_type type);
void	add_token_io(t_data *data, int *i);

// utils.c
void	jump_white_spaces(int *i);
void	clear_list(t_token	**head);
bool	is_special(char c);
bool	is_quote(char c);

// signals.c
void	handle_signal(void);
void	signal_handler(int sig);

// get_line.c
void	get_line(void);
bool	is_white_space(char c);

// panic.c
void	panic(char *msg, t_data *data);

// check.c

int		check(char *str);
void	check_redirect(char *str);
void	check_quotes(char *str);
void	ft_exit(char *str);
void	check_heredoc(char *str);

// prepare_token.c

void	prepare_token(t_data *data);
char	*expand(char *env_name, t_data *data);

#endif
