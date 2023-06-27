/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:13:46 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/27 06:30:31 by ojamal           ###   ########.fr       */
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
			if(value)
				tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}

int	cd_home(t_cmd *cmd, t_env_node **env)
{
	int	error;
	char *oldpwd;
	char *new;

	new = NULL;
	error = 0;
	oldpwd = NULL;
	if (!cmd->cmd[1] || (cmd->cmd[1] && cmd->cmd[1][0] == '~' && !cmd->cmd[1][1]))
	{
		oldpwd = getcwd(oldpwd, 0);
		error = chdir(get_env_val(*env, "HOME"));
		if (error == -1)
			return (printf("HOME not set\n"));
		else
		{
			new = getcwd(new, 0);
			set_env_value(env, "OLDPWD", oldpwd);
			set_env_value(env, "PWD", new);
			free(new);
			free(oldpwd);
			return (1);
		}
	}
	return (0);
}

int	cd_oldpwd(t_cmd *cmd, t_env_node **env)
{
	int	error;
	char *oldpwd;
	char *new;

	new = NULL;
	error = 0;
	oldpwd = NULL;
	if (cmd->cmd[1] && cmd->cmd[1][0] == '-' && !cmd->cmd[1][1])
	{
		oldpwd = getcwd(oldpwd, 0);
		error = chdir(get_env_val(*env, "OLDPWD"));
		if (error == -1)
			return (printf("OLDPWD not set\n"));
		else
		{
			new = getcwd(new, 0);
			set_env_value(env, "OLDPWD", oldpwd);
			set_env_value(env, "PWD", new);
			free(new);
			free(oldpwd);
			printf("%s\n", get_env_val(*env, "PWD"));
			return (1);
		}
    }
	return (0);
}

int	cd_dir(t_cmd *cmd, t_env_node **env)
{
	int	error;
	char *oldpwd;
	char *new;

	new = NULL;
	error = 0;
	oldpwd = NULL;
	oldpwd = getcwd(oldpwd, 0);
	error = chdir(cmd->cmd[1]);
	if (error == -1)
	{
		perror("chdir");
		return (0);
	}
	else
	{	
		new = getcwd(new, 0);
		set_env_value(env, "OLDPWD", oldpwd);
		set_env_value(env, "PWD", new);
		free(new);
		free(oldpwd);
		return (1);
	}
	return (0);
}

int cd_cmd(t_cmd *cmd, t_env_node **env)
{
	if (cd_home(cmd, env))
		return (0);
	if (cd_oldpwd(cmd, env))
		return (0);
	if (cmd->cmd[1])
		if (cd_dir(cmd, env))
			return (0);
	return (1);
}
