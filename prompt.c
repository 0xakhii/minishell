/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 09:28:52 by ojamal            #+#    #+#             */
/*   Updated: 2023/02/25 09:54:10 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*cmd_parser(char *input)
{
	t_node	*head;
	t_node	*tmp;
	t_cmd	*cmd;
	int		i;

	i = 0;
	head = NULL;
	while (input[i])
	{
		if (input[i] == PIPE)
		{
			cmd = (t_cmd *)malloc(sizeof(t_cmd));
			cmd->cmd = ft_substr(input, 0, i);
			cmd->args = ft_split(cmd->cmd, ' ');
			tmp = (t_node *)malloc(sizeof(t_node));
			tmp->cmd = cmd;
			tmp->next = head;
			head = tmp;
			input = ft_substr(input, i + 1, ft_strlen(input));
			i = 0;
		}
		i++;
	}
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->cmd = ft_substr(input, 0, i);
	cmd->args = ft_split(cmd->cmd, ' ');
	tmp = (t_node *)malloc(sizeof(t_node));
	tmp->cmd = cmd;
	tmp->next = head;
	head = tmp;
	return (head);
}

void	herdoc()
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open("herdoc.txt", O_RDWR | O_CREAT, 0777);
	while (1)
	{
		line = readline("herdoc> ");
		if (ft_strcmp(line, "\"") == 0)
			break ;
		else if (ft_strcmp(line, "\'") == 0)
			break ;
		ft_putendl_fd(line, fd);
	}
	close(fd);
}

char	*get_prompt()
{
	char	*cwd;
	char	*input;
	t_node	*head;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
    	cwd = getcwd(NULL, sizeof(cwd));
		cwd = ft_strjoin(cwd, "$>");
		input = readline(cwd);
		if (!check_all(input))
			herdoc();
		head = cmd_parser(input);
		add_history(input);
		if (ft_strcmp(input, "exit") == 0)
			exit(0);
	}
	return (input);
}


int	get_cmd()
{
	char	*cmd;
	cmd = get_prompt();
	return 0;
}