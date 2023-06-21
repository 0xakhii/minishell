/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 08:46:30 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/21 04:17:30 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_path(t_cmd *cmd, t_env_node *env)
{
	char	**path;
	t_env_node *tmp;
	int		i;

	i = 0;
	tmp = env;
	while (ft_strnstr(tmp->key, "PATH", 4) == 0)
		i++;
	path = ft_split(tmp->key + 5, ':');
	i = 0;
}
