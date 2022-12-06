#include "view_chat_window.h"



void view_chat_window(t_current_window_info *current_layout_info)
{

    // add css for  messages

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("messages.css"), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    int count = 0;
    
    char tmp[1024];
    int row = 0;

    GtkLayout *sign_in_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "sign_in_layout"));
    if (current_layout_info->layout_exists)
    {
        gtk_widget_destroy(GTK_WIDGET(sign_in_layout));
    }
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("chat_window.glade"), NULL); ///////rename --> done

    GtkWidget *gtk_scrolled_window = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_scrolled"));

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(gtk_scrolled_window), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

    GtkLayout *home_page_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "home_page_layout"));

    GtkWidget *send_message_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "send_message_button"));

    g_signal_connect(send_message_button, "clicked", G_CALLBACK(send_message_button_clicked), current_layout_info);
    
    GtkWidget *file_chooser_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "gtkfile_chooser_button"));  
 
    // g_signal_connect(file_chooser_button, "file-set", G_CALLBACK(send_file_as_message), current_layout_info);
    
    GtkLayout *chat_window_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "chat_window_layout")); /// rename --> done

    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_grid"));

    GtkWidget *home_chats_scrolled_window = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_scrolled_window")); 

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(home_chats_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);

    current_layout_info->layout_exists = true;

    row = 0;
    gtk_grid_insert_column(GTK_GRID(chat_window_grid), 0);
    gtk_grid_insert_column(GTK_GRID(chat_window_grid), 1);

    current_layout_info->message_position_y = count + 20;
    
    gtk_widget_show_all(current_layout_info->main_window);
    
}



