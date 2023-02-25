/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:09:16 by ojamal            #+#    #+#             */
/*   Updated: 2023/02/25 09:37:26 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquote(char c)
{
	if (c == D_QUOTE || c == S_QUOTE)
		return (1);
	return (0);
}

int	ft_isredir(char c)
{
	if (c == REDIR_IN || c == REDIR_OUT || c == APPEND)
		return (1);
	return (0);
}

int	ft_ispipe(char c)
{
	if (c == PIPE)
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