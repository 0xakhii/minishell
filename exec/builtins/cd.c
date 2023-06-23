/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:13:46 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/23 03:30:44 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void set_env_value(t_env_node **env, const char *key, const char *value)
{
	t_env_node *tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = strdup(value);
			return;
		}
		tmp = tmp->next;
	}
}
	
int cd_cmd(t_cmd *cmd, t_env_node *env)
{
	t_env_node *tmp = env;
	char *oldpwd = NULL;

	if (cmd->cmd[1] && cmd->cmd[1][0] == '~' && !cmd->cmd[1][1])
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, "HOME"))
			{
				if (chdir(tmp->value) != 0)
				{
					perror("chdir");
					return 0; // Return 0 on error
				}
				return 1; // Return 1 on success
			}
			tmp = tmp->next;
		}
		printf("HOME not set\n");
		return 0; // Return 0 if HOME is not set
	}
	else if (!cmd->cmd[1])
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, "HOME"))
			{
				if (chdir(tmp->value) != 0)
				{
					perror("chdir");
					return 0; // Return 0 on error
				}
				return 1; // Return 1 on success
			}
			tmp = tmp->next;
		}
		printf("HOME not set\n");
		return 0; // Return 0 if HOME is not set
	}
	if (cmd->cmd[1] && cmd->cmd[1][0] == '-' && !cmd->cmd[1][1])
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, "OLDPWD"))
			{
				if (tmp->value)
				{
					if (chdir(tmp->value) != 0)
					{
						perror("chdir");
						return 0;
					}
					oldpwd = getcwd(NULL, 0);
					if (!oldpwd)
					{
						perror("getcwd");
						return 0;
					}
					set_env_value(&env, "OLDPWD", oldpwd);  // Update OLDPWD in env
					free(oldpwd);
					return 1;
				}
				else
				{
					printf("cd: OLDPWD not set\n");
					return 0;
				}
			}
			tmp = tmp->next;
		}
		printf("OLDPWD not set\n");
		return 0;
	}
	else
	{
		while (tmp)
		{
			if (cmd->cmd[1])
			{
				if (chdir(cmd->cmd[1]) != 0)
				{
					perror("chdir");
					return 0; // Return 0 on error
				}
				return 1; // Return 1 on success
			}
			tmp = tmp->next;
		}
		printf("Directory not found\n");
		return 0; // Return 0 if the directory is not found
	}
}
