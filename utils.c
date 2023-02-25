/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:09:16 by ojamal            #+#    #+#             */
/*   Updated: 2023/02/25 03:14:43 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*cmd_parsing(char *input)
// {
// 	t_cmd	*cmd;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	cmd = malloc(sizeof(t_cmd));
// 	cmd->args = ft_split(input, ' ');
// 	while (cmd->args[i])
// 	{
		
// 	}
// }

char	*get_prompt()
{
	char	*cwd;
	char	*input;
	// int	i = 0;

	while (1)
	{
		// signal(SIGQUIT, SIG_IGN);
    	cwd = getcwd(NULL, sizeof(cwd));
		cwd = ft_strjoin(cwd, "$>");
		input = readline(cwd);
		// cmd_parsing(input);
		add_history(input);
	}
	// ft_putendl_fd("minishell: Invalid command (still working on it)", 2);
	return (input);
}


int	get_cmd()
{
	get_prompt();
	return 0;
}