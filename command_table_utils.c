/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:03:01 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/18 00:10:15 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*table_init(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	new_cmd->cmd = NULL;
	new_cmd->in_file = NULL;
	new_cmd->out_file = NULL;
	new_cmd->pipe = 0;
	new_cmd->in_fd = -2;
	new_cmd->out_fd = -2;
	return (new_cmd);
}

t_tokens	*files_process(t_cmd **new_cmd, t_tokens *current_token,
		t_env_node *env)
{
	current_token = in_files(new_cmd, current_token, env);
	current_token = out_files(new_cmd, current_token, env);
	if (current_token->e_types == T_PIPE)
	{
		(*new_cmd)->next = table_init();
		(*new_cmd)->next->pipe++;
		(*new_cmd)->next->prev = (*new_cmd);
		(*new_cmd) = (*new_cmd)->next;
		g_helper.exit_status = 0;
	}
	return (current_token);
}

char	**ft_arrjoin(char **split, char *str)
{
	char	**new_split;
	int		i;

	i = 0;
	if (split == NULL)
	{
		new_split = malloc(2 * sizeof(char *));
		new_split[0] = ft_strdup(str);
		new_split[1] = NULL;
	}
	else
	{
		while (split[i])
			i++;
		new_split = malloc((i + 2) * sizeof(char *));
		i = 0;
		while (split[i])
		{
			new_split[i] = ft_strdup(split[i]);
			i++;
		}
		new_split[i] = ft_strdup(str);
		new_split[i + 1] = NULL;
	}
	return (new_split);
}

void	cmd_process(t_tokens *current_token, t_cmd **new_cmd, t_env_node *env,
		int flag)
{
	int		i;
	char	**str;
	char	**tmp;

	if (current_token->e_types == T_STR)
	{
		i = 0;
		str = new_expand(current_token->val, env, flag);
		while (str && str[i])
		{
			tmp = (*new_cmd)->cmd;
			(*new_cmd)->cmd = ft_arrjoin((*new_cmd)->cmd, str[i]);
			ft_freeeeee(tmp);
			free(str[i++]);
		}
		free(str);
		(*new_cmd)->e_types = T_CMD;
	}
}

t_cmd	*create_command_table(t_tokens *lexer, t_env_node *env)
{
	t_cmd		*cmd_table;
	t_tokens	*current_token;
	t_cmd		*new_cmd;

	cmd_table = NULL;
	current_token = lexer;
	new_cmd = table_init();
	cmd_table = new_cmd;
	while (current_token)
	{
		cmd_process(current_token, &new_cmd, env, 2);
		current_token = files_process(&new_cmd, current_token, env);
		current_token = current_token->next;
	}
	g_helper.exit_status = 0;
	return (cmd_table);
}
