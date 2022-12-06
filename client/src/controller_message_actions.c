#include "controller_message_actions.h"
#include "controller_start_chat.h"
// static int current_chat_count = 0;

static GtkGrid*   message_actions_grid = NULL;
static long selected_message = -1;
static GtkLabel* selected_message_label = NULL;
static GtkPopover *popover_for_forward = NULL;
static GtkPopover *popover_for_edit    = NULL;
static t_current_window_info* static_current_window_info = NULL;


void set_static_current_window_info(t_current_window_info* current_window_info) {
    static_current_window_info = current_window_info;
}

void add_chats_for_forward(char **username, t_current_window_info *current_window_info, int count) {

    for(int chat_index = 0; chat_index < count; chat_index++) {
    
        gtk_builder_add_from_file(current_window_info->builder, get_path_to_glade("user_chat_button.glade"), NULL);
        
        GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "person_chat_button"));
        GtkWidget *image = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "user_image"));

        GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "home_chats_grid"));

        t_model_resource *avatar = send_get_avatar_request(username[chat_index]);

        insert_data_resource(avatar);

        GdkPixbuf *image_pixbuf = gdk_pixbuf_new_from_file_at_size(request_file_if_not_exist(avatar->path), 80, 80, NULL);

        gtk_grid_insert_column (GTK_GRID(home_chats_grid), get_current_chat_count());

        gtk_button_set_label(GTK_BUTTON(button), username[chat_index]);

        gtk_image_set_from_pixbuf(GTK_IMAGE(image), image_pixbuf);
            
        gtk_widget_set_size_request(button, 100, 100);
            
        gtk_grid_attach (GTK_GRID(home_chats_grid), button, get_current_chat_count(), 1, 1, 1);
            
        g_signal_connect(button, "clicked", G_CALLBACK(forward_clicked), current_window_info);

        // current_chat_count++;
    }
}

void send_edited_clicked(GtkWidget *widget, GtkWidget* entry) {

    if (selected_message != -1) {

        t_model_message* selected_message_model = get_message_by_id(selected_message);

        if ( strcmp(selected_message_model->from_user, get_from_protocol_string(get_cookies(), "USERNAME")) == 0 ) {
            selected_message_model->status = MESSAGE_EDITED;    
            memset(selected_message_model->data, '\0', strlen(selected_message_model->data));
            strcpy(selected_message_model->data, gtk_entry_get_text(entry));

            cJSON* protocol = create_protocol();
            add_to_protocol_string(protocol, "FROM", get_from_protocol_string(get_cookies(), "USERNAME"));
            add_to_protocol_string(protocol, "TOKEN", get_from_protocol_string(get_cookies(), "TOKEN"));
            selected_message_model->id = selected_message;

            send_message(selected_message_model, protocol);

            // update on user that edit
            gtk_label_set_text(selected_message_label, gtk_entry_get_text(entry));
            gtk_widget_show(selected_message_label);
        }

        gtk_popover_popdown(popover_for_edit);

        free_model_message(&selected_message_model);

    }

}

void callback_edit_message(GtkWidget *b, GdkEventButton *event,  char* text) {
    if (selected_message != -1)
        printf("edit message: %i\n", selected_message);
    
    GtkGrid* edit_grid = gtk_grid_new();
    gtk_grid_insert_row(edit_grid, 0);
    gtk_grid_insert_row(edit_grid, 1);

    GtkEntry* entry = gtk_entry_new();
    gtk_entry_set_text(entry, gtk_label_get_text(selected_message_label));

    GtkButton* send_edited = gtk_button_new_with_label("Send");
    g_signal_connect(send_edited, "clicked", send_edited_clicked, entry);

    gtk_grid_attach(edit_grid, entry, 0, 0, 1, 1);
    gtk_grid_attach(edit_grid, send_edited, 0, 1, 1, 1);

    GtkPopover* edit_popover = gtk_popover_new(b);
    popover_for_edit = edit_popover;
    gtk_popover_set_position(edit_popover, GTK_POS_RIGHT);

    gtk_container_add(GTK_CONTAINER(edit_popover), edit_grid);

    gtk_widget_show_all(edit_popover);
}

void callback_reply_message(GtkWidget *b, GdkEventButton *event,  char* text) {
    if (selected_message != -1) {
        printf("reply message: %i\n", selected_message);
    }
}


void forward_clicked(GtkWidget *widget, t_current_window_info *current_window_info) {
    t_model_message *response = NULL;
    long* msg_id = (long)current_window_info->data;
    t_model_message *msg = get_message_by_id(msg_id);
    fprintf(stderr, "\n\nFORWARD %s \n\n", msg->from_user);

    msg->forward_from = mx_strdup(msg->from_user);
    
    free(msg->to_user);
    msg->to_user = mx_strdup(gtk_button_get_label(GTK_BUTTON(widget)));
    
    if(msg->data_type == MESSAGE_FILE) {
        t_model_resource *resource = get_resource_by_id(msg->data);
        response = controller_forward_message(msg->to_user, msg->data_type, resource->name, msg->forward_from);

    } else if(msg->data_type == MESSAGE_TEXT) {
        response = controller_forward_message(msg->to_user, msg->data_type, msg->data, msg->forward_from);
    }
    gtk_popover_popdown(popover_for_forward);

    char* to_user = get_current_user_to_talk();
    if (to_user != NULL && (strcmp(response->to_user, to_user) == 0) && static_current_window_info != NULL) 
    {
        printf("There\n\n");
        if (response->data_type == MESSAGE_TEXT) {
            view_message(response, static_current_window_info);
        } else if (response->data_type == MESSAGE_FILE) {
            // add request file if not exist
            view_file(response, static_current_window_info);
        }
    }
}

