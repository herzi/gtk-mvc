/* This file is part of herzi's playground
 *
 * AUTHORS
 *     Sven Herzberg
 *
 * Copyright (C) 2009  Sven Herzberg
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

#include "gdk-window.h"

#include <string.h> /* for memset() */

GdkWindow*
gfc_gdk_window_new (GdkWindow  * parent,
                    gchar const* first_attribute,
                    ...)
{
  GdkWindowAttr  attributes;
  gchar const  * attribute;
  GdkWindow    * result = NULL;
  va_list        argv;
  gint           valid_attributes;

  /* FIXME: we could also hardcode this */
  memset (&attributes, '\0', sizeof (&attributes));
  valid_attributes = 0;

  /* defaults for required attributes */
  attributes.width = 1;
  attributes.height = 1;
  attributes.event_mask = 0;
  attributes.wclass = GDK_INPUT_OUTPUT;
  attributes.window_type = gdk_window_get_window_type (parent) == GDK_WINDOW_ROOT ?
                           GDK_WINDOW_TOPLEVEL : GDK_WINDOW_CHILD;

  va_start (argv, first_attribute);
  for (attribute = first_attribute; attribute; attribute = va_arg (argv, gchar const*))
    {
      if (!strcmp (attribute, "class"))
        {
          attributes.wclass = va_arg (argv, GdkWindowClass);
        }
      else if (!strcmp (attribute, "colormap"))
        {
          attributes.colormap = va_arg (argv, GdkColormap*);
          valid_attributes |= GDK_WA_COLORMAP;
        }
      else if (!strcmp (attribute, "cursor"))
        {
          attributes.cursor = va_arg (argv, GdkCursor*);
          valid_attributes |= GDK_WA_CURSOR;
        }
      else if (!strcmp (attribute, "event-mask"))
        {
          attributes.event_mask = va_arg (argv, gint);
        }
      else if (!strcmp (attribute, "height"))
        {
          attributes.height = va_arg (argv, gint);
        }
      else if (!strcmp (attribute, "override-redirect"))
        {
          attributes.override_redirect = va_arg (argv, gboolean);
          valid_attributes |= GDK_WA_NOREDIR;
        }
      else if (!strcmp (attribute, "title"))
        {
          attributes.title = va_arg (argv, gchar*);
          valid_attributes |= GDK_WA_TITLE;
        }
      else if (!strcmp (attribute, "type"))
        {
          attributes.window_type = va_arg (argv, GdkWindowType);
        }
      else if (!strcmp (attribute, "type-hint"))
        {
          attributes.type_hint = va_arg (argv, GdkWindowTypeHint);
        }
      else if (!strcmp (attribute, "visual"))
        {
          attributes.visual = va_arg (argv, GdkVisual*);
          valid_attributes |= GDK_WA_VISUAL;
        }
      else if (!strcmp (attribute, "width"))
        {
          attributes.width = va_arg (argv, gint);
        }
      else if (!strcmp (attribute, "wmclass-class"))
        {
          attributes.wmclass_class = va_arg (argv, gchar*);
          valid_attributes |= GDK_WA_WMCLASS;
        }
      else if (!strcmp (attribute, "wmclass-name"))
        {
          attributes.wmclass_name = va_arg (argv, gchar*);
          valid_attributes |= GDK_WA_WMCLASS;
        }
      else if (!strcmp (attribute, "x"))
        {
          attributes.x = va_arg (argv, int);
          valid_attributes |= GDK_WA_X;
        }
      else if (!strcmp (attribute, "y"))
        {
          attributes.y = va_arg (argv, int);
          valid_attributes |= GDK_WA_Y;
        }
      else
        {
          g_warning ("unknown attribute \"%s\"; did you terminate the argument list with NULL?",
                     attribute);
        }
    }
  va_end (argv);

  if ((valid_attributes & (GDK_WA_VISUAL | GDK_WA_COLORMAP)) == 0)
    {
      valid_attributes |= GDK_WA_COLORMAP;
      attributes.colormap = gdk_drawable_get_colormap (parent);
    }

  result = gdk_window_new (parent,
                           &attributes,
                           valid_attributes);

  return result;
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
