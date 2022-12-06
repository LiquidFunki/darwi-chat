#ifndef USER_INFO_H
#define USER_INFO_H

#include "protocol.h"
#include "view_tools.h"
#include "libmx.h"
#include "resources.h"
#include "user_data_request.h"
#include "user_data.h"


void set_user_info_on_button(GtkWidget *button, t_current_window_info *current_window_info);
void menu_button_clicked(GtkWidget *widget, t_current_window_info *current_window_info);

#endif
