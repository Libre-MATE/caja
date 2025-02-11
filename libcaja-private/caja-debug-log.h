/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*-

   caja-debug-log.h: Ring buffer for logging debug messages

   Copyright (C) 2006 Novell, Inc.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public
   License along with this program; if not, write to the
   Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
   Boston, MA 02110-1301, USA.

   Author: Federico Mena-Quintero <federico@novell.com>
*/

#ifndef CAJA_DEBUG_LOG_H
#define CAJA_DEBUG_LOG_H

#include <glib.h>

#define CAJA_DEBUG_LOG_DOMAIN_USER "USER" /* always enabled */
#define CAJA_DEBUG_LOG_DOMAIN_ASYNC \
  "async" /* when asynchronous notifications come in */
#define CAJA_DEBUG_LOG_DOMAIN_GLOG \
  "GLog" /* used for GLog messages; don't use it yourself */

void caja_debug_log(gboolean is_milestone, const char *domain,
                    const char *format, ...);

void caja_debug_log_with_uri_list(gboolean is_milestone, const char *domain,
                                  const GList *uris, const char *format, ...);
void caja_debug_log_with_file_list(gboolean is_milestone, const char *domain,
                                   GList *files, const char *format, ...);

void caja_debug_logv(gboolean is_milestone, const char *domain,
                     const GList *uris, const char *format, va_list args);

gboolean caja_debug_log_load_configuration(const char *filename,
                                           GError **error);

void caja_debug_log_enable_domains(const char **domains, int n_domains);
void caja_debug_log_disable_domains(const char **domains, int n_domains);

gboolean caja_debug_log_is_domain_enabled(const char *domain);

gboolean caja_debug_log_dump(const char *filename, GError **error);

void caja_debug_log_set_max_lines(int num_lines);
int caja_debug_log_get_max_lines(void);

/* For testing only */
void caja_debug_log_clear(void);

#endif /* CAJA_DEBUG_LOG_H */
