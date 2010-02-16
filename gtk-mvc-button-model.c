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

G_DEFINE_TYPE_WITH_CODE (GtkMvcButtonModel, gtk_mvc_button_model, G_TYPE_INITIALLY_UNOWNED,
                         G_IMPLEMENT_INTERFACE (GTK_MVC_TYPE_MODEL, NULL));

static void
gtk_mvc_button_model_init (GtkMvcButtonModel* self)
{}

static void
gtk_mvc_button_model_class_init (GtkMvcButtonModelClass* self_class)
{}

GtkMvcModel*
gtk_mvc_button_model_new (void)
{
  return g_object_new (GTK_MVC_TYPE_BUTTON_MODEL,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
