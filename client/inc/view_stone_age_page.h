#ifndef VIEW_STONE_AGE_PAGE_H
#define VIEW_STONE_AGE_PAGE_H

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
#include "view_home_page.h"
#include "choose_chat.h"




void view_stone_age_page(t_current_window_info *current_layout_info);
// void	choose_chat(GtkButton *b, t_current_window_info *current_window_info) ;
// int get_current_chat_count();



// char *request_file_if_not_exist(char *file);
// bool is_client_file(char *path);

#endif