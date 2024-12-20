/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:06:41 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/20 15:27:16 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include "../libft/src/libft.h"
# include "../libft/src/ft_printf/ft_printf.h"

void	kill_with_checking(int pid, int signo);
void	ft_signal(int sig, void *handler, bool use_siginfo);

#endif

// MAN
//sigaction
// struct sigaction {
// 	void     (*sa_handler)(int); - a pointer to a signal handler function
// 	void     (*sa_sigaction)(int, siginfo_t *, void *); - alternative 
//                        handler when SA_SIGINFO flag is set
// 	sigset_t   sa_mask; - mask to apply (for blocking signals)
// 	int        sa_flags; - signal options
// 	void     (*sa_restorer)(void);
// };
//siginfo_t
// typedef struct {
// 	int      si_signo;  /* Signal number */
// 	int      si_code;   /* Signal code */
// 	pid_t    si_pid;    /* Sending process ID */ (!!!)
// 	uid_t    si_uid;    /* Real user ID of sending process */
// 	void    *si_addr;   /* Address of faulting instruction */
// 	int      si_status; /* Exit value or signal */
// 	union sigval si_value;  /* Signal value */
// } siginfo_t;