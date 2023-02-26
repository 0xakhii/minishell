/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 09:28:52 by ojamal            #+#    #+#             */
/*   Updated: 2023/02/26 14:04:12 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	lexic(char *input)
// {
// 	int		i;
// 	int		j;
// 	int		quote;
// 	char	*cmd;

// 	i = 0;
// 	j = 0;
// 	quote = 0;
// 	while (input[i])
// 	{
// 		if (ft_isquote(input[i]))
// 			quote++;
// 		if (quote % 2 == 0 && (ft_isredir(input[i]) || ft_ispipe(input[i])))
// 		{
// 			cmd = ft_substr(input, j, i - j);
// 			printf("cmd: %s\n", cmd);
// 			j = i + 1;
// 		}
// 		i++;
// 	}
// }

char	*get_prompt()
{
	char	*cwd;
	char	*input;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
    	cwd = getcwd(NULL, sizeof(cwd));
		cwd = ft_strjoin(cwd, "$>");
		input = readline(cwd);
		// lexic(input);
		add_history(input);
		if (ft_strcmp(input, "exit") == 0)
			exit(0);
	}
	return (input);
}


int	get_cmd()
{
	char	*cmd;
	cmd = get_prompt();
	return 0;
}