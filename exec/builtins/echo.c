/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:15:59 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/20 11:22:44 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_option(char *s)
{
	// int i;

	// i = 0;
	if (s[0] == '-' && s[1] == 'n')
		return (0); //option
	else
		return (1); //no_option
	// while (s[i])
	// {
	// 	if (s[i] != 'n') //no_option
	// 		return (1);
	// }
	return (0);
}
void	echo_cmd(char **str)
{
	int i;
	int	j;

	i = 1;
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
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
		}
	}
}
