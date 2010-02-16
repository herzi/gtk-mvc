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

#include "gtk-mvc-button-model.h"

struct _GtkMvcButtonModelPrivate
{
  guint pushed : 1;
};

#define PRIV(i) (((GtkMvcButtonModel*)(i))->_private)

G_DEFINE_TYPE_WITH_CODE (GtkMvcButtonModel, gtk_mvc_button_model, G_TYPE_INITIALLY_UNOWNED,
                         G_IMPLEMENT_INTERFACE (GTK_MVC_TYPE_MODEL, NULL));

static void
gtk_mvc_button_model_init (GtkMvcButtonModel* self)
{
  PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self, GTK_MVC_TYPE_BUTTON_MODEL, GtkMvcButtonModelPrivate);
}

static void
gtk_mvc_button_model_class_init (GtkMvcButtonModelClass* self_class)
{
  g_type_class_add_private (self_class, sizeof (GtkMvcButtonModelPrivate));
}

gboolean
gtk_mvc_button_model_get_pushed (GtkMvcButtonModel* self)
{
  g_return_val_if_fail (GTK_MVC_IS_BUTTON_MODEL (self), FALSE);

  return PRIV (self)->pushed;
}

GtkMvcModel*
gtk_mvc_button_model_new (void)
{
  return g_object_new (GTK_MVC_TYPE_BUTTON_MODEL,
                       NULL);
}

void
gtk_mvc_button_model_set_pushed (GtkMvcButtonModel* self,
                                 gboolean           pushed)
{
  g_return_if_fail (GTK_MVC_IS_BUTTON_MODEL (self));
  g_return_if_fail (pushed == TRUE || pushed == FALSE);

  if (PRIV (self)->pushed == pushed)
    {
      return;
    }

  PRIV (self)->pushed = pushed;

  gtk_mvc_model_updated (GTK_MVC_MODEL (self));
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
