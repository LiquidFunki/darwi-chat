#include "view_egypt.h"

static guint thread_id = 0;

static t_egypt_elements* egypt_element = NULL;

t_egypt_elements *get_egypt_element(){
    return egypt_element;
}

void view_egypt(t_current_window_info *current_layout_info)
{
    GtkCssProvider *cssProvider = gtk_css_provider_new(); 
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("egypt.css"), NULL); 
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                            GTK_STYLE_PROVIDER(cssProvider), 
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    GtkWidget *button[1000];

    char tmp[1024];
    int column = 0;
    t_egypt_elements *egypt_elements = create_egypt_elements();
    
    GtkLayout *sign_in_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "sign_in_layout"));
    if (current_layout_info->layout_exists)
        gtk_widget_destroy(GTK_WIDGET(sign_in_layout));
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("egypt.glade"), NULL);
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("quiz.glade"), NULL);
   
    egypt_elements->entry = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "type_message_entry"));

    GtkLayout *home_page_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "home_page_layout"));
    GtkWidget *home_page_fixed = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_page_fixed"));
    GtkWidget *home_chats_viewport = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_viewport"));
    GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_grid"));

    GtkWidget *home_chats_scrolled_window = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_scrolled_window")); 
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(home_chats_scrolled_window), GTK_POLICY_NEVER, GTK_POLICY_NEVER);
    ////

    GtkWidget *profile_info_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "profile_info_button"));
    GtkWidget *profile_info_icon_img = gtk_image_new_from_file("./client/resources/static/images/eg_profile_info_icon.png");
    gtk_button_set_image(GTK_BUTTON(profile_info_button), profile_info_icon_img);

    GtkWidget *quiz_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "quiz_button"));
    GtkWidget *quiz_icon_img = gtk_image_new_from_file("./client/resources/static/images/eg_quiz_icon.png");
    gtk_button_set_image(GTK_BUTTON(quiz_button), quiz_icon_img);
    // GtkWidget *menu_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "menu_button"));

    GtkWidget *shop_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "shop_button"));
    GtkWidget *shop_icon_img = gtk_image_new_from_file("./client/resources/static/images/eg_shop_icon.png");
    gtk_button_set_image(GTK_BUTTON(shop_button), shop_icon_img);

    GtkWidget *settings_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "settings_button"));
    GtkWidget *settings_icon_img = gtk_image_new_from_file("./client/resources/static/images/eg_settings_icon.png");
    gtk_button_set_image(GTK_BUTTON(settings_button), settings_icon_img);

    GtkWidget *add_chat_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "add_chat_button"));
   
    GtkWidget *buttons_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "choose_word_2era_grid"));
    GtkWidget *button_refresh_words = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button_refresh_words"));
    egypt_elements->buttons[0] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button1_1"));
    egypt_elements->buttons[1] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button1_2"));
    egypt_elements->buttons[2] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button1_3"));
    egypt_elements->buttons[3] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button1_4"));
    egypt_elements->buttons[4] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button1_5"));
    egypt_elements->buttons[5] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button2_1"));
    egypt_elements->buttons[6] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button2_2"));
    egypt_elements->buttons[7] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button2_3"));
    egypt_elements->buttons[8] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button2_4"));
    egypt_elements->buttons[9] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button2_5"));

    GtkWidget *user_avatar = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "profile_photo"));
    t_model_resource *avatar_resource = send_get_avatar_request(get_from_protocol_string(get_cookies(), "USERNAME" ));
    GdkPixbuf *image_pixbuf = gdk_pixbuf_new_from_file_at_size(request_file_if_not_exist(avatar_resource->path), 80, 80, NULL);
	gtk_image_set_from_pixbuf(GTK_IMAGE(user_avatar), image_pixbuf);
    GtkWidget *user_name_lable = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "user_name"));
    gtk_label_set_text(GTK_LABEL(user_name_lable), get_from_protocol_string(get_cookies(), "USERNAME" ));

    set_quiz_on_button(quiz_button);

    set_add_chat_on_button(GTK_WIDGET(add_chat_button), current_layout_info);

    view_chat_window(current_layout_info);
  
    int user_chats_count = 0; 
    char **user_chats = get_all_user_chats(get_from_protocol_string(get_cookies(), "USERNAME"), &user_chats_count); 

    add_chats(user_chats, current_layout_info, user_chats_count);

    for(int i = 0; i < user_chats_count;i++){ 
        printf("USER CHATS: %s\n\n", user_chats[i]); 
    }
   
    set_user_info_on_button(profile_info_button, current_layout_info);
    set_setting_on_button(settings_button, current_layout_info);
    set_shop_on_button(shop_button, current_layout_info);

   

    current_layout_info->layout_exists = true;
    
    FILE* words_file = fopen("./client/resources/second_era_words", "r");

    if (words_file == NULL) printf("Words file not found\n");

    char* buffer = mx_strnew(1024);

    int buf_size = fread(buffer, sizeof(char), 1024, words_file);

    egypt_elements->words = mx_strsplit(buffer, '\n');

    if(!egypt_elements->words)
        egypt_elements->words = get_words_from_file("./client/resources/second_era_words");
       
    count_words(egypt_elements);
    set_words_on_buttons(egypt_elements);
    
    g_signal_connect(button_refresh_words, "clicked", G_CALLBACK(refresh_words), egypt_elements);

    g_signal_connect(egypt_elements->buttons[0], "clicked", G_CALLBACK(add_word_to_message), egypt_elements);
    g_signal_connect(egypt_elements->buttons[1], "clicked", G_CALLBACK(add_word_to_message), egypt_elements);
    g_signal_connect(egypt_elements->buttons[2], "clicked", G_CALLBACK(add_word_to_message), egypt_elements);
    g_signal_connect(egypt_elements->buttons[3], "clicked", G_CALLBACK(add_word_to_message), egypt_elements);
    g_signal_connect(egypt_elements->buttons[4], "clicked", G_CALLBACK(add_word_to_message), egypt_elements);
    g_signal_connect(egypt_elements->buttons[5], "clicked", G_CALLBACK(add_word_to_message), egypt_elements);
    g_signal_connect(egypt_elements->buttons[6], "clicked", G_CALLBACK(add_word_to_message), egypt_elements);
    g_signal_connect(egypt_elements->buttons[7], "clicked", G_CALLBACK(add_word_to_message), egypt_elements);
    g_signal_connect(egypt_elements->buttons[8], "clicked", G_CALLBACK(add_word_to_message), egypt_elements);
    g_signal_connect(egypt_elements->buttons[9], "clicked", G_CALLBACK(add_word_to_message), egypt_elements);
    gtk_container_add(GTK_CONTAINER(current_layout_info->main_window), GTK_WIDGET(home_page_layout));

    gtk_widget_show_all(home_page_layout);

    pthread_t new_messages_thread;
    pthread_create(&new_messages_thread, NULL, check_new_messages, current_layout_info);
    set_new_messages_thread(&new_messages_thread);
}

