/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:41:35 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/27 14:23:43 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
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
		arg_final = ft_strjoin(all_args[i], (char *)' ');
		i++;
	}
	write (1, &arg_final, ft_strlen(arg_final));
	free(arg_final);
	//clean(all_args)
}*/

void	cmd_echo(t_data *data, t_exec *node)
{
	int		i;
	bool	n;

	i = 0;
	n = false;
	if (node->args[0][0] == '-' && node->args[0][1] == 'n')
	{
		i = 2;
		while (node->args[0][i] == 'n')
			i++;
		if (node->args[0][i] != ' ')
			n = true;
	}
	i = 1;
	while (node->args[i])
	{
		ft_printf("%s", node->args[i]);
		if (node->args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (n == false)
		write(1, "\n", 1);
	clear_tree(data->root);
	exit(status_exit);
}
