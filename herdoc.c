/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:06:15 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/17 00:09:40 by ojamal           ###   ########.fr       */
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
	del = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (str[i])
	{
		del[i] = str[i];
		i++;
	}
	del[i] = '\0';
	return (del);
}

char	*remove_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			continue ;
		}
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

int	herd_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	herd_loop(char *del, int pipefd[2], t_env_node *env)
{
	char	*in;
	char	*tmp;

	tmp = del;
	close(pipefd[0]);
	while (1)
	{
		in = readline("herdoc> ");
		if (!in)
			break ;
		del = remove_quotes(del);
		if (ft_strcmp(del, in) == 0 && ft_strlen(del) == ft_strlen(in))
		{
			free(in);
			break ;
		}
		if (herd_quotes(tmp))
			replace_value(in, env, 0);
		else
			in = replace_value(in, env, 2);
		if (in)
			write(pipefd[1], in, ft_strlen(in));
		write(pipefd[1], "\n", 1);
		free(in);
	}
}

void	create_herdoc(char *str, t_env_node *env, t_cmd *cmd)
{
	int		pid;
	char	*del;
	int		pipefd[2];

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
		signal(SIGINT, herd_sig);
		herd_loop(str, pipefd, env);
		close(pipefd[1]);
		exit(0);
	}
	else
		herd_wait_sig(pid, cmd, del, pipefd);
}
