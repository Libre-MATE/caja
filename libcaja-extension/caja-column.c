/*
 *  caja-column.c - Info columns exported by CajaColumnProvider
 *                      objects.
 *
 *  Copyright (C) 2003 Novell, Inc.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 *  Author:  Dave Camp <dave@ximian.com>
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib/gi18n-lib.h>

#include "caja-column.h"

enum {
  PROP_0,
  PROP_NAME,
  PROP_ATTRIBUTE,
  PROP_ATTRIBUTE_Q,
  PROP_LABEL,
  PROP_DESCRIPTION,
  PROP_XALIGN,
  LAST_PROP
};

struct _CajaColumnDetails {
  char *name;
  GQuark attribute;
  char *label;
  char *description;
  float xalign;
};

G_DEFINE_TYPE(CajaColumn, caja_column, G_TYPE_OBJECT);

/**
 * SECTION:caja-column
 * @title: CajaColumn
 * @short_description: List view column descriptor object
 * @include: libcaja-extension/caja-column.h
 *
 * #CajaColumn is an object that describes a column in the file manager
 * list view. Extensions can provide #CajaColumn by registering a
 * #CajaColumnProvider and returning them from
 * caja_column_provider_get_columns(), which will be called by the main
 * application when creating a view.
 */

/**
 * caja_column_new:
 * @name: identifier of the column
 * @attribute: the file attribute to be displayed in the column
 * @label: the user-visible label for the column
 * @description: a user-visible description of the column
 *
 * Creates a new column
 *
 * Returns: a newly created #CajaColumn
 */
CajaColumn *caja_column_new(const char *name, const char *attribute,
                            const char *label, const char *description) {
  CajaColumn *column;

  g_return_val_if_fail(name != NULL, NULL);
  g_return_val_if_fail(attribute != NULL, NULL);
  g_return_val_if_fail(label != NULL, NULL);
  g_return_val_if_fail(description != NULL, NULL);

  column = g_object_new(CAJA_TYPE_COLUMN, "name", name, "attribute", attribute,
                        "label", label, "description", description, NULL);

  return column;
}

static void caja_column_get_property(GObject *object, guint param_id,
                                     GValue *value, GParamSpec *pspec) {
  CajaColumn *column;

  column = CAJA_COLUMN(object);

  switch (param_id) {
    case PROP_NAME:
      g_value_set_string(value, column->details->name);
      break;
    case PROP_ATTRIBUTE:
      g_value_set_string(value, g_quark_to_string(column->details->attribute));
      break;
    case PROP_ATTRIBUTE_Q:
      g_value_set_uint(value, column->details->attribute);
      break;
    case PROP_LABEL:
      g_value_set_string(value, column->details->label);
      break;
    case PROP_DESCRIPTION:
      g_value_set_string(value, column->details->description);
      break;
    case PROP_XALIGN:
      g_value_set_float(value, column->details->xalign);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, param_id, pspec);
      break;
  }
}

static void caja_column_set_property(GObject *object, guint param_id,
                                     const GValue *value, GParamSpec *pspec) {
  CajaColumn *column;

  column = CAJA_COLUMN(object);

  switch (param_id) {
    case PROP_NAME:
      g_free(column->details->name);
      column->details->name = g_strdup(g_value_get_string(value));
      g_object_notify(object, "name");
      break;
    case PROP_ATTRIBUTE:
      column->details->attribute =
          g_quark_from_string(g_value_get_string(value));
      g_object_notify(object, "attribute");
      g_object_notify(object, "attribute_q");
      break;
    case PROP_LABEL:
      g_free(column->details->label);
      column->details->label = g_strdup(g_value_get_string(value));
      g_object_notify(object, "label");
      break;
    case PROP_DESCRIPTION:
      g_free(column->details->description);
      column->details->description = g_strdup(g_value_get_string(value));
      g_object_notify(object, "description");
      break;
    case PROP_XALIGN:
      column->details->xalign = g_value_get_float(value);
      g_object_notify(object, "xalign");
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, param_id, pspec);
      break;
  }
}

static void caja_column_finalize(GObject *object) {
  CajaColumn *column;

  column = CAJA_COLUMN(object);

  g_free(column->details->name);
  g_free(column->details->label);
  g_free(column->details->description);

  g_free(column->details);

  G_OBJECT_CLASS(caja_column_parent_class)->finalize(object);
}

static void caja_column_init(CajaColumn *column) {
  column->details = g_new0(CajaColumnDetails, 1);
  column->details->xalign = 0.0;
}

static void caja_column_class_init(CajaColumnClass *class) {
  G_OBJECT_CLASS(class)->finalize = caja_column_finalize;
  G_OBJECT_CLASS(class)->get_property = caja_column_get_property;
  G_OBJECT_CLASS(class)->set_property = caja_column_set_property;

  g_object_class_install_property(
      G_OBJECT_CLASS(class), PROP_NAME,
      g_param_spec_string(
          "name", "Name", "Name of the column", NULL,
          G_PARAM_CONSTRUCT_ONLY | G_PARAM_WRITABLE | G_PARAM_READABLE));
  g_object_class_install_property(
      G_OBJECT_CLASS(class), PROP_ATTRIBUTE,
      g_param_spec_string("attribute", "Attribute",
                          "The attribute name to display", NULL,
                          G_PARAM_READWRITE));
  g_object_class_install_property(
      G_OBJECT_CLASS(class), PROP_ATTRIBUTE_Q,
      g_param_spec_uint("attribute_q", "Attribute quark",
                        "The attribute name to display, in quark form", 0,
                        G_MAXUINT, 0, G_PARAM_READABLE));
  g_object_class_install_property(
      G_OBJECT_CLASS(class), PROP_LABEL,
      g_param_spec_string("label", "Label", "Label to display in the column",
                          NULL, G_PARAM_READWRITE));
  g_object_class_install_property(
      G_OBJECT_CLASS(class), PROP_DESCRIPTION,
      g_param_spec_string("description", "Description",
                          "A user-visible description of the column", NULL,
                          G_PARAM_READWRITE));

  g_object_class_install_property(
      G_OBJECT_CLASS(class), PROP_XALIGN,
      g_param_spec_float("xalign", "xalign", "The x-alignment of the column",
                         0.0, 1.0, 0.0, G_PARAM_READWRITE));
}
