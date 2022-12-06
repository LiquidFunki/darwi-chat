#include "controller_start_chat.h"

static int current_chat_count = 0;

int get_current_chat_count() {
    return current_chat_count;
}

void add_chat_clicked(GtkWidget *widget, t_current_window_info *current_window_info) {
    
    GtkWidget *add_chat_entry = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "add_chat_entry"));

    char *user_to_find = (char*)gtk_entry_get_text(GTK_ENTRY(add_chat_entry));
   

    if(user_to_find && strlen(user_to_find) > 0) {
        if(send_start_chat_request(user_to_find)) {
            upload_chats_on_add(user_to_find, current_window_info);
            gtk_widget_show_all(current_window_info->main_window);
        } else {
            NULL;
        }
    }
    gtk_entry_set_text(GTK_ENTRY(add_chat_entry), "");

}

void set_add_chat_on_button(GtkWidget *button, t_current_window_info *current_window_info) {

    // int questions_number = set_quiz_from_file(&quiz_questions, "quiz");

    // printf("%s\n", cJSON_Print(quiz_questions));

    // gtk_button_set_image (GTK_BUTTON (button), gtk_image_new_from_icon_name ("open-menu-symbolic", GTK_ICON_SIZE_BUTTON));
    GtkCssProvider *cssProvider = gtk_css_provider_new(); 
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("add_chat.css"), NULL); 
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                            GTK_STYLE_PROVIDER(cssProvider), 
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
    GtkWidget *add_chat_popover;

    gtk_builder_add_from_file(current_window_info->builder, get_path_to_glade("add_chat.glade"), NULL);


	GtkWidget *add_chat_layout = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "add_chat_layout"));
    
    GtkWidget *add_chat = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "add_chat"));

    add_chat_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (add_chat_popover), add_chat_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), add_chat_popover);

    g_signal_connect (G_OBJECT (add_chat), "clicked", G_CALLBACK (add_chat_clicked), current_window_info);
}

void add_chats(char **username, t_current_window_info *current_window_info, int count) {
    for(int chat_index = 0; chat_index < count; chat_index++) {
        add_chat(username[chat_index], current_window_info);
    }
}


void add_chat(char *username, t_current_window_info *current_window_info) {
    gtk_builder_add_from_file(current_window_info->builder, get_path_to_glade("user_chat_button.glade"), NULL);
    

    // gtk_builder_add_from_file(current_window_info->builder, get_path_to_glade("home_page.glade"), NULL);

    GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "person_chat_button"));
    // GtkWidget *button;
    GtkWidget *image = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "user_image"));

    GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "home_chats_grid"));

    t_model_resource *avatar = send_get_avatar_request(username);

    insert_data_resource(avatar);

    GdkPixbuf *image_pixbuf = gdk_pixbuf_new_from_file_at_size(request_file_if_not_exist(avatar->path), 80, 80, NULL);

    gtk_grid_insert_column (GTK_GRID(home_chats_grid), get_current_chat_count());

    // gtk_grid_attach (GTK_GRID(home_chats_grid), button, get_current_chat_count(), 1, 1, 1);

    	// gtk_grid_insert_column (GTK_GRID(home_chats_grid), get_current_chat_count());

		// button = gtk_button_new_with_label (username);
        gtk_button_set_label(GTK_BUTTON(button), username);

	    gtk_image_set_from_pixbuf(GTK_IMAGE(image), image_pixbuf);
        
        

		// gtk_button_set_alignment (GTK_BUTTON(button), 0.5, 0.0); // hor left, ver center
        gtk_widget_set_size_request(button, 100, 100);
		// gtk_grid_attach (GTK_GRID(home_chats_grid), button, get_current_chat_count(), 1, 1, 1);
        GList* children = gtk_container_get_children(GTK_CONTAINER(home_chats_grid));
        if(children)
            gtk_grid_attach_next_to(GTK_GRID(home_chats_grid), button, children->data, GTK_POS_LEFT, 100, 100);
        else
    		gtk_grid_attach (GTK_GRID(home_chats_grid), button, get_current_chat_count(), 1, 1, 1);

        
		g_signal_connect(button, "clicked", G_CALLBACK(choose_chat), current_window_info);

    current_chat_count++;
    
}
