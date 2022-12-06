#ifndef VIEW_HOME_PAGE_H
#define VIEW_HOME_PAGE_H

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
#include "choose_chat.h"



void view_home_page(t_current_window_info *current_layout_info);
int get_current_chat_count();

gboolean callback_update_messages(gpointer* user_data);



char *request_file_if_not_exist(char *file);
bool is_client_file(char *path);
#endif