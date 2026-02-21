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
volatile sig_atomic_t temp_reset_signal = 0;


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

/* Signal handler for temperature up signal */
static void
sigtup(int signo)
{
	temp_adj = 100;
}

/* Signal handler for temperature down signal */
static void
sigtndown(int signo)
{
	temp_adj = -100;
}

/* Signal handler for temperature up signal */
static void
sigtupbig(int signo)
{
	temp_adj = 500;
}

/* Signal handler for temperature down signal */
static void
sigtndownbig(int signo)
{
	temp_adj = -500;
}

/* Signal handler for temperature reset signal */
static void
sigtempreset(int signo)
{
	temp_reset_signal = 1;
}

int
signals_install_handlers(void)
{
	struct sigaction sigact;
	sigset_t sigset;
	int r;
	sigemptyset(&sigset);

	/* Install signal handler for INT and TERM signals */
	sigact.sa_handler = sigexit;
	sigact.sa_mask = sigset;
	sigact.sa_flags = 0;

	r = sigaction(SIGINT, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}

	r = sigaction(SIGTERM, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}

	/* Install signal handler for USR1 signal */
	sigact.sa_handler = sigdisable;
	sigact.sa_mask = sigset;
	sigact.sa_flags = 0;

	r = sigaction(SIGUSR1, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}

	/* Install signal handler for SIGRTMIN+1 signal */
	sigact.sa_handler = sigtup;
	sigact.sa_mask = sigset;
	sigact.sa_flags = 0;

	r = sigaction(SIGRTMIN + 1, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}

	/* Install signal handler for SIGRTMIN+2 signal */
	sigact.sa_handler = sigtndown;
	sigact.sa_mask = sigset;
	sigact.sa_flags = 0;

	r = sigaction(SIGRTMIN + 2, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}

	/* Install signal handler for SIGRTMIN+3 signal */
	sigact.sa_handler = sigtupbig;
	sigact.sa_mask = sigset;
	sigact.sa_flags = 0;

	r = sigaction(SIGRTMIN + 3, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}

	/* Install signal handler for SIGRTMIN+4 signal */
	sigact.sa_handler = sigtndownbig;
	sigact.sa_mask = sigset;
	sigact.sa_flags = 0;

	r = sigaction(SIGRTMIN + 4, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}

	/* Install signal handler for SIGRTMIN+5 signal */
	sigact.sa_handler = sigtempreset;
	sigact.sa_mask = sigset;
	sigact.sa_flags = 0;

	r = sigaction(SIGRTMIN + 5, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}

	/* Ignore CHLD signal. This causes child processes
	   (hooks) to be reaped automatically. */
	sigact.sa_handler = SIG_IGN;
	sigact.sa_mask = sigset;
	sigact.sa_flags = 0;

	r = sigaction(SIGCHLD, &sigact, NULL);
	if (r < 0) {
		perror("sigaction");
		return -1;
	}

	return 0;
}
