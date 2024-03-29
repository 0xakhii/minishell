/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 08:46:30 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/20 22:23:58 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_exit_msg(char *str)
{
	ft_putstr_fd("exit\nexit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("numeric arguments required\n", 2);
}

void	ft_freeeeee(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
	av = NULL;
}

char	*ft_get_path(char *cmd, t_env_node *env)
{
	char		**path;
	t_env_node	*tmp;
	char		*temp;
	char		*new_p;
	int			i;

	i = 0;
	tmp = env;
	temp = get_env_val(tmp, "PATH");
	path = ft_split(temp + 5, ':');
	free(temp);
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		new_p = ft_strjoin(temp, cmd);
		if (access(new_p, X_OK) == 0)
		{
			free(path);
			return (new_p);
		}
		free(new_p);
		i++;
	}
	free(path);
	return (NULL);
}

char	**node_to_2d(t_env_node *env)
{
	int			j;
	char		**result;
	int			len;
	t_env_node	*tmp;

	tmp = env;
	j = 0;
	while (tmp && ++j)
		tmp = tmp->next;
	result = (char **)malloc((j + 1) * sizeof(char *));
	tmp = env;
	j = 0;
	while (tmp)
	{
		len = ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2;
		result[j] = (char *)malloc(len);
		ft_strncpy(result[j], tmp->key, len);
		ft_strlcat(result[j], "=", len);
		ft_strlcat(result[j], tmp->value, len);
		tmp = tmp->next;
		j++;
	}
	result[j] = NULL;
	return (result);
}

void	print_export(t_env_node **env)
{
	t_env_node	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->key)
		{
			printf("declare -x %s", tmp->key);
			if (ft_strcmp(tmp->value, "\0"))
			{
				if (tmp->value[0] != '\"' && tmp->value[ft_strlen(tmp->value)
						- 1] != '\"')
					printf("=\"%s\"", tmp->value);
				else
					printf("=%s", tmp->value);
			}
			printf("\n");
		}
		tmp = tmp->next;
	}
}
