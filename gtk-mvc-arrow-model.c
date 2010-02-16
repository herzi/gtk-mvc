/* This file is part of herzi's playground
 *
 * Copyright (C) 2010  Sven Herzberg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#include "gtk-mvc-arrow-model.h"

struct _GtkMvcArrowModelPrivate
{
  GtkArrowType  arrow;
};

enum
{
  PROP_0,
  PROP_ARROW
};

#define PRIV(i) (((GtkMvcArrowModel*)(i))->_private)

G_DEFINE_TYPE (GtkMvcArrowModel, gtk_mvc_arrow_model, G_TYPE_INITIALLY_UNOWNED);

static void
gtk_mvc_arrow_model_init (GtkMvcArrowModel* self)
{
  PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self, GTK_MVC_TYPE_ARROW_MODEL, GtkMvcArrowModelPrivate);
  PRIV (self)->arrow = GTK_ARROW_NONE;
}

static void
get_property (GObject   * object,
              guint       prop_id,
              GValue    * value,
              GParamSpec* pspec)
{
  g_warning ("%s(%s): FIXME: unimplemented",
             G_STRFUNC, G_STRLOC);
}

static void
set_property (GObject     * object,
              guint         prop_id,
              GValue const* value,
              GParamSpec  * pspec)
{
  switch (prop_id)
    {
    case PROP_ARROW:
      PRIV (object)->arrow = g_value_get_enum (value);
      g_object_notify (object, "arrow");
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
gtk_mvc_arrow_model_class_init (GtkMvcArrowModelClass* self_class)
{
  GObjectClass* object_class = G_OBJECT_CLASS (self_class);

  object_class->get_property = get_property;
  object_class->set_property = set_property;

  g_object_class_install_property (object_class, PROP_ARROW,
                                   g_param_spec_enum ("arrow", NULL, NULL,
                                                      GTK_TYPE_ARROW_TYPE, GTK_ARROW_NONE,
                                                      G_PARAM_READWRITE));

  g_type_class_add_private (self_class, sizeof (GtkMvcArrowModelPrivate));
}

GtkMvcModel*
gtk_mvc_arrow_model_new (GtkArrowType  arrow)
{
  return g_object_new (GTK_MVC_TYPE_ARROW_MODEL,
                       "arrow", arrow,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
