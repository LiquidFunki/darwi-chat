#include "choose_chat.h"

void upload_chats(char *from_user, t_current_window_info *current_window_info) {
    int user_chats_count = 0; 
    char **user_chats = get_all_user_chats(get_from_protocol_string(get_cookies(), "USERNAME"), &user_chats_count); 
    
    for(int chat_index = 0; chat_index < user_chats_count; chat_index++) {
        if(!strcmp(user_chats[chat_index], from_user)) {
            return;
        }
    }
    add_chat(from_user, current_window_info);
}

void upload_chats_on_add(char *from_user, t_current_window_info *current_window_info) {
    GList *children, *iter;
    GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "home_chats_grid"));


    children = gtk_container_get_children(GTK_CONTAINER(home_chats_grid));
    
    for(iter = children; iter != NULL; iter = g_list_next(iter)) {
        if(!strcmp(gtk_button_get_label(iter->data), from_user)) {
            return;
        }
    }
    add_chat(from_user, current_window_info);
}