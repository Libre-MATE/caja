/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */

/* fm-list-view-private.h - Private functions for both the list and search list
   view to share

   Copyright (C) 2000 Eazel, Inc.

   The Mate Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The Mate Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the Mate Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
   Boston, MA 02110-1301, USA.

   Authors: Rebecca Schulman <rebecka@mit.edu>

*/

struct FMListViewColumn {
  const char *attribute;
  const char *title;
  CajaFileSortType sort_criterion;
  int minimum_width, default_width, maximum_width;
  gboolean right_justified;
};

void fm_list_view_column_set(FMListViewColumn *column, const char *attribute,
                             const char *title, CajaFileSortType sort_criterion,
                             int minimum_width, int default_width,
                             int maximum_width, gboolean right_justified);
