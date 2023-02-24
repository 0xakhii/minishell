/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:24:55 by ojamal            #+#    #+#             */
/*   Updated: 2023/02/24 09:48:26 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	while (1)
	{
		char cwd[1024];
		int	i = 0;
    	if (getcwd(cwd, sizeof(cwd)) != NULL)
    	{
			i = ft_strlen(cwd);
			cwd[i] = '$';
			cwd[i + 1] = '>';
			readline(cwd);
		}
		else
        	perror("getcwd() error");
	}
    return 0;
}
