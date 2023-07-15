/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:06:15 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/15 23:46:48 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*spaces_skip(char *str)
{
	int		i;
	char	*del;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	del = malloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i])
	{
		del[i] = str[i];
		i++;
	}
	del[i] = '\0';
	return (del);
}

int	herd_quotes(char *str)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (2);
}

int	create_herdoc(char *str, t_env_node *env)
{
	char *del;
	char *in;
	int pipefd[2];
	int pid;

	(void)env;
	del = spaces_skip(str);
	pipe(pipefd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		while (1)
		{
			in = readline("herdoc> ");
			if (!in)
				break ;
			if (ft_strcmp(del, in) == 0 && ft_strlen(del) == ft_strlen(in))
			{
				free(del);
				free(in);
				break ;
			}
			in = replace_value(in, env, 1);
			write(pipefd[1], in, ft_strlen(in));
			write(pipefd[1], "\n", 1);
			free(in);
		}
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		free(del);
		close(pipefd[1]);
		return (pipefd[0]);
	}
	
}
