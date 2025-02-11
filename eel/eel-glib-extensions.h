/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */

/* eel-glib-extensions.h - interface for new functions that conceptually
                                belong in glib. Perhaps some of these will be
                                actually rolled into glib someday.

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

   Authors: John Sullivan <sullivan@eazel.com>
*/

#ifndef EEL_GLIB_EXTENSIONS_H
#define EEL_GLIB_EXTENSIONS_H

#include <gio/gio.h>
#include <glib.h>

/* A gboolean variant for bit fields. */
typedef guint eel_boolean_bit;

/* Predicate. */
typedef gboolean (*EelPredicateFunction)(gpointer data, gpointer callback_data);

/* GList functions. */
gboolean eel_g_list_exactly_one_item(GList *list);
gboolean eel_g_list_more_than_one_item(GList *list);
gboolean eel_g_list_equal(GList *list_a, GList *list_b);
gboolean eel_g_lists_sort_and_check_for_intersection(GList **list_a,
                                                     GList **list_b);
GList *eel_g_list_partition(GList *list, EelPredicateFunction predicate,
                            gpointer user_data, GList **removed);

/* List functions for lists of g_free'able objects. */
void eel_g_list_free_deep(GList *list);

/* List functions for lists of C strings. */
gboolean eel_g_str_list_equal(GList *str_list_a, GList *str_list_b);
GList *eel_g_str_list_alphabetize(GList *str_list);
int eel_g_str_list_index(GList *str_list, const char *str);

/* GHashTable functions */
GHashTable *eel_g_hash_table_new_free_at_exit(GHashFunc hash_function,
                                              GCompareFunc key_compare_function,
                                              const char *display_name);
void eel_g_hash_table_safe_for_each(GHashTable *hash_table, GHFunc callback,
                                    gpointer callback_data);

/* NULL terminated string arrays (strv). */
int eel_g_strv_find(char **strv, const char *find_me);
gboolean eel_g_strv_equal(char **a, char **b);

/* math */
int eel_round(double d);

/* Better weak pointer functions */
void eel_add_weak_pointer(gpointer pointer_location);
void eel_remove_weak_pointer(gpointer pointer_location);

void eel_g_settings_add_auto_enum(GSettings *settings, const char *key,
                                  int *storage);
void eel_g_settings_add_auto_int(GSettings *settings, const char *key,
                                 int *storage);
void eel_g_settings_add_auto_boolean(GSettings *settings, const char *key,
                                     gboolean *storage);
void eel_g_settings_add_auto_strv(GSettings *settings, const char *key,
                                  char ***storage);
void eel_g_settings_add_auto_strv_as_quarks(GSettings *settings,
                                            const char *key, GQuark **storage);

#endif /* EEL_GLIB_EXTENSIONS_H */
