#include "view_messages.h"


char *get_current_user_to_talk(void) {
    return get_from_protocol_string(get_cookies(), "TO USER");
}

void set_current_user_to_talk(char *new_user_to_talk) {
    
    if(get_from_protocol_string(get_cookies(), "TO USER")) {
        set_in_protocol_string(get_cookies(), "TO USER", new_user_to_talk);
    } else {
        add_to_protocol_string(get_cookies(), "TO USER", new_user_to_talk);
    }
    
}


void view_messages(t_model_message **model_message, t_current_window_info *current_layout_info, int size) 
{ 
    GtkWidget *label[size]; 
    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_grid")); 
 
    for (int message_id = 0; message_id < size; message_id++) 
    { 
        if(model_message[message_id]->data_type == MESSAGE_TEXT){
            view_message(model_message[message_id], current_layout_info); 
        } else if (model_message[message_id]->data_type == MESSAGE_FILE) {
            view_file(model_message[message_id], current_layout_info);
        }  
    } 
 
} 
 
void view_message(t_model_message *model_message, t_current_window_info *current_layout_info) 
{ 
    GtkWidget *label; 
    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_grid")); 
 
    int current_id = current_layout_info->message_position_y + 1; 
 
    GtkBuilder *message_builder = gtk_builder_new_from_file(get_path_to_glade("message_labels.glade")); 
 
    gtk_grid_insert_row(GTK_GRID(chat_window_grid), current_id); 

    GtkWidget* box = gtk_event_box_new();
    if (!strcmp(model_message->from_user, get_from_protocol_string(get_cookies(), "USERNAME"))) { 
 
        label = GTK_WIDGET(gtk_builder_get_object(message_builder, "current_user_msg_label")); 
        gtk_label_set_text(GTK_LABEL(label), model_message->data);

        gtk_container_add(GTK_CONTAINER(box), label);
         if(strlen(model_message->forward_from) > 0) {
            GtkWidget *forward_label = GTK_WIDGET(gtk_builder_get_object(message_builder, "current_forward_label")); 
            gtk_label_set_text(forward_label, mx_strjoin("From: ",model_message->forward_from));
            gtk_grid_attach(GTK_GRID(chat_window_grid), forward_label, 1, current_id, 1, 1); 
            current_id++;
        }
        gtk_grid_attach(GTK_GRID(chat_window_grid), box, 1, current_id, 1, 1); 

        gtk_widget_show (box);
    } else { 
 
        label = GTK_WIDGET(gtk_builder_get_object(message_builder, "other_user_msg_label")); 
        gtk_label_set_text(GTK_LABEL(label), model_message->data); 

        gtk_container_add(GTK_CONTAINER(box), label);

        if(strlen(model_message->forward_from) > 0) {
            GtkWidget *forward_label = GTK_WIDGET(gtk_builder_get_object(message_builder, "other_forward_label")); 
            gtk_label_set_text(forward_label, mx_strjoin("From: ",model_message->forward_from));
            gtk_grid_attach(GTK_GRID(chat_window_grid), forward_label, 0, current_id, 1, 1); 
            current_id++;
        }
        gtk_grid_attach(GTK_GRID(chat_window_grid), box, 0, current_id, 1, 1); 

        gtk_widget_show (box);

    } 

    g_signal_connect(box, "button_press_event", callback_click_message, model_message);
 
    current_layout_info->message_position_y = current_id; 
 
    GtkWidget *chat_viewport = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_viewport")); 
     
    GtkAdjustment *adjustment = gtk_viewport_get_vadjustment(GTK_VIEWPORT(chat_viewport)); 
    gtk_adjustment_set_upper(adjustment, gtk_adjustment_get_upper(adjustment) + 500); 
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment)); 
}

char* get_file_name(char* full_name) {

    int len = strlen(full_name) - 1;


    for (; len >= 0; len--) {

        if (full_name[len] == '/') {
            len++;
            break;
        } 
    }

    char*  name = full_name + len;
    name = strdup(name);

    fprintf(stdout ,"name: %s\n", name);


    return name;
}

