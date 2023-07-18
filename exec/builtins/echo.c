/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:15:59 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/18 02:29:09 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
void	print_fd(t_cmd *cmd, char *s)
{
	// printf("%d\n", cmd->out_fd);
	if (cmd->out_fd != -2)
		ft_putstr_fd(s, cmd->out_fd);
	else
		ft_putstr_fd(s, 1);

}
int	check_option(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-' && s[1] == 'n')
		i++;
	else
		return (1);
	while (s[i])
	{
		if (s[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo_with_option(t_cmd *cmd, char **str, int *i)
{
	while (str[++(*i)])
	{
		if (check_option(str[(*i)]) == 1)
			break ;
	}
	while (str[(*i)])
	{
		print_fd(cmd, str[(*i)]);
		if (str[(*i) + 1])
			print_fd(cmd, " ");
		(*i)++;
	}
}


void	echo_cmd(t_cmd *cmd ,char **str)
{
	int	i;
	int	j;

	i = 1;
	if (!str[1])
	{
		print_fd(cmd, "\n");
		return ;
	}
	j = check_option(str[i]);
	if (j == 1)
	{
		while (str[i])
		{
			// ft_putstr_fd(str[i], 0);
			print_fd(cmd, str[i]);
			if (str[i + 1])
				print_fd(cmd, " ");
			i++;
		}
		print_fd(cmd, "\n");
	}
	else
		echo_with_option(cmd, str, &i);
}
