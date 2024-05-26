/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:35:46 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/26 18:54:13 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEll_H
# define MINISHEll_H

# define RED 		"\x1b[31m"
# define YELLOW 	"\x1b[33m"
# define GREEN 		"\x1b[32m"
# define BLUE 		"\x1b[34m"
# define LIGHT_GRAY "\x1b[37m"
# define DARK_GRAY  "\x1b[90m"
# define MAGENTA	"\033[1;35m"
# define RESET 		"\x1b[0m"

# include "libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>

// get_line.c
void	get_line();
bool is_white_space(char c);

#endif
