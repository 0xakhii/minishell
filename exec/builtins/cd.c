/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:13:46 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/18 18:55:47 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_chdir(t_env_node *env, char *val)
{
	char	*path;
	int		error;

	path = get_env_val(env, val);
	error = chdir(path);
	free(path);
	return (error);
}

int	cd_home(t_cmd *cmd, t_env_node **env)
{
	int		error;
	char	*oldpwd;
	char	*new;

	new = NULL;
	error = 0;
	oldpwd = NULL;
	if (!cmd->cmd[1] || (cmd->cmd[1] && cmd->cmd[1][0] == '~'
		&& !cmd->cmd[1][1]))
	{
		oldpwd = getcwd(oldpwd, 0);
		error = ft_chdir(*env, "HOME");
		if (error == -1)
			return (free(oldpwd), printf("HOME not set\n"));
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
	int		error;
	char	*oldpwd;
	char	*new;

	new = NULL;
	error = 0;
	oldpwd = NULL;
	if (cmd->cmd[1] && cmd->cmd[1][0] == '-' && !cmd->cmd[1][1])
	{
		oldpwd = getcwd(oldpwd, 0);
		error = ft_chdir(*env, "OLDPWD");
		if (error == -1)
			return (free(oldpwd), printf("OLDPWD not set\n"));
		else
		{
			new = getcwd(new, 0);
			set_env_value(env, "OLDPWD", oldpwd);
			set_env_value(env, "PWD", new);
			printf("%s\n", new);
			free(new);
			free(oldpwd);
			return (1);
		}
	}
	return (0);
}

int	cd_dir(t_cmd *cmd, t_env_node **env)
{
	int		error;
	char	*oldpwd;
	char	*new;

	new = NULL;
	error = 0;
	oldpwd = NULL;
	oldpwd = getcwd(oldpwd, 0);
	error = chdir(cmd->cmd[1]);
	if (error == -1)
	{
		perror("chdir");
		free(oldpwd);
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

int	cd_cmd(t_cmd *cmd, t_env_node **env)
{
	if (cd_home(cmd, env))
		return (0);
	if (cd_oldpwd(cmd, env))
		return (0);
	if (cmd->cmd[1])
	{
		if (cd_dir(cmd, env))
			return (0);
	}
	return (1);
}
