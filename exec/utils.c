/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 08:46:30 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/21 23:42:59 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_free(char **av)
// {
// 	int	i;

// 	i = 0;
// 	while (av[i++])
// 		free(av[i]);
// 	free(av);
// }

// char	*ft_get_path(char *cmd, t_env_node *env)
// {
// 	char	**path;
// 	t_env_node *tmp;
// 	char	*new_p;
// 	int		i;

// 	i = 0;
// 	tmp = env;
// 	while (ft_strnstr(tmp->key, "PATH", 4) == 0)
// 		i++;
// 	path = ft_split(tmp->key + 5, ':');
// 	i = 0;
// 	while (path[i])
// 	{
// 		tmp = ft_strjoin(path[i], "/");
// 		new_p = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (access(new_p, X_OK) == 0)
// 			return (new_p);
// 		free(new_p);
// 		i++;
// 	}
// 	ft_free(path);
// 	return (0);
// }

