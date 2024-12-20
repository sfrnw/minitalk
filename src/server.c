/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:05:48 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/20 11:39:30 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Handles incoming signals from clients.
// Reconstructs characters bit by bit from received signals.
// Prints characters and sends acknowledgments back to the client.
void	handler(int sigusr, siginfo_t *info, void *unused)
{
	static unsigned char	c = 0;
	static int				bit = 0;
	static int				client;

	(void)unused;
	if (info->si_pid)
		client = info->si_pid;
	if (sigusr == SIGUSR1)
		c |= (1 << (7 - bit));
	else if (sigusr == SIGUSR2)
		c &= ~(1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		if (c == 0)
		{
			write(1, "\n", 1);
			kill_with_checking(client, SIGUSR2);
		}
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
	}
	kill(client, SIGUSR1);
}

// Purpose: Entry point of the server program.
// Prints its own PID.
// Sets up signal handlers for SIGUSR1 and SIGUSR2.
// Enters an infinite loop waiting for signals.
// (the pause function causes the calling thread 
// to pause until the signal recieved)
int	main(void)
{
	int	pid;

	pid = getpid();
	if (pid == -1)
		return (ft_putstr_fd("getpid failed", 2), 1);
	ft_printf("SERVER PID=%d\n", pid);
	ft_signal(SIGUSR1, handler, true);
	ft_signal(SIGUSR2, handler, true);
	while (1)
		pause();
	return (0);
}
