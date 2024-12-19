/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:21:01 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/15 17:18:06 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Sends a signal to a process with error checking.
// Exits the program if the kill function fails.
void	kill_with_checking(int pid, int sigusr)
{
	if (kill(pid, sigusr) < 0)
	{
		ft_putstr_fd("Kill failed: ", 2);
		exit(1);
	}
}

// Sets up a signal handler with optional siginfo support.
// Configures a sigaction structure and sets up the signal handler.
// Exits the program if sigaction fails.

// When SA_SIGINFO is set, the signal handler receives extra
// information about the signal through a siginfo_t structure.
// This structure contains details such as the process ID of
// the sender, which is crucial for the server to identify 
// and respond to different clients.

void	ft_signal(int sigusr, void *handler, bool use_siginfo)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	if (use_siginfo)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
	}
	else
		
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sigusr, &sa, NULL) < 0)
	{
		ft_putstr_fd("Sigaction failed: ", 2);
		exit(1);
	}
}
