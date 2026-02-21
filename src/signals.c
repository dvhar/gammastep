// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2009-2015  Jon Lund Steffensen <jonlst@gmail.com>
// Copyright (c) 2015  Mattias Andrée <maandree@member.fsf.org>
// signals.c -- Signal processing source

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>
#include <signal.h>

#include "signals.h"


volatile sig_atomic_t exiting = 0;
volatile sig_atomic_t disable = 0;
volatile sig_atomic_t temp_adj = 0;
volatile sig_atomic_t temp_reset = 0;


/* Signal handler for exit signals */
static void
sigexit(int signo)
{
	exiting = 1;
}

/* Signal handler for disable signal */
static void
sigdisable(int signo)
{
	disable = 1;
}

/* Signal handler for small temperature up signal */
static void
sigsmallup(int signo)
{
	temp_adj = 100;
}

/* Signal handler for small temperature down signal */
static void
sigsmalldown(int signo)
{
	temp_adj = -100;
}

/* Signal handler for big temperature up signal */
static void
sigbigup(int signo)
{
	temp_adj = 500;
}

/* Signal handler for big temperature down signal */
static void
sigbigdown(int signo)
{
	temp_adj = -500;
}

/* Signal handler for temperature reset signal */
static void
sigtempreset(int signo)
{
	temp_reset = 1;
}

int set_signal(int sig, void (*func)(int)) {
	struct sigaction sigact;
	sigset_t sigset;
	int r;

	sigemptyset(&sigset);
	sigact.sa_handler = func;
	sigact.sa_mask = sigset;
	sigact.sa_flags = 0;

	r = sigaction(sig, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}
	return 0;
}

int
signals_install_handlers(void)
{
	/* Install signal handler for INT and TERM signals */
	return set_signal(SIGINT, sigexit) ?:
	set_signal(SIGTERM, sigexit) ?:

	/* Install signal handler for USR1 signal */
	set_signal(SIGUSR1, sigdisable) ?:

	set_signal(SIGCHLD, SIG_IGN);

}

int
install_remote_control_handlers(void)
{
	/* Install handlers for manual-mode remote control signals */
	return set_signal(SIGRTMIN + 1, sigsmallup) ?:
	    set_signal(SIGRTMIN + 2, sigsmalldown) ?:
	    set_signal(SIGRTMIN + 3, sigbigup) ?:
	    set_signal(SIGRTMIN + 4, sigbigdown) ?:
	    set_signal(SIGRTMIN + 5, sigtempreset);
}
