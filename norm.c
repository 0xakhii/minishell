/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:52:07 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/18 18:54:49 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dir(int flag, t_env_node *env)
{
	char	*currdir;
	char	*color;
	char	*prompt;
	char	*tmp;

	currdir = get_currdir(env);
	if (flag)
		color = "\033[1;31m";
	else
		color = "\033[1;32m";
	prompt = join_str(color, "➜ \033[0m");
	tmp = join_str(" \033[1;36m", currdir);
	free(currdir);
	currdir = tmp;
	tmp = join_str(currdir, "\033[0m ");
	free(currdir);
	currdir = tmp;
	tmp = join_str(prompt, currdir);
	free(currdir);
	free(prompt);
	return (tmp);
}

void	free_tokens(t_tokens **t)
{
	t_tokens	*tmp;

	while (*t)
	{
		tmp = (*t)->next;
		free((*t)->val);
		free(*t);
		*t = tmp;
	}
}

char	expand_norm(char c, char *str, int i)
{
	if (c == 0 && (str[i] == '\"' || str[i] == '\''))
		c = str[i];
	else if (c == str[i])
		c = 0;
	return (c);
}

void	herd_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(1);
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
