/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:28:27 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/11 18:43:58 by ojamal           ###   ########.fr       */
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

char	*get_file_name(char *file_name, t_env_node *env)
{
	char	**str;
	char	*tmp;

	str = new_expand(file_name, env, 2);
	if (!str || !str[0] || str[1])
	{
		ft_freeeeee(str);
		msg_er("ambiguous redirect");
		return (NULL);
	}
	tmp = ft_strdup(str[0]);
	ft_freeeeee(str);
	return (tmp);
}

t_tokens	*in_files(t_cmd **new_cmd, t_tokens *current_token, t_env_node *env)
{
	char	*file_name;

	if (current_token->next && current_token->e_types == T_IN_RD)
	{
		current_token = current_token->next;
		if ((*new_cmd)->in_fd == -1 || (*new_cmd)->out_fd == -1)
			return (current_token);
		if ((*new_cmd)->in_fd)
			close((*new_cmd)->in_fd);
		file_name = get_file_name(current_token->val, env);
		if (!file_name)
		{
			(*new_cmd)->in_fd = -1;
			return (current_token);
		}
		(*new_cmd)->in_fd = open(file_name, O_RDONLY, 0644);
		if ((*new_cmd)->in_fd == -1)
			perror(file_name);
	}
	else if (current_token->next && current_token->e_types == T_HERD)
	{
		current_token = current_token->next;
		if ((*new_cmd)->in_fd == -1 || (*new_cmd)->out_fd == -1)
			return (current_token);
		if ((*new_cmd)->in_fd)
			close((*new_cmd)->in_fd);
		(*new_cmd)->in_file = ft_strdup(current_token->val);
		if ((*new_cmd)->in_fd == -1)
			perror(current_token->val);
	}
	return (current_token);
}

t_tokens	*out_files(t_cmd **new_cmd, t_tokens *current_token,
		t_env_node *env)
{
	char	*file_name;

	if (current_token->next && current_token->e_types == T_OUT_RD)
	{
		current_token = current_token->next;
		if ((*new_cmd)->in_fd == -1 || (*new_cmd)->out_fd == -1)
			return (current_token);
		if ((*new_cmd)->out_fd)
			close((*new_cmd)->out_fd);
		file_name = get_file_name(current_token->val, env);
		if (!file_name)
		{
			(*new_cmd)->out_fd = -1;
			return (current_token);
		}
		(*new_cmd)->out_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if ((*new_cmd)->out_fd == -1)
			perror(file_name);
	}
	else if (current_token->next && current_token->e_types == T_APP)
	{
		current_token = current_token->next;
		if ((*new_cmd)->in_fd == -1 || (*new_cmd)->out_fd == -1)
			return (current_token);
		if ((*new_cmd)->out_fd)
			close((*new_cmd)->out_fd);
		file_name = get_file_name(current_token->val, env);
		if (!file_name)
		{
			(*new_cmd)->out_fd = -1;
			return (current_token);
		}
		(*new_cmd)->out_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if ((*new_cmd)->out_fd == -1)
			perror(file_name);
	}
	return (current_token);
}

t_tokens	*files_process(t_cmd **new_cmd, t_tokens *current_token,
		t_env_node *env)
{
	current_token = in_files(new_cmd, current_token, env);
	current_token = out_files(new_cmd, current_token, env);
	if (current_token->e_types == T_PIPE)
	{
		(*new_cmd)->pipe++;
		(*new_cmd)->next = table_init();
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
	free_tokens(&lexer);
	return (cmd_table);
}
