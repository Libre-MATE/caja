/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*-

   caja-directory-notify.h: Caja directory notify calls.

   Copyright (C) 2000, 2001 Eazel, Inc.

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

   Author: Darin Adler <darin@bentspoon.com>
*/

#ifndef __CAJA_DIRECTORY_NOTIFY_H__
#define __CAJA_DIRECTORY_NOTIFY_H__

#include <gdk/gdk.h>

#include "caja-file.h"

typedef struct {
  char *from_uri;
  char *to_uri;
} URIPair;

typedef struct {
  GFile *from;
  GFile *to;
} GFilePair;

typedef struct {
  GFile *location;
  gboolean set;
  GdkPoint point;
  int screen;
} CajaFileChangesQueuePosition;

/* Almost-public change notification calls */
void caja_directory_notify_files_added(GList *files);
void caja_directory_notify_files_moved(GList *file_pairs);
void caja_directory_notify_files_changed(GList *files);
void caja_directory_notify_files_removed(GList *files);

void caja_directory_schedule_metadata_copy(GList *file_pairs);
void caja_directory_schedule_metadata_move(GList *file_pairs);
void caja_directory_schedule_metadata_remove(GList *files);

void caja_directory_schedule_metadata_copy_by_uri(GList *uri_pairs);
void caja_directory_schedule_metadata_move_by_uri(GList *uri_pairs);
void caja_directory_schedule_metadata_remove_by_uri(GList *uris);
void caja_directory_schedule_position_set(GList *position_setting_list);

/* Change notification hack.
 * This is called when code modifies the file and it needs to trigger
 * a notification. Eventually this should become private, but for now
 * it needs to be used for code like the thumbnail generation.
 */
void caja_file_changed(CajaFile *file);

#endif /* __CAJA_DIRECTORY_NOTIFY_H__ */
