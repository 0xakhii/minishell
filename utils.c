/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:09:16 by ojamal            #+#    #+#             */
/*   Updated: 2023/02/24 10:19:47 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt()
{
	char	cwd[1024];
	char	*input;
	int	i = 0;
	while (1)
	{
    	if (getcwd(cwd, sizeof(cwd)) != NULL)
    	{
			i = ft_strlen(cwd);
			cwd[i] = '$';
			cwd[i + 1] = '>';
			input = readline(cwd);
		}
		else
        	perror("getcwd() error");
		ft_putendl_fd("minishell: Invalid command (still working on it)", 2);
	}
	return (input);
}

int	get_cmd()
{
	char	*cmd;
	cmd = get_prompt();
	return 0;
}