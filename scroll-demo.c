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

#include <gtk/gtk.h>
#include "gtk-mvc.h"

#include <glib/gi18n.h>

int
main (int   argc,
      char**argv)
{
  GtkWidget* box;
  GtkWidget* scroll;
  GtkWidget* viewport;
  GtkWidget* window;

  gtk_init (&argc, &argv);

  box      = gtk_hbox_new (FALSE, 0);
  scroll   = gtk_mvc_adaptor_new (gtk_mvc_scroll_view_new ());
  window   = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  viewport = gtk_viewport_new (NULL, NULL);

  g_object_add_weak_pointer (G_OBJECT (window), (gpointer*)&window);
  g_signal_connect (window, "destroy",
                    G_CALLBACK (gtk_main_quit), NULL);
  gtk_window_set_title (GTK_WINDOW (window), _("MVC based Scroll Container"));
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 300);

  gtk_container_add (GTK_CONTAINER (box), viewport);
  gtk_box_pack_start (GTK_BOX (box), scroll,
                      FALSE, FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), box);

  gtk_widget_show_all (window);
  gtk_main ();

  if (window)
    {
      gtk_widget_destroy (window);
    }

  return 0;
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
