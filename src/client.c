/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:08:36 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/20 11:39:31 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// volatile: This keyword tells the compiler that the variable's value
// can change at any time without any action being taken by the code the 
// compiler finds nearby. It's often used with variables that are accessed
// by interrupt service routines or signal handlers.
// sig_atomic_t: This is a data type guaranteed to be read and written
// atomically, even in the presence of asynchronous interrupts made by
// signals. It's typically used for variables shared between the main
// program and a signal handler.

// This global variable is used to coordinate communication between the
// main program and the signal handlers, ensuring safe access to shared
// data in an asynchronous environment. 

volatile sig_atomic_t	g_server = 1;

// Handles acknowledgment signals from the server.
// Sets g_server to 0, indicating the server is ready.
void	ack_handler(int sigusr)
{
	(void)sigusr;
	g_server = 0;
}

// Handles the end-of-transmission signal from the server.
// Prints a message and exits the program.
void	end_handler(int sigusr)
{
	(void)sigusr;
	ft_putstr_fd("Message received by server\n", 1);
	exit(0);
}

// Purpose: Sends a single character to the server bit by bit.
// Uses SIGUSR1 for 1 and SIGUSR2 for 0.
// Waits for server acknowledgment after sending each bit.
static void	send_char(unsigned char c, int server_pid)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (c & (1 << bit))
			kill_with_checking(server_pid, SIGUSR1);
		else
			kill_with_checking(server_pid, SIGUSR2);
		while (g_server == 1)
			usleep(100);
		g_server = 1;
		bit--;
	}
}

// Purpose: Sends a string to the server character by character.
// Calls send_char for each character and sends a null terminator at the end.
static void	send_string(char *str, int server_pid)
{
	while (*str)
	{
		send_char((unsigned char)*str, server_pid);
		str++;
	}
	send_char(0, server_pid);
}

// Entry point of the client program.
// Validates input arguments and server PID.
// Sets up signal handlers and sends the message to the server.
// Waits for final acknowledgment or times out.
int	main(int argc, char **argv)
{
	int	server_pid;

	if (argc != 3)
		return (ft_putstr_fd("Usage: ./client<server_PID> \"Message\"\n",
				2), 1);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		return (ft_putstr_fd("Invalid server PID\n", 2), 1);
	ft_signal(SIGUSR1, ack_handler, false);
	ft_signal(SIGUSR2, end_handler, false);
	send_string(argv[2], server_pid);
	while (g_server == 1)
	{
		if (usleep(100000) == -1)
			return (ft_putstr_fd("Timeout: No response from server\n", 2), 1);
	}
	return (0);
}