void view_file(t_model_message *model_message, t_current_window_info *current_layout_info){
    GtkWidget *image;
    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_grid")); 

    int current_id = current_layout_info->message_position_y + 1; 
    GtkBuilder *message_builder = gtk_builder_new_from_file(get_path_to_glade("message_image.glade")); 
    GtkBuilder *forward_builder = gtk_builder_new_from_file(get_path_to_glade("message_labels.glade")); 
    

    gtk_grid_insert_row(GTK_GRID(chat_window_grid), current_id); 

    GtkWidget* box = gtk_event_box_new();

    t_model_resource *msg_resource = get_resource_by_id(model_message->data);
    char * real_path = request_file_if_not_exist(msg_resource->path);
    GdkPixbuf *image_pixbuf = gdk_pixbuf_new_from_file_at_size(real_path, 100, 100, NULL);

    gchar* message_about = message_about;

    if (model_message->data_type == MESSAGE_FILE) {
        t_model_resource* resource = get_resource_by_id(model_message->data);
        char* name = get_file_name(resource->name);
        message_about = g_strjoin(" ", "File:", name, " ", NULL);
        free(name);
        free_model_resource(&resource);
    }

    GtkWidget* forward_label = NULL;

    if(!strcmp(model_message->from_user, get_from_protocol_string(get_cookies(), "USERNAME"))){
        image = GTK_WIDGET(gtk_builder_get_object(message_builder, "current_user_msg_image"));

        if (image_pixbuf) {
            gtk_image_set_from_pixbuf(GTK_IMAGE(image), image_pixbuf);
        } else {
            image_pixbuf = gdk_pixbuf_new_from_file_at_size(get_path_to_image("click.png"), 100, 100, NULL);
            gtk_image_set_from_pixbuf(GTK_IMAGE(image), image_pixbuf);
        }
        gtk_container_add(GTK_CONTAINER(box), image);

        if(strlen(model_message->forward_from) > 0) {
            forward_label = GTK_WIDGET(gtk_builder_get_object(forward_builder, "current_forward_label")); 
            // gtk_label_set_text(forward_label, mx_strjoin("From: ",model_message->forward_from));
            
            gchar* buff = message_about;
            message_about = g_strjoin(" ", message_about, "From:", model_message->forward_from, NULL);
            if (buff) free(buff);

            gtk_grid_attach(GTK_GRID(chat_window_grid), forward_label, 1, current_id, 1, 1); 
            current_id++;
        } else if (model_message->data_type == MESSAGE_FILE) {
            forward_label = GTK_WIDGET(gtk_builder_get_object(forward_builder, "current_forward_label")); 
            gtk_grid_attach(GTK_GRID(chat_window_grid), forward_label, 1, current_id, 1, 1); 
            current_id++;
        }  
        gtk_grid_attach(GTK_GRID(chat_window_grid), box, 1, current_id, 1, 1); 
        gtk_widget_show (box);

    } else {
        image = GTK_WIDGET(gtk_builder_get_object(message_builder, "other_user_msg_image"));

        if (image_pixbuf) {
            gtk_image_set_from_pixbuf(GTK_IMAGE(image), image_pixbuf);
        } else {
            image_pixbuf = gdk_pixbuf_new_from_file_at_size(get_path_to_image("click.png"), 100, 100, NULL);
            gtk_image_set_from_pixbuf(GTK_IMAGE(image), image_pixbuf);
        }

        gtk_container_add(GTK_CONTAINER(box), image);     
        if(strlen(model_message->forward_from) > 0) {
            forward_label = GTK_WIDGET(gtk_builder_get_object(forward_builder, "other_forward_label")); 
            // gtk_label_set_text(forward_label, mx_strjoin("From: ",model_message->forward_from));
            gchar* buff = message_about;
            message_about = g_strjoin(" ", message_about, "From:", model_message->forward_from, NULL);
            if (buff) free(buff);

            gtk_grid_attach(GTK_GRID(chat_window_grid), forward_label, 0, current_id, 1, 1);
            current_id++;
        } else if (model_message->data_type == MESSAGE_FILE) {
            forward_label = GTK_WIDGET(gtk_builder_get_object(forward_builder, "other_forward_label")); 
            gtk_grid_attach(GTK_GRID(chat_window_grid), forward_label, 1, current_id, 1, 1); 
            current_id++;
        }
        gtk_grid_attach(GTK_GRID(chat_window_grid), box, 0, current_id, 1, 1); 
        gtk_widget_show (box);
    }

    

    if (message_about) {
        gtk_label_set_text(forward_label, message_about);
        gtk_widget_show(forward_label);
    }
    

    g_signal_connect(box, "button_press_event", callback_click_message, model_message);
 
    current_layout_info->message_position_y = current_id; 
 
    GtkWidget *chat_viewport = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_viewport")); 
     
    GtkAdjustment *adjustment = gtk_viewport_get_vadjustment(GTK_VIEWPORT(chat_viewport)); 
    gtk_adjustment_set_upper(adjustment, gtk_adjustment_get_upper(adjustment) + 500); 
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment)); 
    
}


void send_message_button_clicked(GtkWidget *widget, t_current_window_info *current_window_info)
{
    GtkWidget *type_message_entry = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "type_message_entry"));
    char *message_str = mx_strdup((char*)gtk_entry_get_text(GTK_ENTRY(type_message_entry)));
    for(int i = 0; i < strlen(message_str); i++){
        if(message_str[i] == '\''){
            message_str[i] = '`';
        }
    }
    if(message_str && strlen(message_str) > 0){
        t_model_message *message = NULL;
        char *to_user = get_current_user_to_talk();
        if(to_user) 
            message = controller_send_message(to_user, MESSAGE_TEXT, message_str);
        
        if (message != NULL) {
            gtk_entry_set_text(GTK_ENTRY(type_message_entry), "");
            view_message(message, current_window_info);
        }
    }

    t_egypt_elements *to_clear = get_egypt_element();
    if(to_clear){
        if(to_clear->message){
            mx_strdel(&(to_clear->message));
        }
    }
    
    GtkWidget *file_chooser = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "gtkfile_chooser_button")); 
    if(file_chooser){
        char *selected_file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)); 
        if(selected_file) {
            t_model_message *message = NULL;
            char *to_user = get_current_user_to_talk();
            if(to_user) 
                message = controller_send_message(to_user, MESSAGE_FILE, selected_file);
            if (message != NULL) {
                gtk_file_chooser_unselect_all(GTK_FILE_CHOOSER(file_chooser));
                view_file(message, current_window_info);
            }
        }
    }
}

