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

#include "gtk-mvc-scroll-view.h"

struct _GtkMvcScrollViewPrivate
{
  cairo_rectangle_t  position;
};

#define PRIV(i) (((GtkMvcScrollView*)(i))->_private)

static void implement_gtk_mvc_view (GtkMvcViewIface* iface);

G_DEFINE_TYPE_WITH_CODE (GtkMvcScrollView, gtk_scroll_view, G_TYPE_INITIALLY_UNOWNED,
                         G_IMPLEMENT_INTERFACE (GTK_MVC_TYPE_VIEW, implement_gtk_mvc_view));

static void
gtk_scroll_view_init (GtkMvcScrollView* self)
{
  PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self, GTK_MVC_TYPE_SCROLL_VIEW, GtkMvcScrollViewPrivate);
}

static void
gtk_scroll_view_class_init (GtkMvcScrollViewClass* self_class)
{
  g_type_class_add_private (self_class, sizeof (GtkMvcScrollViewPrivate));
}

static void
paint (GtkMvcView            * view,
       cairo_t               * cr,
       cairo_rectangle_t     * area,
       cairo_rectangle_list_t* region)
{
  cairo_save (cr);

  cairo_set_line_width (cr, 1.0);

  /* draw full area */
  cairo_rectangle (cr,
                   0.0, 0.0,
                   PRIV (view)->position.width,
                   PRIV (view)->position.height);
  cairo_set_source_rgb (cr,
                        1.0 / 0xff * 0x4e,
                        1.0 / 0xff * 0x9a,
                        1.0 / 0xff * 0x06);
  cairo_fill (cr);

  /* draw top button */
  cairo_rectangle (cr,
                   0.5, 0.5,
                   PRIV (view)->position.width - 1.0, PRIV (view)->position.width - 1.0);
  cairo_set_source_rgb (cr,
                        1.0 / 0xff * 0x20,
                        1.0 / 0xff * 0x4a,
                        1.0 / 0xff * 0x87);
  cairo_fill_preserve (cr);
  cairo_set_source_rgb (cr,
                        1.0 / 0xff * 0x72,
                        1.0 / 0xff * 0x9f,
                        1.0 / 0xff * 0xcf);
  cairo_stroke (cr);

  /* draw indicator */
  cairo_rectangle (cr,
                   0.5, PRIV (view)->position.width + 0.5,
                   PRIV (view)->position.width - 1.0,
                   PRIV (view)->position.height - 2 * PRIV (view)->position.width - 1.0);
  cairo_set_source_rgba (cr, 1.0, 1.0, 1.0, 0.25);
  cairo_fill_preserve (cr);
  cairo_set_source_rgba (cr, 1.0, 1.0, 1.0, 0.75);
  cairo_stroke (cr);

  /* draw bottom button */
  cairo_rectangle (cr,
                   0.5,
                   PRIV (view)->position.height - PRIV (view)->position.width + 0.5,
                   PRIV (view)->position.width - 1.0, PRIV (view)->position.width - 1.0);
  cairo_set_source_rgb (cr,
                        1.0 / 0xff * 0x20,
                        1.0 / 0xff * 0x4a,
                        1.0 / 0xff * 0x87);
  cairo_fill_preserve (cr);
  cairo_set_source_rgb (cr,
                        1.0 / 0xff * 0x72,
                        1.0 / 0xff * 0x9f,
                        1.0 / 0xff * 0xcf);
  cairo_stroke (cr);

  cairo_restore (cr);
}

static void
query_size (GtkMvcView    * view,
            gtk_mvc_size_t* size)
{
  /* FIXME: add realize() equivalent */
  size->width = 15; /* width */
  size->height = 45; /* (2 Buttons + 1 Scroll Area) * width */
}

static void
set_position (GtkMvcView       * view,
              cairo_rectangle_t* position)
{
  PRIV (view)->position = *position;
}

static void
implement_gtk_mvc_view (GtkMvcViewIface* iface)
{
  iface->paint        = paint;
  iface->query_size   = query_size;
  iface->set_position = set_position;
}

GtkMvcView*
gtk_mvc_scroll_view_new (void)
{
  return g_object_new (GTK_MVC_TYPE_SCROLL_VIEW,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
