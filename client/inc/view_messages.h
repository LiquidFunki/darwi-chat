#ifndef VIEW_MESSAGES_H
#define VIEW_MESSAGES_H

#include <gtk/gtk.h>
#include "libmx.h"
#include "view_sign_in.h"
#include "database_client.h"
#include "drawing_area.h"
#include "view_tools.h"
#include "model_message.h"
#include "quiz.h"
#include "resources.h"
#include "controller_message_actions.h"
#include "view_egypt.h"

void view_messages(t_model_message **model_message, t_current_window_info *current_layout_info, int size);
 
void view_message(t_model_message *model_message, t_current_window_info *current_layout_info);

void view_file(t_model_message *model_message, t_current_window_info *current_layout_info);

void view_stone(t_model_message *model_message, t_current_window_info *current_layout_info);

void send_message_button_clicked(GtkWidget *widget, t_current_window_info *current_window_info);

void send_file_as_message(GtkWidget *widget, t_current_window_info * current_window_info);

void set_current_user_to_talk(char *new_user_to_talk);
char *get_current_user_to_talk(void);

void* check_new_messages(t_current_window_info* window_info);

#endif
