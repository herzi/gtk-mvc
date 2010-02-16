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

#include "gtk-mvc.h"

static void implement_gtk_mvc_view (GtkMvcViewIface* iface);

G_DEFINE_TYPE_WITH_CODE (GtkMvcArrowView, gtk_mvc_arrow_view, GTK_MVC_TYPE_DEFAULT_VIEW,
                         G_IMPLEMENT_INTERFACE (GTK_MVC_TYPE_VIEW, implement_gtk_mvc_view));

static void
gtk_mvc_arrow_view_init (GtkMvcArrowView* self)
{}

static void
gtk_mvc_arrow_view_class_init (GtkMvcArrowViewClass* self_class)
{}

static void
paint (GtkMvcView            * view,
       cairo_t               * context,
       cairo_rectangle_t     * area,
       cairo_rectangle_list_t* region)
{
  cairo_rectangle_t  position = {0.0, 0.0, 0.0, 0.0};
  GtkMvcModel      * model = gtk_mvc_view_get_model (view);

  if (!model)
    {
      return;
    }

  gtk_mvc_view_get_position (view, &position);

  cairo_save (context);
  cairo_translate (context, position.width / 2, position.height / 2);
  switch (gtk_mvc_arrow_model_get_arrow (GTK_MVC_ARROW_MODEL (model)))
    {
    case GTK_ARROW_NONE:
      break;
    case GTK_ARROW_RIGHT:
      cairo_rotate (context, G_PI / 2);
    case GTK_ARROW_UP:
      cairo_rotate (context, G_PI / 2);
    case GTK_ARROW_LEFT:
      cairo_rotate (context, G_PI / 2);
    case GTK_ARROW_DOWN:
      cairo_line_to (context, 0.0, MIN (position.height, position.width) / 2 - 2.0);
      cairo_rotate (context, 2 * G_PI / 3);
      cairo_line_to (context, 0.0, MIN (position.height, position.width) / 2);
      cairo_rotate (context, 2 * G_PI / 3);
      cairo_line_to (context, 0.0, MIN (position.height, position.width) / 2);
      cairo_rotate (context, 2 * G_PI / 3);
      cairo_close_path (context);
      break;
    }
  cairo_restore (context);
  cairo_set_source_rgb (context,
                        1.0 / 0xff * 0xee,
                        1.0 / 0xff * 0xee,
                        1.0 / 0xff * 0xec);
  cairo_fill (context);
  cairo_restore (context);
}

static void
implement_gtk_mvc_view (GtkMvcViewIface* iface)
{
  iface->paint = paint;
}

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
