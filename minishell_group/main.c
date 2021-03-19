/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 12:32:27 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/18 16:28:13 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getline(char **line, t_data *data)
{
	int parsing_ret;

	data->i = 0;
	write(1, PROMPT, ft_strlen(PROMPT));
	get_next_line(0, line);
	parsing_ret = parse_line(*line, data);
	if (parsing_ret == 0)
		pipes_loop(data->command);
	free_data(data);
}

void	signals(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exist.pid == 0)
		{
			ft_putstr_fd("\b\b  \b\n", 1);
			write(1, PROMPT, ft_strlen(PROMPT));
		}
		else if (g_exist.pid == 1)
			ft_putstr_fd("\n", 1);
	}
	if (sig == SIGQUIT)
	{
		if (g_exist.pid == 1)
			ft_putstr_fd("Quit: 3\n", 1);
		else if (g_exist.pid == 0)
			ft_putstr_fd("\b\b  \b\b", 1);
	}
}

int		main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*line;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	if (!data)
		exit_errno(ENOMEM);
	data->command = malloc(sizeof(t_minishell));
	if (!data->command)
		exit_errno(ENOMEM);
	set_env(env, data);
	signal(SIGINT, signals);
	signal(SIGQUIT, signals);
	data->command->out = dup(1);
	data->command->in = dup(0);
	while (1)
	{
		g_exist.pid = 0;
		ft_getline(&line, data);
		free(line);
	}
	free_tab(data->command->env);
	free(data->command);
	free(data);
}