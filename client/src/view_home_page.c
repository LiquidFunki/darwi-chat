#include "view_home_page.h"
#include "pthread.h"


static guint thread_id = 0;


gboolean callback_update_messages(gpointer* user_data) {

    t_current_window_info *current_window_info = (t_current_window_info*)user_data;
    int count = 0;
    t_model_message** messages = controller_get_new_messages(&count);
    // g_source_remove(thread_id);
    if (count != 0) {
        // view_messages(messages, current_window_info, count);
        for (int i = 0; i < count; i++) {
            if(!strcmp(messages[i]->from_user, get_current_user_to_talk()))
                view_message(messages[i], current_window_info);
            free_model_message(&(messages[i]));
        }
        mx_printstr("\a");
        fflush(stdout);
        free(messages);
    }

    // thread_id = g_timeout_add(10000, callback_update_messages, current_window_info);
    // thread_id =g_timeout_add_seconds(10, callback_update_messages, current_window_info);

    return TRUE;
}


    


void view_home_page(t_current_window_info *current_layout_info)
{
    GtkWidget *button[1000];

    char tmp[1024];
    int column = 0;
    
    GtkLayout *sign_in_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "sign_in_layout"));
    if (current_layout_info->layout_exists)
    {
        gtk_widget_destroy(GTK_WIDGET(sign_in_layout));
    }
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("home_page.glade"), NULL);
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("quiz.glade"), NULL);

    GtkLayout *home_page_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "home_page_layout"));

    GtkWidget *home_page_fixed = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_page_fixed"));

    GtkWidget *home_chats_viewport = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_viewport"));

    GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_grid"));

    GtkWidget *quiz_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "quiz_button"));

    GtkWidget *add_chat_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "add_chat_button"));

    GtkWidget *menu_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "menu_button"));

    set_quiz_on_button(quiz_button);
    
    set_add_chat_on_button(GTK_WIDGET(add_chat_button), current_layout_info);

    view_chat_window(current_layout_info);
    
    int user_chats_count = 0; 
    char **user_chats = get_all_user_chats(get_from_protocol_string(get_cookies(), "USERNAME"), &user_chats_count); 

    add_chats(user_chats, current_layout_info, user_chats_count);

    for(int i = 0; i < user_chats_count;i++){ 
        printf("USER CHATS: %s\n\n", user_chats[i]); 
    }

    // TODO: add era checker;
    // add_draw_area(current_layout_info);
 
    set_user_info_on_button(menu_button, current_layout_info);


    gtk_container_add(GTK_CONTAINER(current_layout_info->main_window), GTK_WIDGET(home_page_layout));
    current_layout_info->layout_exists = true;

    FILE *f1 = fopen("functions.txt", "r");

	if (f1 == NULL ) {
		printf("File functions.txt not found\n");
		// return EXIT_FAILURE;
		}
    // g_signal_connect(draw_button, "clicked", G_CALLBACK(add_drawing_area_clicked), current_layout_info);
	column = 0;

        gtk_widget_show_all(GTK_WIDGET(home_page_layout));
    // thread_id = g_timeout_add_seconds(10, callback_update_messages, current_layout_info);
    pthread_t new_messages_thread;
    pthread_create(&new_messages_thread, NULL, check_new_messages, current_layout_info);

}

char *request_file_if_not_exist(char *file) {
    char *path = mx_replace_substr(file, "./server", "./client");
    if(is_client_file(path)) {
        return path;
    } else {
        char *server_path = mx_replace_substr(file, "./server", "");
        get_file(server_path);
        return path;
    }
}

bool is_client_file(char *path) {
    FILE *file;
    if(!(file = fopen(path, "r"))) {
        return 0;
    } else {
        fclose(file);
        return 1;
    }
}