// void send_file_as_message(GtkWidget *widget, t_current_window_info * current_window_info){ 
//    GtkWidget *file_chooser = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "gtkfile_chooser_button")); 
//     char *selected_file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)); 
//     if(selected_file) {
//         t_model_message *message = NULL;
//         char *to_user = get_current_user_to_talk();
//         if(to_user) 
//             message = controller_send_message(to_user, MESSAGE_FILE, selected_file);
//         if (message != NULL) {
//             gtk_file_chooser_unselect_all(GTK_FILE_CHOOSER(file_chooser));
//             view_file(message, current_window_info);
//         }
//     }

// }

static int new_messages_socket = 0;
static char* new_message_str = NULL;

void*
 check_new_messages(t_current_window_info* window_info) {

    cJSON* cookies = get_cookies();

    if (new_messages_socket == 0) {

        
        // connect to server
        // ACTION: create user new messages socket
        // FROM: username
        // TOKEN: token

        struct sockaddr_in* serv_addr = malloc(sizeof(struct sockaddr_in));
    
        memset(serv_addr, '0', sizeof(*serv_addr));

        if((new_messages_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Error : Could not create socket \n");
            return NULL;
        }
        
        set_new_messages_socket(new_messages_socket);

        serv_addr->sin_family = AF_INET;
        serv_addr->sin_port   = htons(PORT);


        if(inet_pton(AF_INET, get_server_ip(), &(serv_addr->sin_addr)) <= 0)
        {
            printf("\n inet_pton error occured\n");
            return NULL;
        }

        

        if (connect(new_messages_socket, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) < 0) {
            printf("\n Error : Connect Failed \n");
            return NULL;
        }


        cJSON* protocol = create_protocol();
        add_to_protocol_string(protocol, "FROM", get_from_protocol_string(cookies, "USERNAME"));
        add_to_protocol_string(protocol, "TOKEN", get_from_protocol_string(cookies, "TOKEN"));

        add_to_protocol_string(protocol, "ACTION", "ADD NEW MESSAGES SOCKET");

        char* request = cJSON_Print(protocol);
        send(new_messages_socket, request, strlen(request), 0);
        
        char* response = mx_strnew(256);
        
        recv(new_messages_socket, response, 256, 0);
        printf("response: there we go: %s\n", response);
        fflush(stdout); 
        free(request);
        free(response);
    }

    if (new_message_str == NULL) {
        new_message_str  = mx_strnew(READ_SIZE);
    }

    int read_number = 0;
    while (1) {

        read_number = recv(new_messages_socket, new_message_str, READ_SIZE, 0);
        fflush(stdout);
        if (read_number && read_number != -1) {
            // add message to db
            // view message
            t_model_message* model_message = from_string_model_message(new_message_str);
            /**
             * @
             *char **all_chats  = get_all_chats(...) 
             * for(int i = 0; i < count_of_chats; i++)
             * if (!strcmp(model_message->from_user, all_chats[i])
             * 
             */
            printf("message: %s\n",  new_message_str);
            upload_chats_on_add(model_message->from_user, window_info);
            set_chat_new_message(model_message->from_user, window_info);
            if (model_message->status == MESSAGE_EDITED) {
                update_message(model_message);
                char* to_user = get_from_protocol_string(cookies, "TO USER");
                if (to_user != NULL && model_message != NULL && strcmp(model_message->from_user, to_user) == 0) {
                    GtkWidget* button = gtk_button_new_with_label(to_user);
                    choose_chat(button, window_info);
                    gtk_widget_destroy(button);
                }
                
            } else {
                insert_data_message(model_message);
                char* to_user = get_from_protocol_string(cookies, "TO USER");
                if (to_user != NULL && model_message != NULL && strcmp(model_message->from_user, to_user) == 0) {
                    if (model_message->data_type == MESSAGE_TEXT)
                        view_message(model_message, window_info);
                    else if (model_message->data_type == MESSAGE_FILE) {
                        t_model_resource* resource = send_get_resource_request(model_message->data);
                        // pthread_t* current_thread = get_current_thread();
                        // pthread_join(*current_thread, NULL);
                        insert_data_resource(resource);
                        printf("before request\n");
                        request_file_if_not_exist(resource->path);
                        // current_thread = get_current_thread();
                        // pthread_join(*current_thread, NULL);
                        printf("after request\n");
                        view_file(model_message, window_info);
                    }
                    else if(model_message->data_type == MESSAGE_STONE) {
                        t_model_stone* stone = send_get_stone_request(model_message->data);
                        insert_data_stone(stone);
                        request_file_if_not_exist(stone->path);
                        view_stone(model_message, window_info);
                    }
                }
            }
            

            memset(new_message_str, '\0', read_number);
            sleep(1);

        }
    }


}