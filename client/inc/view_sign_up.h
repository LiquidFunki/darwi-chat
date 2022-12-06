#ifndef VIEW_SIGN_UP_H
#define VIEW_SIGN_UP_H

#include <gtk/gtk.h>
#include "libmx.h"
#include "controller_sign_up.h"
#include "view_tools.h"
#include "view_sign_in.h"
#include "encrypt.h"

void view_sign_up(t_current_window_info *current_layout);
G_MODULE_EXPORT void sign_up_insert_clicked(GtkButton* button,  t_current_window_info *current_layout);
G_MODULE_EXPORT void return_clicked(GtkButton* button, t_current_window_info *current_layout);

// void view_sign_up(GtkWidget* window);

#endif
