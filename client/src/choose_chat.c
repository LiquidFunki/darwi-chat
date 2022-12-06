#include "choose_chat.h"

void set_chat_is_chosen(GtkWidget *user_chat_button, t_current_window_info *current_window_info) {
    GList *children, *iter;
    GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "home_chats_grid"));

    children = gtk_container_get_children(GTK_CONTAINER(home_chats_grid));
    
    for(iter = children; iter != NULL; iter = g_list_next(iter)) {
        GtkStyleContext *user_button_context = gtk_widget_get_style_context(GTK_WIDGET(iter->data));
        gtk_style_context_remove_class(user_button_context, "user_button_chosen");
        gtk_style_context_remove_class(user_button_context, "user_button_new_message");

        gtk_style_context_add_class(user_button_context, "user_button");
    }

    GtkStyleContext *user_button_context = gtk_widget_get_style_context(GTK_WIDGET(user_chat_button));
    gtk_style_context_remove_class(user_button_context, "user_button");
    gtk_style_context_add_class(user_button_context, "user_button_chosen");
}

void set_chat_new_message(char* from_user, t_current_window_info *current_window_info) {
    GList *children, *iter;
    GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "home_chats_grid"));

    children = gtk_container_get_children(GTK_CONTAINER(home_chats_grid));
    
    for(iter = children; iter != NULL; iter = g_list_next(iter)) {
        if(!strcmp(from_user, gtk_button_get_label(iter->data))) {
            GtkStyleContext *user_button_context = gtk_widget_get_style_context(GTK_WIDGET(iter->data));
            gtk_style_context_remove_class(user_button_context, "user_button");
            gtk_style_context_add_class(user_button_context, "user_button_new_message");
        }
    }
}
void choose_chat(GtkButton *b, t_current_window_info *current_window_info) {
    set_chat_is_chosen(b, current_window_info);
    printf("You selected: %s\n", gtk_button_get_label (b));

    set_in_protocol_string(get_cookies(), "TO USER", gtk_button_get_label(b));

    int count = 0;
    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "chat_window_grid"));


    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(chat_window_grid));
    
    for(iter = children; iter != NULL; iter = g_list_next(iter))
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    
    g_list_free(children);


    t_model_user_data *current_user_date = send_user_data_request(get_from_protocol_string(get_cookies(), "USERNAME"));

    t_model_user_data *other_user_data = send_user_data_request(gtk_button_get_label (b));

    set_current_user_to_talk((char*)gtk_button_get_label (b)); //TODO:

    // TODO: uncomment this for stones
    if(other_user_data->era == STONE_AGE || current_user_date == STONE_AGE){ 
        t_model_message *model_message = get_stone_message_from_chat((char*)gtk_button_get_label (b), &count);
        add_draw_area(current_window_info, model_message);
        printf("\n\n THERE STONE ERA\n\n");

    } else {
        t_model_message **model_message = get_all_messages_from_chat((char*)gtk_button_get_label (b), &count);
        for (int i = 0; i < 20; i++)
        {
            GtkBuilder *message_builder = gtk_builder_new_from_file(get_path_to_glade("message_labels.glade"));
            gtk_grid_insert_row(GTK_GRID(chat_window_grid), i);
            gtk_grid_attach(GTK_GRID(chat_window_grid), GTK_WIDGET(gtk_builder_get_object(message_builder, "invisible_label")), 1, i, 1, 1);
        }
        current_window_info->message_position_y = count + 20;

        view_messages(model_message, current_window_info, count);
    }
    set_static_current_window_info(current_window_info);


}

