/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:10:21 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/18 02:22:47 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_env_value(t_env_node **env, const char *key, const char *value)
{
	t_env_node	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (value)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			return ;
		}
		tmp = tmp->next;
	}
}

void	add_node(t_env_node **env, char *key, char *value)
{
	t_env_node	*new_node;
	t_env_node	*temp;

	temp = *env;
	new_node = create_env_node(key, value);
	if (*env == NULL)
		*env = new_node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

t_env_node	*find_node(t_env_node **env, char *key)
{
	t_env_node	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	execute_builtins(t_cmd *cmd, t_env_node **env)
{
	if (!cmd->cmd)
		return ;
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		echo_cmd(cmd, cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		print_env(cmd->cmd, *env);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		my_exit(cmd);
	if (!ft_strcmp(cmd->cmd[0], "pwd"))
		pwd_cmd(*env);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		cd_cmd(cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		export_variable(cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		my_unset(cmd, env);
	else
		return ;
}

int	is_builtins(t_cmd *cmd)
{
	if (!cmd->cmd)
		return (0);
	if (!ft_strcmp(cmd->cmd[0], "echo") || (!ft_strcmp(cmd->cmd[0], "env"))
		|| (!ft_strcmp(cmd->cmd[0], "exit")) || (!ft_strcmp(cmd->cmd[0], "pwd"))
		|| (!ft_strcmp(cmd->cmd[0], "cd")) || (!ft_strcmp(cmd->cmd[0],
				"export")) || (!ft_strcmp(cmd->cmd[0], "unset")))
		return (1);
	return (0);
}
