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

#include "gtk-mvc-arrow-view.h"

G_DEFINE_TYPE (GtkMvcArrowView, gtk_mvc_arrow_view, GTK_MVC_TYPE_DEFAULT_VIEW);

static void
gtk_mvc_arrow_view_init (GtkMvcArrowView* self)
{}

static void
gtk_mvc_arrow_view_class_init (GtkMvcArrowViewClass* self_class)
{}

GtkMvcView*
gtk_mvc_arrow_view_new_with_model (GtkMvcModel* model)
{
  GtkMvcView* result = g_object_new (GTK_MVC_TYPE_ARROW_VIEW,
                                     NULL);

  /* FIXME: turn into a property */
  gtk_mvc_view_set_model (result, model);

  return result;
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
