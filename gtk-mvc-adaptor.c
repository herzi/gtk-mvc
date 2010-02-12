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

#include "gtk-mvc-adaptor.h"

struct _GtkMvcAdaptorPrivate
{
  GtkMvcView* view;
};

enum
{
  PROP_0,
  PROP_VIEW
};

#define PRIV(i) (((GtkMvcAdaptor*)(i))->_private)

G_DEFINE_TYPE (GtkMvcAdaptor, gtk_mvc_adaptor, GTK_TYPE_LABEL);

static void
gtk_mvc_adaptor_init (GtkMvcAdaptor* self)
{
  PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self, GTK_MVC_TYPE_ADAPTOR, GtkMvcAdaptorPrivate);
}

static void
dispose (GObject* object)
{
  if (PRIV (object)->view)
    {
      g_object_unref (PRIV (object)->view);
      PRIV (object)->view = NULL;
    }

  G_OBJECT_CLASS (gtk_mvc_adaptor_parent_class)->dispose (object);
}

static void
get_property (GObject   * object,
              guint       prop_id,
              GValue    * value,
              GParamSpec* pspec)
{
  g_warning ("%s(%s): unimplemented",
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
    case PROP_VIEW:
      g_return_if_fail (!PRIV (object)->view);

      PRIV (object)->view = g_value_dup_object (value);
      g_object_notify (object, "view");
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
gtk_mvc_adaptor_class_init (GtkMvcAdaptorClass* self_class)
{
  GObjectClass* object_class = G_OBJECT_CLASS (self_class);

  object_class->dispose      = dispose;
  object_class->get_property = get_property;
  object_class->set_property = set_property;

  g_object_class_install_property (object_class, PROP_VIEW,
                                   g_param_spec_object ("view", NULL, NULL,
                                                        G_TYPE_OBJECT,
                                                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

  g_type_class_add_private (self_class, sizeof (GtkMvcAdaptorPrivate));
}

GtkWidget*
gtk_mvc_adaptor_new (GtkMvcView* view)
{
  return g_object_new (GTK_MVC_TYPE_ADAPTOR,
                       "label", "GtkMvcAdaptor",
                       "view", view,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
