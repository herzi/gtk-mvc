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

#include "gtk-mvc-view.h"

enum
{
  QUEUE_REDRAW,
  N_SIGNALS
};

static void gtk_mvc_view_iface_init (GtkMvcViewIface* iface);

static gint signals[N_SIGNALS] = {0};

GType
gtk_mvc_view_get_type (void)
{
  static GType type = 0;

  if (g_once_init_enter (&type))
    {
      GType registered = g_type_register_static_simple (G_TYPE_INTERFACE,
                                                        G_STRINGIFY (GtkMvcView),
                                                        sizeof (GtkMvcViewIface),
                                                        (GClassInitFunc)gtk_mvc_view_iface_init,
                                                        0, NULL, 0);
      g_once_init_leave (&type, registered);
    }

  return type;
}

static void
gtk_mvc_view_iface_init (GtkMvcViewIface* iface)
{
  signals[QUEUE_REDRAW] = g_signal_new ("queue-redraw",
                                        G_TYPE_FROM_INTERFACE (iface),
                                        G_SIGNAL_ACTION, 0,
                                        NULL, NULL,
                                        g_cclosure_marshal_VOID__VOID,
                                        G_TYPE_NONE, 0);
}

GList*
gtk_mvc_view_enumerate_children (GtkMvcView* self)
{
  GtkMvcViewIface* iface;

  g_return_val_if_fail (GTK_MVC_IS_VIEW (self), NULL);

  iface = GTK_MVC_VIEW_GET_IFACE (self);
  if (!iface->enumerate_children)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->enumerate_children",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
      return NULL;
    }

  return iface->enumerate_children (self);
}

GtkMvcController*
gtk_mvc_view_get_controller (GtkMvcView* self)
{
  GtkMvcViewIface* iface;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));

  iface = GTK_MVC_VIEW_GET_IFACE (self);
  if (!iface->get_controller)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->get_controller()",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
      return NULL;
    }

  return iface->get_controller (self);
}

GtkMvcModel*
gtk_mvc_view_get_model (GtkMvcView* self)
{
  GtkMvcViewIface* iface;

  g_return_val_if_fail (GTK_MVC_IS_VIEW (self), NULL);

  iface = GTK_MVC_VIEW_GET_IFACE (self);
  if (!iface->get_model)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->get_model()",
                 G_STRLOC, G_STRFUNC,
                 G_OBJECT_TYPE_NAME (self));

      return NULL;
    }

  return iface->get_model (self);
}

void
gtk_mvc_view_get_position (GtkMvcView       * self,
                           cairo_rectangle_t* position)
{
  GtkMvcViewIface* iface;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));
  g_return_if_fail (position);

  iface = GTK_MVC_VIEW_GET_IFACE (self);
  if (!iface->get_position)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->get_position()",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
    }
  else
    {
      iface->get_position (self, position);
    }
}

gboolean
gtk_mvc_view_hit_test (GtkMvcView* self,
                       double      x,
                       double      y)
{
  GtkMvcViewIface* iface;

  g_return_val_if_fail (GTK_MVC_IS_VIEW (self), FALSE);

  iface = GTK_MVC_VIEW_GET_IFACE (self);

  if (!iface->hit_test)
    {
      g_warning ("%s(%s): the type %s doesn't implement the GtkMvcViewIface->hit_test() function",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));

      return FALSE;
    }

  return iface->hit_test (self, x, y);
}

void
gtk_mvc_view_paint (GtkMvcView            * self,
                    cairo_t               * context,
                    cairo_rectangle_t     * area,
                    cairo_rectangle_list_t* region)
{
  GtkMvcViewIface* iface;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));
  g_return_if_fail (area);
  g_return_if_fail (region->status == CAIRO_STATUS_SUCCESS);

  iface = GTK_MVC_VIEW_GET_IFACE (self);
  if (!iface->paint)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->paint()",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
    }
  else if (cairo_status (context) == CAIRO_STATUS_SUCCESS)
    {
      cairo_rectangle_t  position;
      gtk_mvc_view_get_position (self, &position);

      cairo_save (context);
      cairo_translate (context, position.x, position.y);
      iface->paint (self, context, area, region);
      cairo_restore (context);
    }
}

void
gtk_mvc_view_query_size (GtkMvcView    * self,
                         gtk_mvc_size_t* size)
{
  GtkMvcViewIface* iface;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));
  g_return_if_fail (size);

  iface = GTK_MVC_VIEW_GET_IFACE (self);
  if (!iface->query_size)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->query_size()",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
    }
  else
    {
      iface->query_size (self, size);
    }
}

void
gtk_mvc_view_queue_redraw (GtkMvcView       * self,
                           cairo_rectangle_t* area)
{
  cairo_rectangle_t  position;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));

  if (!area)
    {
      gtk_mvc_view_get_position (self, &position);
      area = &position;
    }

  /* FIXME: add the area */

  g_signal_emit (self, signals[QUEUE_REDRAW], 0);
}

void
gtk_mvc_view_set_controller (GtkMvcView      * self,
                             GtkMvcController* controller)
{
  GtkMvcViewIface* iface;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));
  g_return_if_fail (!controller || GTK_MVC_IS_CONTROLLER (controller));

  iface = GTK_MVC_VIEW_GET_IFACE (self);
  if (!iface->set_controller)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->set_controller",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
    }
  else
    {
      iface->set_controller (self, controller);
    }
}

void
gtk_mvc_view_set_default_controller (GtkMvcView* self)
{
  GtkMvcViewIface* iface;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));

  iface = GTK_MVC_VIEW_GET_IFACE (self);

  if (!iface->create_default_controller)
    {
      /* FIXME: add tests for this */
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->create_default_controller()",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
    }
  else
    {
      GtkMvcController* controller = iface->create_default_controller (self);

      if (!controller)
        {
          /* FIXME: test for this */
          g_warning ("%s(%s): the type %s doesn't create a controller in GtkMvcViewIface->create_default_controller()",
                     G_STRFUNC, G_STRLOC,
                     G_OBJECT_TYPE_NAME (self));
        }
      else if (GTK_MVC_IS_CONTROLLER (controller))
        {
          gtk_mvc_view_set_controller (self, controller);
        }
      else
        {
          /* FIXME: test for this */
          g_warning ("%s(%s): the type %s doesn't create an object implementing "
                     "GtkMvcController in GtkMvcViewIface->create_default_controller()",
                     G_STRFUNC, G_STRLOC,
                     G_OBJECT_TYPE_NAME (self));
        }
    }
}

void
gtk_mvc_view_set_model (GtkMvcView * self,
                        GtkMvcModel* model)
{
  GtkMvcViewIface* iface;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));
  g_return_if_fail (!model || GTK_MVC_IS_MODEL (model));

  iface = GTK_MVC_VIEW_GET_IFACE (self);
  if (!iface->set_model)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->set_model()",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
    }
  else
    {
      iface->set_model (self, model);
    }
}

void
gtk_mvc_view_set_position (GtkMvcView       * self,
                           cairo_rectangle_t* position)
{
  GtkMvcViewIface* iface;

  g_return_if_fail (GTK_MVC_IS_VIEW (self));
  g_return_if_fail (position);

  iface = GTK_MVC_VIEW_GET_IFACE (self);

  if (!iface->set_position)
    {
      g_warning ("%s(%s): the type %s doesn't implement GtkMvcViewIface->set_position()",
                 G_STRFUNC, G_STRLOC,
                 G_OBJECT_TYPE_NAME (self));
    }
  else
    {
      iface->set_position (self, position);
    }
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
