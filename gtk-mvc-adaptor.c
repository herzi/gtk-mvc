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

#include "gdk-window.h"

struct _GtkMvcAdaptorPrivate
{
  GdkWindow  * event_window;
  GtkMvcModel* model;
  GtkMvcView * view;
  guint        view_handler_queue_redraw;
};

enum
{
  PROP_0,
  PROP_MODEL,
  PROP_VIEW
};

#define PRIV(i) (((GtkMvcAdaptor*)(i))->_private)

G_DEFINE_TYPE (GtkMvcAdaptor, gtk_mvc_adaptor, GTK_TYPE_WIDGET);

static void
gtk_mvc_adaptor_init (GtkMvcAdaptor* self)
{
  PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self, GTK_MVC_TYPE_ADAPTOR, GtkMvcAdaptorPrivate);

  GTK_WIDGET_SET_FLAGS (self, GTK_NO_WINDOW);
}

static void
constructed (GObject* object)
{
  if (G_OBJECT_CLASS (gtk_mvc_adaptor_parent_class)->constructed)
    {
      G_OBJECT_CLASS (gtk_mvc_adaptor_parent_class)->constructed (object);
    }

  if (PRIV (object)->model && PRIV (object)->view)
    {
      gtk_mvc_view_set_model (PRIV (object)->view,
                              PRIV (object)->model);
    }
}