void callback_forward_message(GtkWidget *b, GdkEventButton *event,  char* text) {

    GtkBuilder *builder = gtk_builder_new_from_file(get_path_to_glade("forward_msg.glade"));
    
    GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(builder, "home_chats_grid"));

    GtkWidget *home_chats_window = GTK_WIDGET(gtk_builder_get_object(builder, "home_chats_scrolled_window"));


    t_current_window_info *current_window_info = create_current_window_info();
    current_window_info->builder = builder;
    current_window_info->data = (void*)selected_message;
    int user_chats_count = 0; 
    char **user_chats = get_all_user_chats(get_from_protocol_string(get_cookies(), "USERNAME"), &user_chats_count); 

    add_chats_for_forward(user_chats, current_window_info, user_chats_count);

    popover_for_forward = gtk_popover_new(b);

    gtk_popover_set_position(popover_for_forward, GTK_POS_RIGHT);

    gtk_container_add(GTK_CONTAINER(popover_for_forward), home_chats_window);

    gtk_widget_show_all(popover_for_forward);

    if (selected_message != -1)
        printf("forward message: %i\n", selected_message);
}


void create_message_actions_grid() {

    message_actions_grid = gtk_grid_new();

    GtkButton* edit = NULL;

    if (selected_message != -1) {
        t_model_message* message = get_message_by_id(selected_message);

        if (message->data_type == MESSAGE_TEXT) {

            edit = gtk_button_new_with_label("Edit");
            g_signal_connect(edit, "clicked", callback_edit_message, NULL);

        } 

        free_model_message(&message);

    }
    
    GtkButton* reply = gtk_button_new_with_label("Reply");
    GtkButton* forward = gtk_button_new_with_label("Forward");

    g_signal_connect(reply, "clicked", callback_reply_message, NULL);
    g_signal_connect(forward, "clicked", callback_forward_message, NULL);

    gtk_grid_insert_column(message_actions_grid, 0);
    gtk_grid_insert_row(message_actions_grid, 0);
    gtk_grid_insert_row(message_actions_grid, 1);
    gtk_grid_insert_row(message_actions_grid, 2);

    if (edit != NULL)
        gtk_grid_attach(message_actions_grid, edit, 0, 0, 1, 1);
    gtk_grid_attach(message_actions_grid, reply, 0, 1, 1, 1);
    gtk_grid_attach(message_actions_grid, forward, 0, 2, 1, 1);

}

void callback_message_actions_popover_closed(GtkWidget* popover, GdkEventButton* event, gpointer* data) {
    gtk_widget_destroy(popover);
    selected_message = -1;
    selected_message_label = NULL;
    message_actions_grid = NULL;
}

void show_message_actions_popover(GtkWidget* label) {
    if (message_actions_grid == NULL) {
        create_message_actions_grid();
    }

    GtkWidget* message_popover =  gtk_popover_new (label);
    selected_message_label = label;
    gtk_container_add(GTK_CONTAINER(message_popover), GTK_WIDGET(message_actions_grid));
    gtk_popover_set_position(message_popover, GTK_POS_RIGHT);
    gtk_widget_show_all(message_popover);
    gtk_popover_popup(message_popover);
    g_signal_connect(message_popover, "closed", callback_message_actions_popover_closed, NULL);
}

char *get_correct_path(char *path, char *name){
        char * real_path = mx_replace_substr(path, "./server", "./client");
        real_path = mx_replace_substr(real_path, "\r\n", "");
        int name_len = strlen(name);
        int dot_idx;
        for(dot_idx = name_len; dot_idx >= 0; dot_idx--){ 
            if(name[dot_idx] == '.' ){
                break;
            }
        }
        char *real_path_delete = real_path;
        real_path = mx_strjoin(real_path, name + dot_idx); 
        mx_strdel(&real_path_delete);
        return real_path;
}

void callback_click_message(GtkWidget *b, GdkEventButton *event,  t_model_message* model_message) {
    if(event->type == GDK_BUTTON_PRESS  &&  event->button == 3) {
        printf("message id: %zu\n", model_message->id);
        GList* childs = gtk_container_get_children(GTK_CONTAINER(b));
        GtkLabel* label = GTK_LABEL(childs->data);
        
        selected_message = (long)model_message->id;
        show_message_actions_popover(label);

        g_list_free(childs);
    } else if(GTK_IS_IMAGE(gtk_container_get_children(GTK_CONTAINER(b))->data) && (event->type == GDK_BUTTON_PRESS  &&  event->button == 1)){

        t_model_resource *msg_resource = get_resource_by_id(model_message->data);
        char * real_path = mx_replace_substr(msg_resource->path, "./server", "./client");

        char * real_path_tmp = get_correct_path(msg_resource->path, msg_resource->name);

        char* mv_command = NULL;
        char *rename_command_mask = "cp '%s' '%s'";
        asprintf(&mv_command, rename_command_mask, real_path, real_path_tmp );

        real_path = get_correct_path(msg_resource->path, msg_resource->name);

        fflush(stdout);
        system(mv_command);
        char* open_command = mx_strjoin("open ", real_path_tmp);
        system(open_command);

        mx_strdel(&open_command);
        mx_strdel(&real_path);
        mx_strdel(&real_path_tmp);
        mx_strdel(&real_path);
        mx_strdel(&mv_command);
    }
}

