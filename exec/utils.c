/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 08:46:30 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/27 05:38:58 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freeeeee(char **av)
{
	int i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
	av = NULL;
}

char *ft_get_path(char *cmd, t_env_node *env)
{
	char **path;
	t_env_node *tmp;
	char *temp;
	char *new_p;
	int i = 0;

	tmp = env;
	temp = get_env_val(tmp, "PATH");
	path = ft_split(temp + 5, ':');
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		new_p = ft_strjoin(temp, cmd);
		if (access(new_p, X_OK) == 0)
		{
			free(path);
			return new_p;
		}
		free(new_p);
		i++;
	}
	free(path);
	return NULL;
}

char **node_to_2d(t_env_node *env)
{
	int j;
	int i;
	t_env_node *tmp;

	j = 0;
	tmp = env;
	while (tmp)
	{
		j++;
		tmp = tmp->next;
	}
	char **result = (char **)malloc((j + 1) * sizeof(char *));
	tmp = env;
	i = 0;
	while (tmp)
	{
		result[i] = (char *)malloc((ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2) * sizeof(char));
		ft_strncpy(result[i], tmp->key, ft_strlen(tmp->key));
		result[i][ft_strlen(tmp->key)] = '=';
		ft_strncpy(result[i] + (ft_strlen(tmp->key) + 1), tmp->value, ft_strlen(tmp->value));
		result[i][(ft_strlen(tmp->key) + ft_strlen(tmp->value)) - 1] = '\0';
		i++;
		tmp = tmp->next;
	}
	return ((result[i] = NULL), (result));
}
