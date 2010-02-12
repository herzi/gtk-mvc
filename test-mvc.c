/* This file is part of herzi's playground
 *
 * Copyright (C) 2010  Sven Herzberg
 *
 * This work is provided "as is"; redistribution and modification
 * in whole or in part, in any medium, physical or electronic is
 * permitted without restriction.
 *
 * This work is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * In no event shall the authors or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 */

#include "gtk-mvc.h"

static void
test_adaptor_constructor (void)
{
  GtkWidget* widget = gtk_mvc_adaptor_new ();
  g_object_ref_sink (widget);

  g_object_unref (widget);
}

static void
test_view_constructor (void)
{
  GtkWidget* widget = gtk_scroll_view_new ();
  g_object_ref_sink (widget);

  g_assert_cmpstr (G_OBJECT_TYPE_NAME (widget), ==, "GtkScrollView");

  g_object_unref (widget);
}

int
main (int   argc,
      char**argv)
{
  gtk_test_init (&argc, &argv, NULL);

  g_test_add_func ("/mvc-adaptor/constructor", test_adaptor_constructor);
  g_test_add_func ("/scroll/view/constructor", test_view_constructor);

  return g_test_run ();
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
