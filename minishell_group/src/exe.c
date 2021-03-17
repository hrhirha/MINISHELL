/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/17 18:24:50 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		shell_launch2(t_command *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command->full_args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exist.last_exec = 127;
	return (1);
}

int		shell_launch3(t_command *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command->full_args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (126);
}

void	shell_launch4(t_command *command, int pid, char *execter)
{
	waitpid(pid, &g_exist.last_exec, 0);
	g_exist.last_exec = WEXITSTATUS(g_exist.last_exec);
	if (ft_str_has_char(command->full_args[0], '/') == 0)
	{
		free(execter);
	}
}

char	*shell_launch5(t_minishell *minishell, t_command *command)
{
	char	*execter;

	if (ft_str_has_char(command->full_args[0], '/') == 0)
		execter = found_exec(command, minishell);
	else
		execter = command->full_args[0];
	return (execter);
}

int		shell_launch(t_minishell *minishell, t_command *command)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	*execter;

	execter = shell_launch5(minishell, command);
	if (execter == NULL)
		return (shell_launch2(command));
	pid = fork();
	g_exist.pid = 1;
	if (pid == 0)
	{
		if (execve(execter, command->full_args, minishell->env) == -1)
			exit(shell_launch3(command));
		else
			exit(0);
		
	}
	else if (pid < 0)
	{
		ft_putstr_fd("minishell: Fork failed to create a new process \n", 2);
		g_exist.last_exec = 127;
	}
	shell_launch4(command, pid, execter);
	return (1);
}
