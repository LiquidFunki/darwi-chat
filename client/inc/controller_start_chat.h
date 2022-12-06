#ifndef CONTROLLER_START_CHAT_H
#define CONTROLLER_START_CHAT_H

#include "protocol.h"
#include "view_tools.h"
#include "libmx.h"
#include "resources.h"
#include "user_data.h"
#include "messages_requests.h"
#include "view_home_page.h"

void add_chat_clicked(GtkWidget *widget, t_current_window_info *current_window_info);
void set_add_chat_on_button(GtkWidget *button, t_current_window_info *current_window_info);
void add_chat(char *username, t_current_window_info *current_window_info);
void add_chats(char **username, t_current_window_info *current_window_info, int count);

#endif