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

#ifndef GDK_WINDOW_H
#define GDK_WINDOW_H

#include <gdk/gdk.h>

G_BEGIN_DECLS

GdkWindow* gfc_gdk_window_new (GdkWindow  * parent,
                               gchar const* first_attribute,
                               ...) G_GNUC_NULL_TERMINATED;

G_END_DECLS

#endif /* !GDK_WINDOW_H */

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
