/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:28:27 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/19 21:35:01 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_tokens	*in_files_norm(t_tokens *current_token, t_env_node *env,
		t_cmd **new_cmd, char *file_name)
{
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
	free(file_name);
	return (current_token);
}

t_tokens	*in_files(t_cmd **new_cmd, t_tokens *current_token, t_env_node *env)
{
	char	*file_name;

	file_name = NULL;
	current_token = in_files_norm(current_token, env, new_cmd, file_name);
	if (current_token->next && current_token->e_types == T_HERD)
	{
		current_token = current_token->next;
		signal(SIGINT, SIG_IGN);
		if ((*new_cmd)->in_fd == -1 || (*new_cmd)->out_fd == -1)
			return (current_token);
		if ((*new_cmd)->in_fd)
			close((*new_cmd)->in_fd);
		create_herdoc(current_token->val, env, *new_cmd);
		if ((*new_cmd)->in_fd == -1)
			perror(current_token->val);
	}
	return (current_token);
}

t_tokens	*out_files_norm(t_cmd **new_cmd, t_tokens *current_token,
		t_env_node *env, char *file_name)
{
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
	free(file_name);
	return (current_token);
}

t_tokens	*out_files(t_cmd **new_cmd, t_tokens *current_token,
		t_env_node *env)
{
	char	*file_name;

	file_name = NULL;
	current_token = out_files_norm(new_cmd, current_token, env, file_name);
	if (current_token->next && current_token->e_types == T_APP)
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
	free(file_name);
	return (current_token);
}
