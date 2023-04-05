/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:09:16 by ojamal            #+#    #+#             */
/*   Updated: 2023/04/05 07:29:14 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquote(char c)
{
	if (ft_strcmp(&c, S_QUOTE) == 0
		|| ft_strcmp(&c, D_QUOTE) == 0)
		return (1);
	return (0);
}

int	ft_isredir(char c)
{
	if (ft_strcmp(&c, REDIR_IN) == 0
		|| ft_strcmp(&c, REDIR_OUT) == 0)
		return (1);
	return (0);
}

int	ft_ispipe(char c)
{
	if (ft_strcmp(&c, PIPE) == 0)
		return (1);
	return (0);
}

int	ft_isand(char c)
{
	if (ft_strcmp(&c, AND) == 0)
		return (1);
	return (0);
}

int	check_all(char *input)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (ft_isquote(input[i]))
			quote++;
		i++;
	}
	if (quote % 2 != 0)
	{
		printf("Error: Unmatched quotes\n");
		return (0);
	}
	return (1);
}