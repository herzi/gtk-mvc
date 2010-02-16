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

#include "gtk-mvc-default-view.h"

#include "gtk-mvc-default-controller.h"

struct _GtkMvcDefaultViewPrivate
{
  cairo_rectangle_t  position;
  GtkMvcController * controller;
  GtkMvcModel      * model;
};

#define PRIV(i) (((GtkMvcDefaultView*)(i))->_private)

static void implement_gtk_mvc_view (GtkMvcViewIface* iface);

G_DEFINE_TYPE_WITH_CODE (GtkMvcDefaultView, gtk_mvc_default_view, G_TYPE_INITIALLY_UNOWNED,
                         G_IMPLEMENT_INTERFACE (GTK_MVC_TYPE_VIEW, implement_gtk_mvc_view));

static void
gtk_mvc_default_view_init (GtkMvcDefaultView* self)
{
  PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self, GTK_MVC_TYPE_DEFAULT_VIEW, GtkMvcDefaultViewPrivate);
}

static void
constructed (GObject* object)
{
  /* FIXME: NULL as of 2.22.4 - add a testcase to find out if this is maybe
   * not required at some point in the future anymore */
  if (G_OBJECT_CLASS (gtk_mvc_default_view_parent_class)->constructed)
    {
      G_OBJECT_CLASS (gtk_mvc_default_view_parent_class)->constructed (object);
    }

  if (!PRIV (object)->controller)
    {
      gtk_mvc_view_set_default_controller (GTK_MVC_VIEW (object));
    }
}

static void
dispose (GObject* object)
{
  GtkMvcView* view = GTK_MVC_VIEW (object);

  gtk_mvc_view_set_controller (view, NULL);
  gtk_mvc_view_set_model (view, NULL);

  G_OBJECT_CLASS (gtk_mvc_default_view_parent_class)->dispose (object);
}

static void
gtk_mvc_default_view_class_init (GtkMvcDefaultViewClass* self_class)
{
  GObjectClass* object_class = G_OBJECT_CLASS (self_class);

  object_class->constructed = constructed;
  object_class->dispose     = dispose;

  g_type_class_add_private (self_class, sizeof (GtkMvcDefaultViewPrivate));
}

static GtkMvcController*
create_default_controller (GtkMvcView* self)
{
  return g_object_new (GTK_MVC_TYPE_DEFAULT_CONTROLLER,
                       NULL);
}

static GtkMvcController*
get_controller (GtkMvcView* view)
{
  return PRIV (view)->controller;
}

static GtkMvcModel*
get_model (GtkMvcView* view)
{
  return PRIV (view)->model;
}

static void
get_position (GtkMvcView       * view,
              cairo_rectangle_t* position)
{
  *position = PRIV (view)->position;
}

static void
set_controller (GtkMvcView      * view,
                GtkMvcController* controller)
{
  if (PRIV (view)->controller == controller)
    {
      /* FIXME: test this */
      return;
    }

  if (PRIV (view)->controller)
    {
      gtk_mvc_controller_introduce_view (PRIV (view)->controller,
                                         NULL);
      g_object_unref (PRIV (view)->controller);
      PRIV (view)->controller = NULL;
    }

  if (controller)
    {
      PRIV (view)->controller = g_object_ref_sink (controller);

      gtk_mvc_controller_introduce_view (PRIV (view)->controller,
                                         view);
    }
}

static void
set_model (GtkMvcView * view,
           GtkMvcModel* model)
{
  if (PRIV (view)->model == model)
    {
      /* FIXME: test this */
      return;
    }

  if (PRIV (view)->model)
    {
      g_object_unref (PRIV (view)->model);
      PRIV (view)->model = NULL;
    }

  if (model)
    {
      PRIV (view)->model = g_object_ref_sink (model);
    }
}

static void
set_position (GtkMvcView       * view,
              cairo_rectangle_t* position)
{
  PRIV (view)->position = *position;

  /* FIXME: trigger redraw */
}

static void
implement_gtk_mvc_view (GtkMvcViewIface* iface)
{
  iface->create_default_controller = create_default_controller;
  iface->get_controller            = get_controller;
  iface->get_model                 = get_model;
  iface->get_position              = get_position;
  iface->set_controller            = set_controller;
  iface->set_model                 = set_model;
  iface->set_position              = set_position;
}

GtkMvcView*
gtk_mvc_default_view_new (void)
{
  return g_object_new (GTK_MVC_TYPE_DEFAULT_VIEW,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