void set_words_on_buttons(t_egypt_elements *egypt_elements) {
    for (int i = egypt_elements->page * 10 - 10, ind = 0; ind < 10; i++, ind++) {
        if (!egypt_elements->words[i])
            i = 0;
        printf("THERE %s\n\n", egypt_elements->words[i]);
        gtk_button_set_label(GTK_BUTTON(egypt_elements->buttons[ind]), egypt_elements->words[i]);
    }
}

void refresh_words(GtkWidget *widget, t_egypt_elements *egypt_elements) {
    if (egypt_elements->page < egypt_elements->word_count / 10 + 1)
        egypt_elements->page++;
    else
        egypt_elements->page = 1;
    
    set_words_on_buttons(egypt_elements);
}

char **get_words_from_file(char *file_name) {
    char *file = mx_file_to_str(file_name);    
    char **words_arr = mx_strsplit(file, '\n');


    return words_arr;
}

t_egypt_elements *create_egypt_elements() {
    t_egypt_elements *egypt_elements = (t_egypt_elements *)malloc(sizeof(t_egypt_elements));
    egypt_elements->buttons = (GtkWidget **)(malloc(sizeof(GtkWidget *) * 10));
    egypt_elements->words = NULL;
    egypt_elements->page = 1;
    egypt_elements->message = NULL;
    egypt_elements->word_count = 0;
    egypt_elements->entry = NULL;

    return egypt_elements; 
}

void add_word_to_message(GtkWidget *widget, t_egypt_elements *egypt_elements) {
    char *word = (char*)gtk_button_get_label(GTK_BUTTON(widget));

    char* buff = NULL;
    if(egypt_elements->message) {
        if((strlen(egypt_elements->message)) <= 140) {

            if (egypt_elements->message) {
                buff = egypt_elements->message;
                egypt_elements->message = mx_strjoin(egypt_elements->message, " ");
                free(buff);
            }

            buff = egypt_elements->message;
            egypt_elements->message = mx_strjoin(egypt_elements->message, word);
         
            if (buff) 
                free(buff);
                gtk_entry_set_text(GTK_ENTRY(egypt_elements->entry), egypt_elements->message);
        }
    } else {

        buff = egypt_elements->message;
        egypt_elements->message = mx_strjoin(egypt_elements->message, word);

            if (buff) 
                free(buff);
            
        gtk_entry_set_text(GTK_ENTRY(egypt_elements->entry), egypt_elements->message);
    }
    egypt_element = egypt_elements;
    printf("%s\n", egypt_elements->message);
}

void count_words(t_egypt_elements *egypt_elements) {
   int word_count = 0;
    for (int i = 0; egypt_elements->words[i]; i++){
        word_count++;
    }

    egypt_elements->word_count = word_count;
}

void clear_egypt_elements(t_egypt_elements *egypt_elements) {
    free(egypt_elements->message);

    for (int i = 0; i < egypt_elements->word_count; i++)
        free(egypt_elements->words[i]);
    free(egypt_elements->words);
}
