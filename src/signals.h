// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2009-2015  Jon Lund Steffensen <jonlst@gmail.com>
// Copyright (c) 2015  Mattias Andrée <maandree@member.fsf.org>
// signals.h -- Signal processing header

#ifndef REDSHIFT_SIGNALS_H
#define REDSHIFT_SIGNALS_H

extern volatile sig_atomic_t exiting;
extern volatile sig_atomic_t disable;
extern volatile sig_atomic_t temp_adj;
extern volatile sig_atomic_t temp_reset;

int signals_install_continuous_mode_handlers(void);
int signals_install_manual_mode_handlers(void);

#endif /* REDSHIFT_SIGNALS_H */
