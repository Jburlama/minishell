/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:41:35 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/05 17:11:06 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_dollar(char *str)
{
	char	*dollar;
	int		i;

	i = 0;
	while(str[i] != " ")
		i++;
	dollar = malloc((char*)  i + 1);
	if (!dollar)
		return (NULL);
	while(i >= 0)
	{
		*dollar++ = *str++;
		i--;
	}
	*dollar++ = '\0';
	return (dollar);
}

void	handle_type3(char *str)
{
	char	*dollar;
	int		i;

	i = 0;
	if(*str == 34)
	{
		str++;
		while (*str != '\0' && *str != 34)
		{
			if (*str == "$")
				{
					dollar = expand(get_dollar(str));
					write(1, &dollar, ft_strlen(dollar));
					free(dollar); 
					while (*str != " ")
						str++;
				}
			write(1, &str, 1);
		}
	}
	if(*str == 39)
	{	
		str++;
		write(1, &str, (ft_strlen(str) - 1));
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
		if (all_args[i][0] == "$")
			all_args[i] = expand(all_args[i]);
		arg_final = ft_strjoin(all_args[i], (char *)" ");
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
	i = 0;
	if (token->content[0] == "-" && token->content[1] == "n")
	{
		while (token->content[i] == "n")
			i++;
		if (token->content[i] != " ")
			n = true;
	}
	while (token->content && token->type != SPECIAL)
	{
		if (token->type == 2)
			handle_type2(*token->content);
		if (token->type == 3)
			handle_type3(*token->content);
	}
	if (n == false)
		write(1, '\n', 1);
}