static void
dispose (GObject* object)
{
  if (PRIV (object)->model)
    {
      g_object_unref (PRIV (object)->model);
      PRIV (object)->model = NULL;
    }

  if (PRIV (object)->view)
    {
      g_signal_handler_disconnect (PRIV (object)->view,
                                   PRIV (object)->view_handler_queue_redraw);
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
queue_redraw_from_view (GtkMvcView   * view,
                        GtkMvcAdaptor* self)
{
  /* FIXME: support partial updates */
  gtk_widget_queue_draw (GTK_WIDGET (self));
}

static void
set_property (GObject     * object,
              guint         prop_id,
              GValue const* value,
              GParamSpec  * pspec)
{
  switch (prop_id)
    {
    case PROP_MODEL:
      g_return_if_fail (!PRIV (object)->model);
      g_return_if_fail (!g_value_get_object (value) || GTK_MVC_IS_MODEL (g_value_get_object (value)));

      PRIV (object)->model = g_value_dup_object (value);
      g_object_notify (object, "model");
      break;
    case PROP_VIEW:
      g_return_if_fail (!PRIV (object)->view);
      g_return_if_fail (!g_value_get_object (value) || GTK_MVC_IS_VIEW (g_value_get_object (value)));

      PRIV (object)->view = g_value_dup_object (value);
      if (PRIV (object)->view)
        {
          PRIV (object)->view_handler_queue_redraw = g_signal_connect (PRIV (object)->view, "queue-redraw",
                                                                       G_CALLBACK (queue_redraw_from_view), object);
        }
      g_object_notify (object, "view");
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static gboolean
button_press_event (GtkWidget     * widget,
                    GdkEventButton* event)
{
  gboolean handled = FALSE;

  if (PRIV (widget)->view)
    {
      GtkMvcController* controller = gtk_mvc_view_get_controller (PRIV (widget)->view);

      if (controller)
        {
          handled = gtk_mvc_controller_handle_button_press (controller,
                                                            event->device,
                                                            event->x,
                                                            event->y);
        }
    }

  return handled;
}

static gboolean
button_release_event (GtkWidget     * widget,
                      GdkEventButton* event)
{
  gboolean handled = FALSE;

  if (PRIV (widget)->view)
    {
      GtkMvcController* controller = gtk_mvc_view_get_controller (PRIV (widget)->view);

      if (controller)
        {
          handled = gtk_mvc_controller_handle_button_release (controller,
                                                              event->device,
                                                              event->x,
                                                              event->y);
        }
    }

  return handled;
}

static void
map (GtkWidget* widget)
{
  GTK_WIDGET_CLASS (gtk_mvc_adaptor_parent_class)->map (widget);

  gdk_window_show_unraised (PRIV (widget)->event_window);
}

static void
realize (GtkWidget* widget)
{
  GTK_WIDGET_CLASS (gtk_mvc_adaptor_parent_class)->realize (widget);

  PRIV (widget)->event_window = gfc_gdk_window_new (widget->window,
                                                    "class", GDK_INPUT_ONLY,
                                                    "event-mask", GDK_ALL_EVENTS_MASK,
                                                    "x", widget->allocation.x,
                                                    "y", widget->allocation.y,
                                                    "width", widget->allocation.width,
                                                    "height", widget->allocation.height,
                                                    NULL);
  gdk_window_set_user_data (PRIV (widget)->event_window, widget);

  GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);
}

static void
size_request (GtkWidget     * widget,
              GtkRequisition* request)
{
  if (PRIV (widget)->view)
    {
      gtk_mvc_size_t  size = {0.0, 0.0};

      gtk_mvc_view_query_size (PRIV (widget)->view, &size);

      request->width = size.width;
      request->height = size.height;
    }
}

static void
size_allocate (GtkWidget    * widget,
               GtkAllocation* allocation)
{
  GTK_WIDGET_CLASS (gtk_mvc_adaptor_parent_class)->size_allocate (widget, allocation);

  if (PRIV (widget)->view)
    {
      cairo_rectangle_t  position = {allocation->x, allocation->y, allocation->width, allocation->height};
      gtk_mvc_view_set_position (PRIV (widget)->view, &position);
    }

  if (GTK_WIDGET_REALIZED (widget))
    {
      gdk_window_move_resize (PRIV (widget)->event_window,
                              allocation->x, allocation->y,
                              allocation->width, allocation->height);
    }
}

static gboolean
expose_event (GtkWidget     * widget,
              GdkEventExpose* event)
{
  if (PRIV (widget)->view)
    {
      cairo_rectangle_list_t  region = {
              CAIRO_STATUS_SUCCESS,
              NULL,
              0
      };
      cairo_rectangle_t  area = {
              0.0,
              0.0,
              event->area.width,
              event->area.height
      };
      GdkRectangle          * rectangles = NULL;
      cairo_t               * context = gdk_cairo_create (event->window);
      size_t                  iter;

      gdk_region_get_rectangles (event->region, &rectangles, &region.num_rectangles);
      region.rectangles = g_slice_alloc (sizeof (*region.rectangles) * region.num_rectangles);
      for (iter = 0; iter < region.num_rectangles; iter++)
        {
          region.rectangles[iter].x = rectangles[iter].x - widget->allocation.x;
          region.rectangles[iter].y = rectangles[iter].y - widget->allocation.y;
          region.rectangles[iter].width = rectangles[iter].width - widget->allocation.x;
          region.rectangles[iter].height = rectangles[iter].height - widget->allocation.y;
        }
      g_free (rectangles);

      cairo_save (context);

      gtk_mvc_view_paint (PRIV (widget)->view, context,
                          &area, &region);

      g_slice_free1 (sizeof (*region.rectangles) * region.num_rectangles, region.rectangles);

      cairo_restore (context);
      cairo_destroy (context);
    }

  return FALSE;
}

static void
unmap (GtkWidget* widget)
{
  gdk_window_hide (PRIV (widget)->event_window);

  GTK_WIDGET_CLASS (gtk_mvc_adaptor_parent_class)->unmap (widget);
}

static void
unrealize (GtkWidget* widget)
{
  gdk_window_destroy (PRIV (widget)->event_window);

  GTK_WIDGET_CLASS (gtk_mvc_adaptor_parent_class)->unrealize (widget);
}

static void
gtk_mvc_adaptor_class_init (GtkMvcAdaptorClass* self_class)
{
  GObjectClass* object_class   = G_OBJECT_CLASS (self_class);
  GtkWidgetClass* widget_class = GTK_WIDGET_CLASS (self_class);

  object_class->constructed  = constructed;
  object_class->dispose      = dispose;
  object_class->get_property = get_property;
  object_class->set_property = set_property;

  g_object_class_install_property (object_class, PROP_MODEL,
                                   g_param_spec_object ("model", NULL, NULL,
                                                        G_TYPE_OBJECT,
                                                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property (object_class, PROP_VIEW,
                                   g_param_spec_object ("view", NULL, NULL,
                                                        G_TYPE_OBJECT,
                                                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

  widget_class->button_press_event   = button_press_event;
  widget_class->button_release_event = button_release_event;
  widget_class->expose_event         = expose_event;
  widget_class->map                  = map;
  widget_class->realize              = realize;
  widget_class->size_allocate        = size_allocate;
  widget_class->size_request         = size_request;
  widget_class->unmap                = unmap;
  widget_class->unrealize            = unrealize;

  g_type_class_add_private (self_class, sizeof (GtkMvcAdaptorPrivate));
}

GtkWidget*
gtk_mvc_adaptor_new (GtkMvcView* view)
{
  return g_object_new (GTK_MVC_TYPE_ADAPTOR,
                       "view", view,
                       NULL);
}

GtkWidget*
gtk_mvc_adaptor_new_with_model (GtkMvcModel* model,
                                GtkMvcView * view)
{
  return g_object_new (GTK_MVC_TYPE_ADAPTOR,
                       "model", model,
                       "view", view,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
