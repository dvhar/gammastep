// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2009-2015  Jon Lund Steffensen <jonlst@gmail.com>
// Copyright (c) 2015  Mattias Andrée <maandree@member.fsf.org>
// signals.h -- Signal processing header

#ifndef REDSHIFT_SIGNALS_H
#define REDSHIFT_SIGNALS_H

extern volatile sig_atomic_t exiting;
extern volatile sig_atomic_t disable;
extern volatile sig_atomic_t temp_up_signal;
extern volatile sig_atomic_t temp_down_signal;

int signals_install_handlers(void);

#endif /* REDSHIFT_SIGNALS_H */
