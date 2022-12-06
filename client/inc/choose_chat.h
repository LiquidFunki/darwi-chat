#ifndef CHOOSE_CHAT_H
#define CHOOSE_CHAT_H

#include <gtk/gtk.h>
#include "libmx.h"
#include "view_sign_in.h"
#include "drawing_area.h"
#include "view_tools.h"
#include "quiz.h"
#include "user_info.h"
#include "resources.h"
#include "view_chat_window.h"
#include "controller_start_chat.h"
#include "controller_get_messages.h"
#include "get_resources_request.h"
#include "user_data_request.h"
#include "controller_message_actions.h"

void set_chat_is_chosen(GtkWidget *user_chat_button, t_current_window_info *current_window_info);
void set_chat_new_message(char* from_user, t_current_window_info *current_window_info);

void upload_chats_on_add(char *from_user, t_current_window_info *current_window_info);
void upload_chats(char *from_user, t_current_window_info *current_window_info);
void	choose_chat(GtkButton *b, t_current_window_info *current_window_info);

#endif