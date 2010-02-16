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

#include "gtk-mvc-button-view.h"

#include "gtk-mvc.h"

struct _GtkMvcButtonViewPrivate
{
  GtkMvcView* child;
};

#define PRIV(i) (((GtkMvcButtonView*)(i))->_private)

static GtkMvcViewIface* gtk_mvc_view_parent_iface = NULL;

static void implement_gtk_mvc_view (GtkMvcViewIface* iface);

G_DEFINE_TYPE_WITH_CODE (GtkMvcButtonView, gtk_mvc_button_view, GTK_MVC_TYPE_DEFAULT_VIEW,
                         G_IMPLEMENT_INTERFACE (GTK_MVC_TYPE_VIEW, implement_gtk_mvc_view));

static void
gtk_mvc_button_view_init (GtkMvcButtonView* self)
{
  PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self, GTK_MVC_TYPE_BUTTON_VIEW, GtkMvcButtonViewPrivate);
}

static void
dispose (GObject* object)
{
  gtk_mvc_button_view_set_child (GTK_MVC_BUTTON_VIEW (object), NULL);

  G_OBJECT_CLASS (gtk_mvc_button_view_parent_class)->dispose (object);
}

static void
gtk_mvc_button_view_class_init (GtkMvcButtonViewClass* self_class)
{
  GObjectClass* object_class = G_OBJECT_CLASS (self_class);

  object_class->dispose = dispose;

  g_type_class_add_private (self_class, sizeof (GtkMvcButtonViewPrivate));
}

static GtkMvcController*
create_default_controller (GtkMvcView* view)
{
  return gtk_mvc_button_controller_new ();
}

static gboolean
hit_test (GtkMvcView* view,
          double      x,
          double      y)
{
  cairo_rectangle_t  rectangle = {0.0, 0.0, 0.0, 0.0};

  gtk_mvc_view_get_position (view, &rectangle);

  if (x >= rectangle.x && y >= rectangle.y &&
      x - rectangle.x <= rectangle.width &&
      y - rectangle.y <= rectangle.height)
    {
      return TRUE;
    }

  return FALSE;
}

static void
paint (GtkMvcView            * view,
       cairo_t               * context,
       cairo_rectangle_t     * area,
       cairo_rectangle_list_t* region)
{
  cairo_rectangle_t  position;
  GtkMvcModel      * model = gtk_mvc_view_get_model (view);

  gtk_mvc_view_get_position (view, &position);
  cairo_set_line_width (context, 1.0);
  cairo_rectangle (context,
                   0.5, 0.5,
                   position.width - 1.0, position.height - 1.0);
  if (GTK_MVC_IS_BUTTON_MODEL (model) && gtk_mvc_button_model_get_pushed (GTK_MVC_BUTTON_MODEL (model)))
    {
      cairo_set_source_rgb (context,
                            1.0 / 0xff * 0x20,
                            1.0 / 0xff * 0x4a,
                            1.0 / 0xff * 0x87);
    }
  else
    {
      cairo_set_source_rgb (context,
                            1.0 / 0xff * 0x34,
                            1.0 / 0xff * 0x65,
                            1.0 / 0xff * 0xa4);
    }
  cairo_fill_preserve (context);
  if (PRIV (view)->child)
    {
      cairo_save (context);
      cairo_new_path (context);
      gtk_mvc_view_paint (PRIV (view)->child, context,
                          area, region);
      cairo_restore (context);
    }
  cairo_set_source_rgb (context,
                        1.0 / 0xff * 0x72,
                        1.0 / 0xff * 0x9f,
                        1.0 / 0xff * 0xcf);
  cairo_stroke (context);
}

static void
update_from_model (GtkMvcModel* model,
                   GtkMvcView * view)
{
  cairo_rectangle_t  position;

  gtk_mvc_view_get_position (view, &position);

  gtk_mvc_view_queue_redraw (view, &position);
}

static void
set_model (GtkMvcView * view,
           GtkMvcModel* model)
{
  GtkMvcModel* old_model;

  if (model && !GTK_MVC_IS_BUTTON_MODEL (model))
    {
      return;
    }

  old_model = gtk_mvc_view_get_model (view);
  if (old_model)
    {
      /* FIXME: store the signal handler id */
      g_signal_handlers_disconnect_by_func (model, update_from_model, view);
    }

  gtk_mvc_view_parent_iface->set_model (view, model);

  if (model)
    {
      g_signal_connect (model, "update",
                        G_CALLBACK (update_from_model), view);
    }
}

static void
set_position (GtkMvcView       * view,
              cairo_rectangle_t* position)
{
  gtk_mvc_view_parent_iface->set_position (view, position);

  if (PRIV (view)->child)
    {
      cairo_rectangle_t  child_position;

      /* FIXME: make the border width themable */
      /* FIXME: check child requisition */
      if (position->width >= 1.0 + 2 * 2.0) /*min-size + 2*border*/
        {
          child_position.x = 2.0;
          child_position.width = position->width - 2 * 2.0;
        }
      else
        {
          g_warning ("%s(%s): FIXME: implement horizontal scaling",
                     G_STRFUNC, G_STRLOC);
          child_position.x = 0.0;
          child_position.width = position->width;
        }

      if (position->height >= 1.0 + 2 * 2.0)
        {
          child_position.y = 2.0;
          child_position.height = position->height - 2 * 2.0;
        }
      else
        {
          g_warning ("%s(%s): FIXME: implement vertical scaling",
                     G_STRFUNC, G_STRLOC);
          child_position.y = 0.0;
          child_position.height = position->height;
        }

      gtk_mvc_view_set_position (PRIV (view)->child, &child_position);
    }
}

static void
implement_gtk_mvc_view (GtkMvcViewIface* iface)
{
  gtk_mvc_view_parent_iface = g_type_interface_peek_parent (iface);

  iface->create_default_controller = create_default_controller;
  iface->hit_test                  = hit_test;
  iface->paint                     = paint;
  iface->set_model                 = set_model;
  iface->set_position              = set_position;
}

void
gtk_mvc_button_view_set_child (GtkMvcButtonView* self,
                               GtkMvcView      * child)
{
  g_return_if_fail (GTK_MVC_IS_BUTTON_VIEW (self));
  g_return_if_fail (!child || GTK_MVC_IS_VIEW (child));

  if (PRIV (self)->child == child)
    {
      return;
    }

  if (PRIV (self)->child)
    {
      /* FIXME: disconnect from the child */
      g_object_unref (PRIV (self)->child);
      PRIV (self)->child = NULL;
    }

  if (child)
    {
      PRIV (self)->child = g_object_ref_sink (child);
      /* FIXME: connect to the child */
    }
}

GtkMvcView*
gtk_mvc_button_view_new (void)
{
  return g_object_new (GTK_MVC_TYPE_BUTTON_VIEW,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
