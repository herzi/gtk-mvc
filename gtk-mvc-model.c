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

#include "gtk-mvc-model.h"

enum {
        UPDATED,
        N_SIGNALS
};

static void  gtk_mvc_model_iface_init (GtkMvcModelIface* iface);

static guint signals[N_SIGNALS] = {0};

GType
gtk_mvc_model_get_type (void)
{
  static GType type = 0;

  if (g_once_init_enter (&type))
    {
      GType registered = g_type_register_static_simple (G_TYPE_INTERFACE,
                                                        G_STRINGIFY (GtkMvcModel),
                                                        sizeof (GtkMvcModelIface),
                                                        (GClassInitFunc) gtk_mvc_model_iface_init, 0,
                                                        NULL, 0);

      g_once_init_leave (&type, registered);
    }

  return type;
}

static void
gtk_mvc_model_iface_init (GtkMvcModelIface* iface)
{
  signals[UPDATED] = g_signal_new ("update",
                                   G_TYPE_FROM_INTERFACE (iface),
                                   G_SIGNAL_ACTION, 0,
                                   NULL, NULL,
                                   g_cclosure_marshal_VOID__VOID,
                                   G_TYPE_NONE, 0);
}

void
gtk_mvc_model_updated (GtkMvcModel* model)
{
  g_return_if_fail (GTK_MVC_IS_MODEL (model));

  g_signal_emit (model, signals[UPDATED], 0);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
