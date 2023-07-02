/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:15:59 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/28 08:07:34 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	echo_with_option(char **str, int *i)
{
	while (str[++(*i)])
	{
		if (check_option(str[(*i)]) == 1)
			break ;
	}
	while (str[(*i)])
	{
		printf("%s", str[(*i)]);
		if (str[(*i) + 1])
			printf(" ");
		(*i)++;
	}
}

void	echo_cmd(char **str)
{
	int	i;
	int	j;

	i = 1;
	if (!str[1])
	{
		printf("\n");
		return ;
	}
	j = check_option(str[i]);
	if (j == 1)
	{
		while (str[i])
		{
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	else
		echo_with_option(str, &i);
}
