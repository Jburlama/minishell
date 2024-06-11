/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:41:35 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/08 13:15:39 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_dollar(char *str)
{
	char	*dollar;
	int		i;

	i = 1;
	while(str[i] != " ")
		i++;
	dollar = ft_calloc(sizeof(char),  (i + 1));
	if (!dollar)
		return (NULL);
	while(i >= 0)
	{
		*dollar++ = *str++;
		i--;
	}
	return (dollar);
}

void	handle_type3(char *str, int type)
{
	char	*dollar;

	if(type == DQUOTES)
	{
		while (*str != '\0')
		{
			if (*str == '$')
				{
					dollar = expand(get_dollar(str));
					write(1, &dollar, ft_strlen(dollar));
					free(dollar); 
					while (*str != ' ')
						str++;
				}
			write(1, &str, 1);
			str++;
		}
	}
	if(type == SQUOTES)
	{	
		write(1, &str, (ft_strlen(str)));
	}
}

void	handle_type2(char *str)
{
	char	**all_args;
	char	*arg_final;
	int		i;

	all_args = ft_split(str, " ");
	while (all_args[i] != NULL)
	{	
		if (all_args[i][0] == '$')
			all_args[i] = expand(all_args[i]);
		arg_final = ft_strjoin(all_args[i], (char *)' ');
		i++;
	}
	write (1, &arg_final, ft_strlen(arg_final));
	free(arg_final);
	//clean(all_args)
}

int	echo(t_token *token)
{
	char	**split_arg;
	int		i;
	bool	n;

	n = false;
	if (token->content[0] == '-' && token->content[1] == 'n')
	{
		i = 2;
		while (token->content[i] == 'n')
			i++;
		if (token->content[i] != ' ')
			n = true;
	}
	while (token->content && token->type != SPECIAL)
	{
		if (token->type == WORD)
			handle_type2(*token->content);
		if (token->type == DQUOTES || token->type == SQUOTES)
			handle_type3(*token->content, token->type);
	}
	if (n == false)
		write(1, '\n', 1);
}


