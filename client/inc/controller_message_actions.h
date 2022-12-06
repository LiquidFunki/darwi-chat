#ifndef CONTROLLER_MESSAGE_ACTIONS
#define CONTROLLER_MESSAGE_ACTIONS

#include <gtk/gtk.h>
#include "model_message.h"
#include "model_resource.h"
#include "model_stone.h"
#include "database_client.h"
#include "controller_start_chat.h"

void callback_click_message(GtkWidget *b, GdkEventButton *event,  t_model_message* model_message);
void set_selected_message(long id);
long get_selected_message();
void forward_clicked(GtkWidget *widget, t_current_window_info *current_window_info);
void add_chats_for_forward(char **username, t_current_window_info *current_window_info, int count);
void set_static_current_window_info(t_current_window_info* current_window_info);

#endif
