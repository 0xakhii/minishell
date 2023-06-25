/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:15:59 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/25 10:29:06 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_option(char *s)
{
	int i;

	i = 0;
	if (s[0] == '-' && s[1] == 'n')
		i++; //option
	else
		return (1); //no_option
	while (s[i])
	{
		if (s[i] != 'n') //no_option
			return (1);
		i++;
	}
	return (0);
}

void	echo_cmd(char **str)
{
	int i;
	int	j;

	i = 1;
	if (!str[1])
	{
		printf("\n");
		return ;
	}
	j = check_option(str[i]);
	if (j == 1) //no_option
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
	{
		while (str[++i])
		{	
			if (check_option(str[i]) == 1)
				break;
		}
		while (str[i])
		{
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
			i++;
		}
	}
}

