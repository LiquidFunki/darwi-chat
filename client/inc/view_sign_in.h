#ifndef VIEW_SIGN_IN_H
#define VIEW_SIGN_IN_H

#include <gtk/gtk.h>
#include "libmx.h"
#include "controller_sign_in.h"
#include "view_sign_up.h"
#include "view_home_page.h"
#include "view_tools.h"
#include "resources.h"
#include "encrypt.h"

// void view_sign_in(GtkWidget* window);

G_MODULE_EXPORT void sign_up_clicked(GtkButton* button, t_current_window_info *current_layout_info);
void view_sign_in(t_current_window_info *current_layout_info);
G_MODULE_EXPORT void sign_in_clicked(GtkButton* button, t_current_window_info *current_layout_info);



#endif
