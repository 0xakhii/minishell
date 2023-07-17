/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:29:33 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/17 03:37:22 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_currdir(t_env_node *env)
{
	char	*copy;
	char	*path;
	char	*currdir;

	path = NULL;
	path = get_env_val(env, "PWD");
	if (path == NULL)
		return (NULL);
	currdir = ft_strrchr(path, '/');
	if (currdir)
		currdir++;
	else
		currdir = path;
	copy = ft_strdup(currdir);
	free(path);
	return (copy);
}

char	*join_str(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*result;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (result && s1 && s2)
	{
		ft_strcpy(result, s1);
		ft_strlcat(result, s2, (len1 + len2 + 1));
	}
	return (result);
}

void	herd_wait_sig(int pid, t_cmd *cmd, int pipefd[2])
{
	int	stat;

	close(pipefd[1]);
	cmd->in_fd = pipefd[0];
	waitpid(pid, &stat, 0);
	g_helper.exit_status = get_exit_status(stat);
}

t_tokens	*create_token(char *val, int type)
{
	t_tokens	*node;

	if (val == NULL)
	{
		node = malloc(sizeof(t_tokens));
		node->val = NULL;
		node->e_types = type;
		node->next = NULL;
	}
	else
	{
		node = malloc(sizeof(t_tokens));
		node->val = val;
		node->e_types = type;
		node->next = NULL;
	}
	return (node);
}

void	add_token(t_tokens **lexer, t_tokens *node)
{
	t_tokens	*current;

	if (*lexer == NULL)
		*lexer = node;
	else
	{
		current = *lexer;
		while (current->next != NULL)
			current = current->next;
		current->next = node;
	}
}
